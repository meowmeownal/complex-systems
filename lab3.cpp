#include <cstdlib>
#include <cmath>
#include <fstream>
#include<iostream>
#include<vector>
#include <iomanip>
#include <deque>
#define N1 50
#define N2 100
#define N3 10000
#define x_01 0.5
#define r1 2.0

// std::ofstream& operator<<(std::ofstream& out, const std::vector<double>& vec) 
// {
//     for (const auto & elem : vec) //typ zastepczy auto 
//     {
//         out << elem << "\n";
//     }
//     out << std::endl; 
//     return out;
// }

std::ostream& operator<<(std::ostream& out, const std::vector<double>& vec) {
    for (const auto & elem : vec) 
    {
        out << elem << " ";
    }
    out << std::endl;
    return out;
}



std::vector<double> log_map(double r, double N, double x_0)
{
    std::vector<double> X(N,0);
    X[0] = x_0;
    for(int i = 1; i < N; i++)
    {   
        X[i] = X[i-1] *r *(1 - X[i-1]);
    }

    return X;
}

int main()
{
    std::vector<double> r = {1,2,3,3.5,3.55,3.6};
    std::vector<double> x_0 = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
    
    std::ofstream file("log_map_data.txt");

    for(int j = 0; j < x_0.size(); j++)
    {
        std::vector<double> solution1 = log_map(r1, N1, x_0[j]);

        file << "# x0 = " << x_0[j]<<std::endl;

        for (int i = 0; i < N1; i++)
        {
            file << i <<" "<< solution1[i]<<std::endl;
        
        }
    }
    file.close();

    std::ofstream file2("log_map_data_r.txt");

    for(int i = 0; i < r.size(); i++)
    {
        std::vector<double> solution2 = log_map(r[i], N2, x_01);
        file2 << "# r = " << r[i]<<std::endl;
        for(int j = 0; j < N2; j++)
        {
            file2 << j <<" "<< solution2[j]<<std::endl;
        }
    }
    file2.close();

    std::vector<double> r3;

    for(double k = 1.00; k <= 4.00; k += 0.01)
    {
        r3.push_back(k);
    }

    std::ofstream file3("log_map_data_1000.csv");

    // std::deque<std::vector<double>> evolution;

    for(int m = 0; m < r3.size(); m++)
    {
        std::vector<double> solution3 = log_map(r3[m], N3, x_01);

        if(solution3.size() >= 1000)
        {
            solution3.erase(solution3.begin(), solution3.end() - 1000);
        }
        file3<< r3[m]<<",";

        for(int l = 0; l < solution3.size(); l++)
        {
            file3 <<  solution3[l]<<",";
        }
        file3<<std::endl;
    }
    file3.close();
}