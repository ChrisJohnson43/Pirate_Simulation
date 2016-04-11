//=======================================================================
// This is the console class.  It will only be used for testing.  It will have the same interface as the Graphical
// Display.
//
// Date:    Jan. 21, 2016
//=======================================================================
#include<string>
#include"Ship_Type_Enum.hpp"        // enum State

class Controller;
class Counts;

typedef int (&grid3D)[35][20][4];

class Console
{
    private:
        static const char pirate_sym;   // character that notates a Pirate ship on the display
        static const char cargo_sym;
        static const char captured_sym;
        static const char escort_sym;
        std::string count_file;              // name of the file used to write the counts every step
        std::string grid_file;               // name of the file used to write the grid every time step
        std::string StringCounts(Counts* counts) const;      // method used to output counts to console
        std::string StringMap(grid3D& grid, int x, int y) const;                             // generates grid in the form of a string
        std::string Map(grid3D& grid, int x, int y) const;

    public:
        Console();   // constructor that recieves the address of the Controller object.
        virtual ~Console();
        State::Enum UserIO();                         // returns the user command
        int RunSteps();                         // returns the number of steps the user wants to simulate
        void Output(Counts* counts, grid3D& grid, int x, int y);                          // outputs the counts and grid to Console::count_file and Console::grid_file
        int X();                                    // user input number of x coordinates
        int Y();                                    // user input number of y coordinates
        void OutputCounts(Counts* counts, grid3D& grid, int x, int y) const;
};
