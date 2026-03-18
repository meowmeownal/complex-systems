#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

int func1(double t, const double y[], double f[], void* p )
{
    double m = ((double*)p)[0];
    double epsilon = ((double*)p)[1];

    (void)(t); //unused parameter
    f[0] = y[1];
    f[1] = -epsilon*(y[0]*y[0] -1)*y[1] -y[0] + m;
    return GSL_SUCCESS;
}



void solve_div_eq(gsl_odeiv2_system *system, double tp, double tk, double x0[], double y0[], int fun, size_t size_x, size_t size_y)
{
    gsl_odeiv2_driver * d1 = gsl_odeiv2_driver_alloc_y_new (system, gsl_odeiv2_step_rk8pd,1e-6, 1e-6, 1e-6);
    int i;
    double t = tp, t1 = tk;
    double y[2]; //inital vals
    //double y_all[10]; //size_x *2

    //std::ofstream file("r" + std::to_string(fun) + ".csv");

    for(size_t s = 0; s < size_y; s++)
    {

        for(size_t z = 0; z < size_x; z++)
        {
            y[0] = x0[z]; //x
            y[1] = y0[s];

            t = tp; 
            std::ofstream file("r_amp" + std::to_string(fun) + "_" + std::to_string(z) + ".csv");

            for (i = 1; i <= 1000; i++) 
            {
                double ti = t1 * i / 1000.0; //controlled time step, max step in given iteration
                int status = gsl_odeiv2_driver_apply (d1, &t, ti, y);

                if (status != GSL_SUCCESS)
                {
                    printf ("error, return value=%d\n", status);
                    break;
                }
                // y_all[0+z*2] = y[0]; 
                // y_all[1 + z*2] = y[1]; 

                file << y[0] << ", " << y[1]<< "\n";

                
            }
            //file << y_all[0] << ", " << y_all[1]<< ", " << y_all[2]<< ", " << y_all[3]<< ", " << y_all[4]<< ", " << y_all[5]<< ", " << y_all[6]<< ", " << y_all[7]<< ", " << y_all[8]<< ", " << y_all[9]<< "\n";
            //file << "\n ";
 
            file.close();
        }
    
    }
    //file.close();
    
    gsl_odeiv2_driver_free (d1);



}


int main (void)
{
    double params1[2] = {0.9, 0.0};
    double params2[2] = {0.95, 0.0};
    double params3[2] = {0.99, 0.0};
    double params4[2] = {1.05, 0.0};


    double x0[1] = {0.9};
    double y0[1] = {0.6};

        
    
    gsl_odeiv2_system sys1 = {func1, NULL, 2, &params1}; //func, jac, dimensions, parameters
    gsl_odeiv2_system sys2 = {func1, NULL, 2, &params2}; 
    gsl_odeiv2_system sys3 = {func1, NULL, 2, &params3}; 
    gsl_odeiv2_system sys4 = {func1, NULL, 2, &params4}; 


    solve_div_eq(&sys1, 0, 60, x0, y0, 1, 1, 1);
    solve_div_eq(&sys2, 0, 60, x0, y0, 2, 1, 1);
    solve_div_eq(&sys3, 0, 60, x0, y0, 3, 1, 1);
    solve_div_eq(&sys4, 0, 60, x0, y0, 4, 1, 1);




    

}


