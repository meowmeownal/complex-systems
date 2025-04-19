#include <iostream>
#include <vector>
#include <tuple>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <ctime>
#include <unordered_set>
#include <fstream>
#include <iomanip>

const int N{16};

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& macierzatko) 
{
    for (const auto& row : macierzatko) 
    {
        for (const auto& elem : row) {
            out << elem << " "; 
        }
        out << "\n"; 
    }
    return out;
}

double uniform()
{
    return  rand() / double (RAND_MAX);
}

// int minimum(int )

//tworze funkcje siatka ktora przyjmuje pstwo, 
void siatka(double p, std::vector<std::vector<double>> & A)
{
    //petla sprawdzajaca czy obsadzic wezel, czy nie SIATKA Z OBWÓDKA ZER 
    double k {1};
    for(int x = 1; x < A.size() - 1 ; x++)
        for(int y = 1; y < A[0].size() - 1; y++)
            {
               //if(A[x][y] != 0) continue;
                if(uniform() <= p)
                {
                    if(A[x-1][y] != 0 && A[x][y-1] != 0) A[x][y] = std::min(A[x-1][y], A[x][y-1]);
                    else if(A[x-1][y] != 0 || A[x][y-1] != 0) A[x][y] = (A[x-1][y] != 0) ? A[x-1][y] : A[x][y-1];
                    else if ( (A[x-1][y] == 0 && A[x][y-1] == 0)) 
                    {
                        A[x][y] = k;
                        k++;
                    }
                }
            }

    
    //druga iteracja uzupelniajaca:

    bool zmieniono = true;

    while (zmieniono)
    {
        zmieniono = false;
        for(int x = 1; x < A.size() - 1; x++)
            for(int y = 1; y < A[0].size() - 1; y++)
            {
                if (A[x][y] == 0) continue;
                double current = A[x][y];
                std::vector<double> candidates;

                if( A[x-1][y] != current && A[x-1][y] != 0)  candidates.push_back(A[x-1][y]);
                if( A[x][y-1] != current && A[x][y-1] != 0)  candidates.push_back(A[x][y-1]);
                if( A[x+1][y] != current && A[x+1][y] != 0 )  candidates.push_back(A[x+1][y]);
                if( A[x][y+1] != current && A[x][y+1] != 0)  candidates.push_back( A[x][y+1]);

                if (!candidates.empty())
                {
                    double min_sasiad = *std::min_element(candidates.begin(), candidates.end());
                    //A[x][y] = std::min(current, min_sasiad);
                    if(min_sasiad < current)
                    {
                        A[x][y] = min_sasiad;
                        // if(A[x-1][y] != 0 && A[x-1][y] != min_sasiad) A[x-1][y] = min_sasiad;
                        // if(A[x][y-1] != 0 && A[x][y-1] != min_sasiad) A[x][y-1] = min_sasiad;
                        zmieniono = true;
                    }
                }
            }
    }       
}

// void siatka(double p, std::vector<std::vector<double>> &A)
// {
//     double k {1}; 

//     for(int x = 1; x < A.size() - 1 ; x++) 
//         for(int y = 1; y < A[0].size() - 1; y++) 
//             if(uniform() <= p) 
//             {
//                 double up = A[x-1][y];
//                 double left = A[x][y-1];

//                 bool up_occupied = (up != 0);
//                 bool left_occupied = (left != 0);

//                 if (!up_occupied && !left_occupied) 
//                 {
//                     A[x][y] = k++;
//                 }
//                 else if (up_occupied && !left_occupied) 
//                 {
//                     A[x][y] = up;
//                 }
//                 else if (!up_occupied && left_occupied) 
//                 {
//                     A[x][y] = left;
//                 }
//                 else {
//                     double minLabel = std::min(up, left);
//                     double maxLabel = std::max(up, left);
//                     A[x][y] = minLabel;

//                     for(int i = 1; i < A.size() - 1; i++) 
//                         for(int j = 1; j < A[0].size() - 1; j++)
//                             if (A[i][j] == maxLabel) A[i][j] = minLabel;
        
                    
//                 }
//             }
    
    
// }
bool isperkolasjon(const std::vector<std::vector<double>>& grid)
 {
    std::unordered_set<double> up;
    std::unordered_set<double> down;

    for (int j = 1; j < grid.size() - 1; j++) 
        if (grid[1][j] != 0)up.insert(grid[1][j]);

    for (int j = 1; j < grid.size() - 1; j++) 
        if (grid[grid.size() - 2][j] != 0) down.insert(grid[grid.size() - 2][j]);

    for (double etykieta : up) 
        if (down.count(etykieta))return true; 

    return false; 
}

int main()
{
    std::srand(std::time(0)); 
    //std::vector<std::vector<double>> grid(N+2, std::vector<double>(N+2, 0));
    std::vector<double> pstwo {0.4, 0.6, 0.8};

    for(int i = 0; i < pstwo.size(); i++)
    {   
        std::ofstream file1("pstwo_" + std::to_string(pstwo[i]) + ".csv");
        std::vector<std::vector<double>> grid(N+2, std::vector<double>(N+2, 0));
        siatka(pstwo[i], grid);


        file1<<grid<<"\n";
        file1.close();

        std::cout<<"pstw: "<<pstwo[i]<<"\n";
        if(isperkolasjon(grid)) std::cout<<"perkolacja\n";
        else std::cout<<"brak perkolacji\n";
        for(int k = 1; k < grid.size() - 1; k++)
        {
            for(int l = 1; l < grid.size() - 1; l++)
                std::cout << std::setw(3) << grid[k][l]<<" ";
            std::cout<<"\n";            
        }

    }

    std::ofstream file2("zad2.csv");
    for(double p = 0.4; p < 0.81; p+=0.01)
    {   
        double x {0};
        for(int t = 0; t < 1000; t++)
        {
            std::vector<std::vector<double>> grid(N+2, std::vector<double>(N+2, 0));
            siatka(p, grid);
            if (isperkolasjon(grid)) x++;
            // for(int i = 1; i < N -1; i++)
            //     for(int j = 1; j < N -1; j++)
            //         if(grid[1][i] == grid[N-1][j] && grid[1][i] !=0 && grid[N-1][j] != 0) x++;
        }

        file2<< x / 1000 <<", "<<p<<"\n";     
    }
    file2.close();

    std::ofstream file3("zad3.csv");
    int L {32};
    for(double p = 0.4; p < 0.81; p+=0.01)
    {   
        double x {0};
        for(int t = 0; t < 1000; t++)
        {
            std::vector<std::vector<double>> grid(L+2, std::vector<double>(L+2, 0));
            siatka(p, grid);
            if (isperkolasjon(grid)) x++;
        }

        file3<< x / 1000 <<", "<<p<<"\n";
        
    }

    file3.close();
}
