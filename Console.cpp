//=======================================================================
// This is the console class.  It will only be used for testing.  It will have the same interface as the Graphical
// Display.
//
// Date:    Jan. 21, 2016
//=======================================================================

#include"Console.hpp"
#include"Counts.hpp"
#include<iostream>
#include<fstream>
#include<string>
#include"Ship_Type_Enum.hpp"        // enum State

const char Console::pirate_sym = 'P';
const char Console::cargo_sym = 'C';
const char Console::captured_sym = 'A';
const char Console::escort_sym = 'E';


Console::Console(Controller* ref) : control_ref(ref){
    std::cout<<"Enter the name of the file used to write the grid log: ";
    bool flag = true;
    while (flag) {
        flag = false;
        std::cin>>grid_file;
        std::ofstream grid_out {grid_file};
        if (!grid_out) {
            std::cout<<"File was not opened.  Try again.\n";
            flag = true;
        }
        std::cout<<"Enter the name of the file used to write the counts log: ";
    }
    flag = true;
    while (flag) {
        flag = false;
        std::cin>>count_file;
        std::ofstream count_out {count_file};
        if (!count_out) {
            std::cout<<"File was not opened.  Try again.\n";
            flag = true;
        }
    }
}

Console::~Console(){
}

std::string Console::StringCounts(Counts& counts) const {
    std::string str;
    str = "Pirates Entered: " + std::to_string(counts.PiratesEntered()) + "\n";
    str = str + "Pirates Exited: " + std::to_string(counts.PiratesExited()) + "\n";
    str = str + "Pirates Defeated: " + std::to_string(counts.PiratesDefeated()) + "\n";
    str = str + "Cargos Entered: " + std::to_string(counts.CargosEntered()) + "\n";
    str = str + "Cargos Exited: " + std::to_string(counts.CargosExited()) + "\n";
    str = str + "Cargos Captured: " + std::to_string(counts.CargosCaptured()) + "\n";
    str = str + "Captureds Rescued: " + std::to_string(counts.CapturedsRescued()) + "\n";
    str = str + "Escorts Entered: " + std::to_string(counts.EscortsEntered()) + "\n";
    str = str + "Escorts Entered: " + std::to_string(counts.EscortsExited()) + "\n";
    return str;
}


State::Enum Console::UserIO(){
    std::cout<<"Enter [S]ingle Step, [R]un, Sto[P], or [Q]uit. ";
    char input;
    bool flag = true;
    State::Enum state;
    while (flag){
        std::cin>>input;
        switch (input) {
            case 'S':
            case 's':
                state = State::SINGLE_STEP;
                flag = false;
                break;
            case 'R':
            case 'r':
                state = State::RUNNING;
                flag = false;
                break;
            case 'P':
            case 'p':
                state = State::STOP;
                flag = false;
                break;
            case 'Q':
            case 'q':
                state = State::CLOSE;
                flag = false;
                break;
            default:
                std::cout<<"Incorrect input.  Try again.\n";
                flag = true;
        }
    }
    return state; 
}

int Console::RunSteps(){
    std::cout<<"Enter the number of time steps to simulate [1, 1000]: ";
    int num = 0;
    while(std::cin>>num && !(1<=num && num<=1000)){
        std::cout<<"Sorry "<<num<<" is not in the range [1, 1000]. Try again.\n";
    }
    return num;
}

void Console::Output(Counts& counts){
    std::ofstream grid_out;
    std::ofstream count_out;
    grid_out.open(grid_file, std::ios::app);
    count_out.open(count_file, std::ios::app);
    grid_out<<StringMap(counts);
    count_out<<StringCounts(counts);
}

std::string Console::StringMap(Counts& counts) const {
}

