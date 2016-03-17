#include"RandomEvent.hpp"
#include<iostream>

using namespace std;

int main()
{
    int num_runs = 10000;
    int seed = 50;
    int true_count=0;
    int false_count=0;
    for (int i=0; i <num_runs;i++)
    {
        if (IsShipSpawned(seed)) 
            true_count++;
        else
            false_count++;
    }

    cout<<"Seed: "<<seed<<"\tTrue: "<<true_count<<"\tFalse: "<<false_count<<endl;

    cout<<"Testing GetNode(): "<<std::endl;
    int max = 10;
    int results[10];
    for (int i =0; i<10;i++) results[i] = 0;
    for (int i =0; i<10000;i++){
        results[GetNode(max)]++;
    }
    for (int i =0; i<10; i++) cout<<i<<": "<<results[i]<<endl;
    
    return 0;
}
