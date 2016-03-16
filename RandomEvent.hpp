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

bool IsShipSpawned(int x)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,100);

    int r = distribution(generator);
    return (r<=x);
}


// Function to randomly pick an integer number in the interval [1,n]
int GetNode(int n){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, (n - 1) );
    return distribution(generator);

}


#endif
