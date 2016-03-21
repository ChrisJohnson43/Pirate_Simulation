//=======================================================================
// Simulation class.  This class is responsible for interacting with the controller.  It provides the interface for the Model.
//
// Date:    Jan. 21, 2016
//=======================================================================

#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"
#include"Ships.hpp"
#include"Counts.hpp"
#include"Simulation.hpp"

const int num_x = 35;
const int num_y = 20;

Simulation::Simulation(int PIRATE_PROB, int CARGO_PROB, int ESCORT_PROB)
{
    pirate_ships = Ships(Ship_Type::Pirates, PIRATE_PROB, CARGO_PROB, ESCORT_PROB);
    cargo_ships = Ships( Ship_Type::Cargo, PIRATE_PROB, CARGO_PROB, ESCORT_PROB);
    captured_ships = Ships( Ship_Type::Captured,PIRATE_PROB, CARGO_PROB, ESCORT_PROB);
    escort_ships = Ships( Ship_Type::Escort, PIRATE_PROB, CARGO_PROB, ESCORT_PROB);
    Counters = { 
        0,      // cargos_exited 
        0,      // cargos_entered
        0,      // cargos_captured
        0,      // escorts_exited
        0,      // escorts_entered
        0,      // pirates_exited
        0,      // pirates_entered
        0,      // pirates_defeated
        0,      // captureds_rescued
    };
    grid[num_x][num_y];
}

Simulation::~Simulation()
{
}

void Simulation::Move()
{
    pirate_ships.Move();
    cargo_ships.Move();
    captured_ships.Move();
    escort_ships.Move();
}

void Generate()
{
    cargo_ships.Gen();
    pirate_ships.Gen();
    escort_ships.Gen();
}

void Defeat()
{
}

void IncCargosCaptured()
{
    Counters.cargos_captured++;
}

void IncPiratesDefeated()
{
    Counters.pirates_defeated++;
}

void IncCapturedsRescued()
{
    Counters.captureds_rescued++;
}

void IncEscortsExited()
{
    Counters.escorts_exited++;
}

void IncCargosEntered()
{
    Counters.cargos_entered++;
}

void IncPiratesExited()
{
    Counters.pirates_exited++;
}

void IncEscortsEntered()
{
    Counters.escorts_entered++;
}

void IncCargosExited()
{
    Counters.cargos_exited++;
}

void IncPiratesEntered()
{
    Counters.pirates_entered++;
}

void Simulation::Update()
{
    Move();
    Generate();
    Defeat();
    Capture();
    Rescue();
}
    
void Simulation::Reset()
{
    for (int i = 0; i < num_x; i++)
    {
        for (int y = 0; y < num_y; y++)
        {
            grid[i][y] = -1;
        }
    }
}

int[num_x][num_y] Simulation::Grid()
{
    Reset();
    BuildGrid();
    return grid;
}

void Simulation::BuildGrid()
{
}

void Simulation::Capture()
{
}

void Simulation::Rescue()
{
}

const counts* Simulation::Counters() const
{
    return &Counters;
}


