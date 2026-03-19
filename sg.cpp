#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <string>

#include <random>
std::mt19937 gen(std::random_device{}());
std::uniform_real_distribution<> dist(0.0, 1.0);

double uniform() 
{
    return dist(gen);
}


double energy(std::vector<int> spins, double J)
{
    size_t size = spins.size();
    double E {0.0};
    for(int i = 0; i < size; i++)
        E -= J*spins[i] *spins[(i+1 + size) % size];

    return E;
}

//mozna
std::vector<std::vector<int>> config_1(int spin_num)
{
    int total = 1 << spin_num; // 2^N
    std::vector<std::vector<int>> configurations;
    for (int i = 0; i < total; ++i) 
    {
        std::vector<int> config(spin_num);
        for (int j = 0; j < spin_num; ++j) 
        {
            config[spin_num - j - 1] = (i >> j) & 1;  //from oldset to youngest 
        }
        configurations.push_back(config);
    }

    return configurations;
}



std::vector<int> bit_to_spin(const std::vector<int>& bits)
{
    std::vector<int> spins(bits.size());
    for (size_t i = 0; i < bits.size(); ++i) 
        spins[i] = (bits[i] == 0) ? -1 : 1;
    
    return spins;
}

int main()
{

    std::vector<std::vector<int>> configs = config_1(5);

    for (const auto& c: configs) 
    {
        auto spin_c = bit_to_spin(c);
        double E = energy(spin_c, 1);

        std::vector<int> spin_real;
        spin_real = bit_to_spin(spin_c);
        for (int s : spin_c)
            std::cout << s << " ";
        std::cout << " E = " << E << '\n';
    }

    return 0;
}
