//=======================================================================
// This is the Main file used for integration testing.  
//
// Date:    Jan. 21, 2016
//=======================================================================

#include"Counts.hpp"
#include"Controller.hpp"
#include"Ship_Type_Enum.hpp"
#include<iostream>
#include<string>

using namespace std;

int main(){
    // initiate a Controller class
    Controller ctr {};
    ctr.Start();

    return 0;
}
