#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include <cstdlib> 
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include<map>
#define _USE_MATH_DEFINES
#include <cmath>

inline int edges(int x, int s)
{
    return (x % s + s) % s;
}


void initRandom() 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int uniform(int M) 
{
     return std::rand() % M; //%2 -(0,1)
}

void wandering1D(int steps, int &full_d, int file_name)
{
    std::ofstream file;
    std::ostream *out = nullptr;

    if(file_name != 0)
    {
        file.open("1D_" + std::to_string(file_name) + ".csv");
        out = &file;
    }
    int n2{0};
    int n1{0};
    for(int i = 0; i < steps; i++)
    {
        int step_direct = uniform(2);
        if(step_direct == 0) n2++;//left
        else n1++;

        if(out) *out << n1 - n2<<"\n";
    }
    if (file.is_open()) file.close();
    full_d = n1 - n2;

}

std::vector<std::vector<int>> wandering2D(int M, int steps)
{
    std::vector<std::vector<int>> visitors(M,std::vector<int>(M,0));
    int x = uniform(M); //starting point
    int y = uniform(M);

    //visitors[y][x] y - up or down, x - right or left
    for(int  k = 0; k < steps; k++)
    {
        int step_direct = uniform(4); //wiersz - y
        switch(step_direct) 
        {
        case 0: //going left 
            x -= 1;
            visitors[edges(y,M)][edges(x,M)]++;
            break;
        case 1: //going right
            x += 1;
            visitors[edges(y,M)][edges(x,M)]++;
            break;

        case 2: //going down
            y -= 1;
            visitors[edges(y,M)][edges(x,M)]++;
            break;
        case 3: //going up
            y += 1;
            visitors[edges(y,M)][edges(x,M)]++;
            break;
        }

    }

    return visitors;
}

double wandering2D_free(int steps)
{
    int x{0};
    int y{0};

    for(int  k = 0; k < steps; k++)
    {
        int step_direct = uniform(4); 
        switch(step_direct) 
        {
        case 0: //going left 
            x -= 1;
            break;
        case 1: //going right
            x += 1;
            break;

        case 2: //going down
            y -= 1;
            break;
        case 3: //going up
            y += 1;
            break;
        }

    }


    return std::sqrt(x*x + y*y);

}

int main()
{
    int full_d_1d {0};
    wandering1D(200, full_d_1d, 1);
    wandering1D(200, full_d_1d, 2);
    wandering1D(200, full_d_1d, 3);
    wandering1D(200, full_d_1d, 4);
    wandering1D(200, full_d_1d, 5);

    std::vector<int> full_d_vec;
    int N = 1000000;
    for(int p = 0; p < N; p++)
    {
        int fd {0}; //road at the end
        wandering1D(20, fd, 0);
        full_d_vec.push_back(fd);
    }

    std::ofstream file2("hist.csv");
    std::unordered_map<int, int> hist;
    for(int x : full_d_vec)
        hist[x]++;
    for(const auto &para : hist)
        file2 << para.first << ","<<para.second<<"\n";
    file2.close();

//---------------zad2-----------------
    int M {10};
    std::vector<std::vector<int>> visitors = wandering2D(M,N);
    double sum {0};
    double var {0};

    for(int i = 0; i < M; i++)
        for(int j = 0; j < M; j++)
        {
            std::cout<<visitors[i][j]<<", ";
            sum += visitors[i][j];
        }

    std::cout<<"\n";

    double mean = sum /(M*M);

    for(int i = 0; i < M; i++)
        for(int j = 0; j < M; j++)
            var += (double(visitors[i][j] - mean)* double(visitors[i][j] - mean));
    
    std::cout<<"mean: "<<mean<<"\n";
    std::cout<<"standard devivivvava: " << std::sqrt(1/double(N) *var)<<"\n";

    //----------------------zad3----------------------------

    double d{0};
    double d2{0};
    double d3{0};
    for(int i = 0; i < 10*10; i++)
        d += wandering2D_free(10);

    for(int i = 0; i < 10*100; i++)
        d2 += wandering2D_free(100);

    for(int i = 0; i < 10*200; i++)
        d3 += wandering2D_free(200);

    std::cout<< "how far away from starting point with 10 steps: "<< d /100 <<"\n";
    std::cout<< "how far away from starting point with 100 steps: "<< d2 / 1000 <<"\n";
    std::cout<< "how far away from starting point with 200 steps: "<< d3 / 2000 <<"\n";

}
