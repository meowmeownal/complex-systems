#include <cstdlib>
#include <cmath>
#include <fstream>
#include<iostream>
#include<string>

double uniform()
{
    double x;
    x = rand() / double (RAND_MAX);
    return x;

}

int main()
{
    int N = 1e7;
    double p[3] = {0.1, 0.5, 0.9};
    int k = 2;
    double X;
    double U1;
    srand(time(NULL));
    
    
    for(int j = 0; j<3; j++)
    {
        double sum_X = 0;
        double sum_X2 = 0;

        std::ofstream file("./pstwo" + std::to_string(j) + ".csv");

        // if(file.is_open())
        // {
        //     std::cout<<j<<"aaaaaaaaaaaaa"<<std::endl;
        // }
        for(int i =0; i<=N; i++)
        {
            U1 = uniform();
            if (i < 10) {
                std::cout << "U1[" << i << "] = " << U1 << std::endl;
            }
            {
                if(U1 <= p[j])
                {
                    X = 1;
                }
                else
                {
                    X = 0;
                }

                sum_X +=X;
                sum_X2 +=X*X;

                if(i == std::pow(10,k))
                {
                    double X_mean = sum_X/(double)i;
                    double X2_mean = sum_X2/(double)i; 
                    double error_X = std::abs( (X_mean-p[j]) / p[j] );
                    double var_numeric = (X2_mean - X_mean*X_mean) / (double)i;
                    double var_teoreric = (p[j] - p[j]*p[j]) / (double)i;
                    double error_var = std::abs((var_numeric - var_teoreric) / var_teoreric);

                    file<<p[j]<<","<<i<<","<<X_mean<<","<<X2_mean<<","<<error_X<<","<<error_var<<"\n";
                    k++;
                    //std::cout<<j<<" ?????"<<std::endl;

                }
            }
        }

        file.close();
        k = 2;
        sum_X = 0;
        sum_X2 = 0;
        
    }

}