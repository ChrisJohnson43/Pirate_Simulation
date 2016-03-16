//=======================================================================
// File:  Ships class.  This is the container for all active ships.
//
// Date:    March 15, 2016
//=======================================================================

#include<forward_list>
#include"Ship_Type_Enum.hpp"
#include"Ships.hpp"
#include"Ship.hpp"
#include"RandomEvent.hpp"

// The following ints are the percentage chance that a ship of that type will be
// spwaned each time period
int PIRATE_PROB = 40;
int CARGO_PROB = 50;
int ESCORT_PROB = 25;

void Ships::Move() {
    for (auto it = ship_list.begin(); it != ship_list.end(); it++)
        it->Move();
}

void Ships::Gen() {
    int x_grid;
    int y_grid;
    switch (type) {
        case Ship_Type::Escort:
            if (IsShipSpawned(ESCORT_PROB)) 
            {
                x_grid = num_x - 1;
                y_grid = GetNode(num_y);
                Ship ship = Ship(x_grid, y_grid, num_escorts, Ship_Type::Escort); 
                AddEscortShip(ship);                              
                break;
            }
        case Ship_Type::Pirate:
            if (IsShipSpawned(PIRATE_PROB)) 
            {
                x_grid = GetNode(num_x);
                y_grid = 0;
                Ship ship = Ship(x_grid, y_grid, num_pirates, Ship_Type::Pirate); 
                AddPirateShip(ship);               
                break;  
            }
        case Ship_Type::Cargo:
            if (IsShipSpawned(CARGO_PROB)) 
            {
                x_grid = 0;
                y_grid = GetNode(num_y);
                Ship ship = Ship(x_grid, y_grid, num_cargos, Ship_Type::Cargo); 
                AddCargoShip(ship);
                break;
            }
    }
}

Ships::Ships(int prob, Ship_Type::Enum ship_type){
    probability = prob;
    type = ship_type;
    std::forward_list<Ship> ship_list;
}

Ships::~Ships()
{
}

void Ships::AddCargoShip(Ship ship) {
    ship_list.push_front (ship);
    IncNumCargos();
}
   
void Ships::AddPirateShip(Ship ship) {
    ship_list.push_front (ship);
    IncNumPirates();
}

void Ships::AddEscortShip(Ship ship) {
    ship_list.push_front (ship);
    IncNumEscorts();
}
 
void Ships::AddCapturedShip(Ship ship) {
    ship_list.push_front (ship);
    IncNumCaptureds();
}

void Ships::RemoveShip(int val) {
    Ship* ship_ptr;
    auto prev_it = ship_list.before_begin();
    for (auto it = ship_list.begin(); it != ship_list.end(); it++) {
        if (it->Value() == val) {
            ship_list.erase_after(prev_it);
            break;
        }
        prev_it++;
    }
}

void Ships::IncNumPirates()
{
    num_pirates++;
    return;
}

void Ships::IncNumCargos()
{
    num_cargos++;
    return;
}

void Ships::IncNumCaptureds()
{
    num_captureds++;
    return;
}

void Ships::IncNumEscorts()
{
    num_escorts++;
    return;
}
