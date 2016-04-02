//=================================================================================================
// File: Controller class
// Author: Chris Johnson
// Date: 3/31/2016
//  This file provides the header for the controller.  This is not the
//  controller that will be used for the final application.  This class is just
//  for integration testing of the Simulation, Ships, and Ship classes.
//=================================================================================================

#include"Counts.hpp"
#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"
#include"Ships.hpp"
#include"Simulation.hpp"
#include"Console.hpp"


class Controller
{
    private:
        int steps_left; 
        State::Enum state;          // the state of the controller 
        Simulation sim;
        Console console;
        int steps;                  // total number of time steps the sim has run
        bool open_flag;             // flag that will be used to close simulation
    public:
        Controller();
        virtual ~Controller();
        void Start();
        void CloseSim();                // used to set open_flag to false (close sim)
}
