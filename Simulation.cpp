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

const int num_x = 35;
const int num_y = 20;

Simulation::Simulation(int PIRATE_PROB, int CARGO_PROB, int ESCORT_PROB)
    :   pirate_ships{Ship_Type::Pirate, PIRATE_PROB, CARGO_PROB, ESCORT_PROB},
        cargo_ships{ Ship_Type::Cargo, PIRATE_PROB, CARGO_PROB, ESCORT_PROB},
        captured_ships{ Ship_Type::Captured,PIRATE_PROB, CARGO_PROB, ESCORT_PROB},
        escort_ships{ Ship_Type::Escort, PIRATE_PROB, CARGO_PROB, ESCORT_PROB}, 
        pirate_prob(PIRATE_PROB),
        cargo_prob(CARGO_PROB),
        escort_prob(ESCORT_PROB) {}

       /* 
{
    pirate_ships = Ships(Ship_Type::Pirate, PIRATE_PROB, CARGO_PROB, ESCORT_PROB);
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
*/
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
    std::forward_list<Ship>::iterator e_begin = escort_ships.Begin();
    std::forward_list<Ship>::iterator e_end = escort_ships.End();
    std::forward_list<Ship>::iterator p_begin;
    std::forward_list<Ship>::iterator p_end;

    // iterate through escort ships and for each iterate through pirate ships
    // looking for the first adjacent pirate ship to delete.
    for ( ; e_begin != e_end; e_begin++){
        p_begin = pirate_ships.Begin();
        p_end = pirate_ships.End();
        for ( ; p_begin != p_end; p_end++){
            if (p_begin->IsAdjacent(e_begin->Xpos(), e_begin->Ypos())){
                pirate_ships.RemoveShip(p_begin->Value());
                break;
            }
        }
    }
}
    
void IncCargosCaptured()
{
    counters.cargos_captured++;
}

void IncPiratesDefeated()
{
    counters.pirates_defeated++;
}

void IncCapturedsRescued()
{
    counters.captureds_rescued++;
}

void IncEscortsExited()
{
    counters.escorts_exited++;
}

void IncCargosEntered()
{
    counters.cargos_entered++;
}

void IncPiratesExited()
{
    counters.pirates_exited++;
}

void IncEscortsEntered()
{
    counters.escorts_entered++;
}

void IncCargosExited()
{
    counters.cargos_exited++;
}

void IncPiratesEntered()
{
    counters.pirates_entered++;
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
/*
int[num_x][num_y] Simulation::Grid()
{
    Reset();
    BuildGrid();
    return grid;
}

void Simulation::BuildGrid()
{
    // get iterator for each of the 4 forward_list member objects
    std::forward_list<Ship>::iterator p_list_begin = p_ships.Begin();
    std::forward_list<Ship>::iterator p_list_end = p_ships.End();
    std::forward_list<Ship>::iterator car_list_begin = car_ships.Begin();
    std::forward_list<Ship>::iterator car_list_end = car_ships.End();
    std::forward_list<Ship>::iterator e_list_begin = e_ships.Begin();
    std::forward_list<Ship>::iterator e_list_end = e_ships.End();
    std::forward_list<Ship>::iterator cap_list_begin = cap_ships.Begin();
    std::forward_list<Ship>::iterator cap_list_end = cap_ships.End();

    // iterate through each forward_list and add each Ship to the grid[][]
    for ( ; p_list_begin != p_list_end; p_list_begin++;)
    {
        if (grid[p_list_begin.Xpos()][p_list_begin.Ypos()] == -1) { 
            grid[p_list_begin.Xpos()][p_list_begin.Ypos()] = Ship_Type::Pirate;
        }
    }

    // iterate through each forward_list and add each Ship to the grid[][]
    for ( ; car_list_begin != car_list_end; car_list_begin++;)
    {
        if (grid[car_list_begin.Xpos()][car_list_begin.Ypos()] == -1){
            grid[car_list_begin.Xpos()][car_list_begin.Ypos()] = Ship_Type::Cargo;
        }
    }
    // iterate through each forward_list and add each Ship to the grid[][]
    for ( ; e_list_begin != e_list_end; e_list_begin++;)
    {
        if (grid[e_list_begin.Xpos()][e_list_begin.Ypos()] == -1) {
            grid[e_list_begin.Xpos()][e_list_begin.Ypos()] = Ship_Type::Escort;
        }
    }
    // iterate through each forward_list and add each Ship to the grid[][]
    for ( ; cap_list_begin != cap_list_end; cap_list_begin++;)
    {
        if (grid[cap_list_begin.Xpos()][cap_list_begin.Ypos()] == -1){ 
            grid[cap_list_begin.Xpos()][cap_list_begin.Ypos()] = Ship_Type::Captured;
        }
    }
}
*/
void Simulation::Capture()
{
    std::forward_list<Ship>::iterator p_begin = pirate_ships.Begin();
    std::forward_list<Ship>::iterator p_end = pirate_ships.End();
    std::forward_list<Ship>::iterator car_begin; 
    std::forward_list<Ship>::iterator car_end;

    // iterate through pirate ships and for each, iterate through cargo ships
    // looking for the first adjacent cargo ship to capture. Captured cargo
    // ships will be removed and in its place a captured ship will be created.
    // The capturing pirate ship will have its Ship.captured flag set.  
    for ( ; p_begin != p_end; p_begin++){
       car_begin = cargo_ships.Begin();
       car_end = cargo_ships.End();
       for ( ; car_begin != car_end; car_end++){
            if (car_begin->IsAdjacent(p_begin->Xpos(), p_begin->Ypos())){
                p_begin->SetCaptured(true);
                // create new captured ship in the same position as the cargo
                // ship
                captured_ships.AddCapturedShip(car_begin->Xpos(), car_begin->Ypos());
                // delete the captured cargo ship
                cargo_ships.RemoveShip(car_begin->Value());
                break;
            }
        }
    }
    // delete all pirate ships that captured on this turn
    pirate_ships.RemoveCaptured();
}

void Simulation::Rescue()
{
    std::forward_list<Ship>::iterator e_begin = escort_ships.Begin();
    std::forward_list<Ship>::iterator e_end = escort_ships.End();
    std::forward_list<Ship>::iterator cap_begin;
    std::forward_list<Ship>::iterator cap_end;

    // iterate through escort ships and for each iterate through captured ships
    // looking for the first adjacent captured ship to delete.
    for ( ; e_begin != e_end; e_begin++){
        cap_begin = captured_ships.Begin();
        cap_end = captured_ships.End();
        for ( ; cap_begin != cap_end; cap_end++){
            if (cap_begin->IsAdjacent(e_begin->Xpos(), e_begin->Ypos())){
                // cap_begin points to an adjacent captured.  create cargo in
                // its place.  then remove captured
                cargo_ships.AddCargoShip(cap_begin->Xpos(), cap_begin->Ypos());
                captured_ships.RemoveShip(cap_begin->Value());
                break;
            }
        }
    }
}

const Counts* Simulation::GetCounters() const
{
    return &counters;
}


