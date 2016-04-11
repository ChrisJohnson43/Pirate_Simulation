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

class Controller;

typedef int (&grid3D)[35][20][4];

const char Console::pirate_sym = 'P';
const char Console::cargo_sym = 'C';
const char Console::captured_sym = 'A';
const char Console::escort_sym = 'E';

Console::Console() : grid_file {"grid_out.txt"},
    count_file {"count_out.txt"} { 
/*    std::cout<<"Enter the name of the file used to write the grid log: ";
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
    }*/
    std::ofstream grid_out {grid_file};
    if (!grid_out) {
       std::cout<<"File was not opened.  Try again.\n";
    }
    std::ofstream count_out {count_file};
    if (!count_out) {
       std::cout<<"File was not opened.  Try again.\n";
    }
    grid_out.close();
    count_out.close();
  
}

Console::~Console(){
}

std::string Console::StringCounts(Counts* counts) const {
    std::string str = "====================================================================================\n";
    str = str + "Pirates Entered: " + std::to_string(counts->PiratesEntered()) + "\n";
    str = str + "Pirates Exited: " + std::to_string(counts->PiratesExited()) + "\n";
    str = str + "Pirates Defeated: " + std::to_string(counts->PiratesDefeated()) + "\n";
    str = str + "Cargos Entered: " + std::to_string(counts->CargosEntered()) + "\n";
    str = str + "Cargos Exited: " + std::to_string(counts->CargosExited()) + "\n";
    str = str + "Cargos Captured: " + std::to_string(counts->CargosCaptured()) + "\n";
    str = str + "Captureds Rescued: " + std::to_string(counts->CapturedsRescued()) + "\n";
    str = str + "Escorts Entered: " + std::to_string(counts->EscortsEntered()) + "\n";
    str = str + "Escorts Exited: " + std::to_string(counts->EscortsExited()) + "\n";
    return str;
}

void Console::OutputCounts(Counts* counts, grid3D& grid, int x, int y) const {
    std::ofstream count_out;
    count_out.open(count_file, std::ios::app);
    count_out<< "\n====================================================================================\n";
    count_out<<"Pirates Entered: " + std::to_string(counts->PiratesEntered()) + "\n";
    count_out<<"Pirates Exited: " + std::to_string(counts->PiratesExited()) + "\n";
    count_out<<"Pirates Defeated: " + std::to_string(counts->PiratesDefeated()) + "\n";
    count_out<<"Cargos Entered: " + std::to_string(counts->CargosEntered()) + "\n";
    count_out<<"Cargos Exited: " + std::to_string(counts->CargosExited()) + "\n";
    count_out<<"Cargos Captured: " + std::to_string(counts->CargosCaptured()) + "\n";
    count_out<<"Captureds Rescued: " + std::to_string(counts->CapturedsRescued()) + "\n";
    count_out<<"Escorts Entered: " + std::to_string(counts->EscortsEntered()) + "\n";
    count_out<<"Escorts Exited: " + std::to_string(counts->EscortsExited()) + "\n";
    count_out<< "====================================================================================\n";
    for(int i = 0; i < y; i++){
        for (int j=0; j<x; j++){
            if (j ==0) count_out<<"\n";
            if ( grid[j][i][0] > 0){
                count_out<<"A";
            }
            else if (grid[j][i][1] > 0){
                count_out<<"C";
            }
            else if (grid[j][i][2] > 0){
                count_out<<"E";
            }
            else if (grid[j][i][3] > 0){
                count_out<<"P";
            }
            else count_out<<"-";
        }
    }
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

void Console::Output(Counts* counts, grid3D& grid, int x, int y){
    /*
    std::ofstream grid_out;
    std::ofstream count_out;
    grid_out.open(grid_file, std::ios::app);
    count_out.open(count_file, std::ios::app);
    grid_out<<Map(grid, x, y);
    count_out<<StringCounts(counts);
    grid_out.close();
    count_out.close();
    */
    OutputCounts(counts, grid, x, y);
}

std::string Console::StringMap(grid3D& grid, int x, int y) const {
    std::string str;

    for(int i = 0; i < x; i++){
        for(int j =0; j < y; j++){
            if (i == 0) {
                str = str + "\n";
            }
            str = str + "(" + std::to_string(grid[i][j][0]) +","+ std::to_string(grid[i][j][1]) + "," + std::to_string(grid[i][j][2]) + "," + std::to_string(grid[i][j][3]) + ") ";
        } 
    }
    return str;
}

std::string Console::Map(grid3D& grid, int x, int y) const {
    std::string str;
    str = "\n==============================================================================\n";
    for(int i = 0; i < y; i++){
        for (int j=0; j<x; j++){
            if (j ==0) str = str + "\n";
            if ( grid[j][i][0] > 0){
                str = str + "A";
            }
            else if (grid[j][i][1] > 0){
                str = str + "C";
            }
            else if (grid[j][i][2] > 0){
                str = str + "E";
            }
            else if (grid[j][i][3] > 0){
                str = str + "P";
            }
            else str = str + "-";
        }
    }
    return str;
}

