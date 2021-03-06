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
#include"Controller.hpp"

class Simulation;
class Console;

Controller::Controller() : 
    steps_left {0}, 
    state {State::STOP},
    steps {0},
    sim {40, 50, 25},
    open_flag {true},
    X {35}, 
    Y {20} {}

Controller::~Controller(){
}

void Controller::CloseSim(){
    open_flag = false;
}

void Controller::Start(){
    while (state != State::CLOSE) {
        switch (state) {
            case State::SINGLE_STEP:        // run the sim one time step and write the results to file
                OneStep();                  // runs sim one time step and sends results to console to be written to file
                GetState();                 // gets the state for the next iteration
                break;
            case State::RUNNING:
                while (steps_left > 0) {
                    OneStep();
                    steps_left--;
                }
                GetState();
                break;
            case State::STOP:
                GetState();
                break;
        }

    }
}

void Controller::OneStep(){
    sim.Update();
    console.Output(sim.GetCounters(), sim.Grid(), X, Y);
    steps++;
}

void Controller::GetState(){
    state = console.UserIO();
    if (state == State::RUNNING) {
        steps_left = console.RunSteps();
    }
}




