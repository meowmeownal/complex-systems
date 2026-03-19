#include <cstdlib>
#include <cmath>
#include <fstream>
#include<iostream>
#include<vector>
#define N 60
#define M 60

std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>>& A)
{
 for(int i = 0; i <= N-1; i++ ) 
 {
   for(int j = 0; j <=M-1; j++)
   {
    out<<A[i][j]<<" ";
   }
   out<<"\n"; 
 }  

    return out;    
}

int conv (std::vector<std::vector<int>>& kernel, std::vector<std::vector<int>>& A, int x, int y)
{
    int suma = 0;

    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j <  2; j++)
        {
            int row = (x + i +N) % N;
            int col = (y+j+M) % M;
            suma += kernel[i+1][j+1] *A[row][col];

        }
    }
    return suma;
}



int main()
{
    std::vector<std::vector<int>> kernel = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };

    std::vector<std::vector<int>> A(N, std::vector<int>(M));

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            A[i][j] = rand() % 2;

        }
    }

    
    std::vector<std::vector<int>> A_new(N, std::vector<int>(M, 0));

    for(int t = 0; t < 2; t++)
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
                int suma = conv(kernel, A, i, j);

                if(A[i][j] == 0)
                {
                    if(suma == 4 || suma == 6 || suma == 7 || suma == 8)
                    {
                        A_new[i][j] = 1;
                    }
                    else
                    {
                        A_new[i][j] = 0;
                    }
                }
                else
                {
                    if(suma == 3 || suma == 5 || suma == 7 || suma == 8 || suma == 6)
                    {
                        A_new[i][j] = 1; 
                    }
                    else
                    {
                        A_new[i][j] = 0; 
                    }
                }
            }
        }
        A = A_new;
        A_new.assign(N, std::vector<int>(M, 0));
        std::cout<<A<<"\n";
    }

    

    


     
}
