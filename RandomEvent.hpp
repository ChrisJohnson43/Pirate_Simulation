//=======================================================================
//File:     This is the file containing the declarations for the free functions that will handle the probabilistic functions used
//           in the model.
//
//Date:   Jan. 21, 2016
//=======================================================================


#ifndef RandomEvent
#define RandomEvent

#include <stdlib.h>
#include <random>

bool isShipSpawned(double p){
    double r = ((double) rand() / (RAND_MAX));                   // 0<r<1
    return (r<p);
}


// Function to randomly pick an integer number in the interval [1,n]
int getNode(int n){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,n);
    return distribution(generator);

}


#endif