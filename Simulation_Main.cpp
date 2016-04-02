//=======================================================================
// Simulation class.  This class is responsible for interacting with the controller.  It provides the interface for the Model.
//
// Date:    Jan. 21, 2016
//=======================================================================

#include"Simulation.hpp"
#include"Ship_Type_Enum.hpp"
#include"Counts.hpp"
#include"Ship.hpp"
#include"Ships.hpp"
#include<iostream>

using namespace std;

int main(){
    Simulation sim {40, 50, 25};

    // add 5 of each ship at (34, 19)
    for (int i=0; i<5; i++){
        sim.AddCargoShip(34, 19);
        sim.AddEscortShip(34, 19);
        sim.AddPirateShip(34, 19);
        sim.AddCapturedShip(34, 19);
    }

    Simulation::gridXxYx4 grid = sim.Grid();
    for (int i=0; i<35; i++){
        for (int j=0; j<20; j++){
            for (int k=0; k<4; k++){
                cout<<"("<<i<<","<<j<<")\t\t\t"<<grid[i][j][k]<<endl;
            }
        }
    }
    

    return 0;

}
