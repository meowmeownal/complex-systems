#include <iostream>
#include <vector>
#include <random>
#include <cstdlib> 
#include <ctime>
#include <fstream>
#include <numeric>


template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) 
{
    for (const auto & elem : vec) 
    {
        out << elem << " ";
    }
    out << std::endl;
    return out;
}


void initRandom() 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}
int uniform(int M) 
{
     return std::rand() % M; //%2 -(0,1)
}

double prob()
{
    return rand() / double (RAND_MAX);
}

template<class T>
std::vector<T> vecxmat(std::vector<T> &vec, std::vector<std::vector<T>> &mat)
{
    size_t size = vec.size();
    std::vector<T> result(size, 0.0);
    for(int i = 0; i < size; i++)
        for(int j = 0; j <size; j ++)
            result[j] += vec[i] * mat[i][j];

    return result;
}

std::vector<double> randwalk(std::vector<std::vector<int>> &list)
{
    size_t size = list.size();
    double epsilon {0.0};


    int node_idx = uniform(size);

    std::vector<double> visitors_prev(size, 0.0);
    visitors_prev[node_idx]++;
    std::vector<double> visitors_next(size, 0.0);

    visitors_next = visitors_prev;

    do
    {
        epsilon = 0.0;
        size_t k = list[node_idx].size(); //checking how many possible paths

        if(k == 0) node_idx = node_idx;
        else node_idx = list[node_idx][uniform(k)]; //going one of them

        visitors_next[node_idx]++; //visit has beeen payed....

        double sum_prev= std::accumulate(visitors_prev.begin(), visitors_prev.end(), 0.0);
        double sum_next= std::accumulate(visitors_next.begin(), visitors_next.end(), 0.0);

        for(int i = 0; i <size; i++)
            epsilon += std::abs(visitors_prev[i] / sum_prev - visitors_next[i] / sum_next);

        visitors_prev = visitors_next;
    }while(epsilon >= 1e-6);

    double denominator = std::accumulate(visitors_next.begin(), visitors_next.end(),0.0);

    for(int i = 0; i <  size; i++)
    {
        visitors_next[i] = visitors_next[i] / denominator;
    }

    return visitors_next;
}

std::vector<double> randwalk_teleport(std::vector<std::vector<int>> &list, bool graph3 = false)
{
    size_t size = list.size();
    int node_idx = uniform(size);
    double epsilon {0.0};

    std::vector<double> visitors_prev(size, 0.0);
    visitors_prev[node_idx]++;
    std::vector<double> visitors_next(size, 0.0);
    visitors_next = visitors_prev;
    do
    {   
        epsilon = 0.0;

        size_t k = list[node_idx].size(); //checking how many possible paths 

        if(k == 0 || prob() <= .15) node_idx = uniform(size); //teleports always and anywhere 

        else node_idx =  list[node_idx][uniform(k)]; //new index
        
        //if(graph3) std::cout<<"NODES PATH: "<<node_idx<<"\n";
        visitors_next[node_idx]++; //visit has been payed.....

        double sum_prev= std::accumulate(visitors_prev.begin(), visitors_prev.end(), 0.0);
        double sum_next= std::accumulate(visitors_next.begin(), visitors_next.end(), 0.0);

        for(int i = 0; i < size; i++)
            epsilon += std::abs(visitors_prev[i]/sum_prev - visitors_next[i]/sum_next);
        

        visitors_prev = visitors_next;
    }while(epsilon >= 1e-6 && graph3 == true);

    double denominator = std::accumulate(visitors_next.begin(), visitors_next.end(), 0.0);
    for(int i = 0; i < size; i++)
    {
        visitors_next[i] = visitors_next[i] / denominator;
    }
    return visitors_next;

}

std::vector<double> page_rank(std::vector<std::vector<int>> &list)
{
    size_t size = list.size();
    double epsilon (1e-6);
    double error {0};
    std::vector<double> ni_next(size,0.0);
    std::vector<std::vector<double>> A(size, std::vector<double>(size,0.0));

    for(int i = 0; i <size; i++)
    {
        size_t k = list[i].size();

        if (k == 0) 
        {
            for (int j = 0; j < size; j++)
                A[i][j] = 1.0 / size;
        }
        else
            for (int neighbor : list[i]) 
                A[i][neighbor] = 1.0 / k;
    }

    std::cout<<"macierz A: "<<"\n";
    std::cout<<A<<"\n";

    std::vector<double> ni_prev(size, 1.0/size);
        do
        {
            ni_next = vecxmat(ni_prev, A);
            error = 0;
            for(int l = 0; l < size; l++)
                error += std::abs(ni_next[l] - ni_prev[l]);
        
            ni_prev = ni_next;

        } while (error > epsilon*size);

    return ni_next;
}


int main()
{
     std::vector<std::vector<int>> g1 {
        {1,2,3}, 
        {0},
        {0,1},
        {1,2}
    };

         std::vector<std::vector<int>> g2 {
        {1}, 
        {0},
        {1,3},
        {0,2}
    };

         std::vector<std::vector<int>> g3 {
        {1}, 
        {},
        {1,3},
        {0,2}
    };


    // //--------------------graph1------------------------------
    std::vector<double> rw1 = randwalk(g1);
    std::cout<<"first graph, random walk: "<<rw1<<"\n";

    std::vector<double> rw1t = randwalk_teleport(g1);
    std::cout<<"first graph, random walk + teleport: "<<rw1t<<"\n";

    std::vector<double> pg1 = page_rank(g1);
    std::cout<<"first graph, page rank: "<<pg1<<"\n";

    // //--------------------graph2------------------------------
    std::vector<double> rw2 = randwalk(g2);
    std::cout<<"second graph, random walk: "<<rw2<<"\n";

    std::vector<double> rw2t = randwalk_teleport(g2);
    std::cout<<"second graph, random walk + teleport: "<<rw2t<<"\n";

    std::vector<double> pg2 = page_rank(g2);
    std::cout<<"second graph, page rank: "<<pg2<<"\n";

    ////--------------------graph3------------------------------
    std::vector<double> rw3 = randwalk(g3);
    std::cout<<"third graph, random walk (WONT WORK): "<<rw3<<"\n";

    std::vector<double> rw3t = randwalk_teleport(g3, true);
    std::cout<<"third graph, random walk + teleport: "<<rw3t<<"\n";

    std::vector<double> pg3 = page_rank(g3);
    std::cout<<"third graph, page rank: "<<pg3<<"\n";
}