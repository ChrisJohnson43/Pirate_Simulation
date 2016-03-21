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
#include<iostream>            

// The following ints are the percentage chance that a ship of that type will be
// spwaned each time period
int PIRATE_PROB = 40;
int CARGO_PROB = 50;
int ESCORT_PROB = 25;

int Ships::num_cargos = 0;
int Ships::num_escorts=0;
int Ships::num_pirates=0;
int Ships::num_captureds=0;

void Ships::Move() {
    Ship* ship_ptr;
    for (auto it = ship_list.begin(); it != ship_list.end(); it++)
    {
        it->Move();
        ship_ptr = &(*it);
        if (IsOutOfBounds(ship_ptr))
        {
            RemoveShip(it->Value()); 
        }
    }
}

bool Ships::IsOutOfBounds(Ship* ship_ptr)
{
    switch (type) {
        case Ship_Type::Escort:
            if (ship_ptr->Xpos() < 0) return true;
            break;
        case Ship_Type::Pirate:
            if (ship_ptr->Ypos() < 0) return true;
            break;
        case Ship_Type::Cargo:
            if (ship_ptr->Xpos() > (num_x - 1)) return true;
            break;
        case Ship_Type::Captured:
            if (ship_ptr->Ypos() > (num_y - 1)) return true;
            break;
    }
    return false;
}

void Ships::Gen() {
    std::cout<<"Ship_Type: " <<type<<std::endl;
    int x_grid;
    int y_grid;
    switch (type) {
        case Ship_Type::Captured:
            break;
        case Ship_Type::Cargo:
            if (IsShipSpawned(CARGO_PROB)) 
            {
                x_grid = 0;
                y_grid = GetNode(num_y);
                Ship ship = Ship(x_grid, y_grid, num_cargos, type ); 
                AddCargoShip(ship);
            }
            break;
         case Ship_Type::Escort:
            if (IsShipSpawned(ESCORT_PROB)) 
            {
                x_grid = num_x - 1;
                y_grid = GetNode(num_y);
                Ship ship = Ship(x_grid, y_grid, num_escorts, type); 
                AddEscortShip(ship);                              
            }
            break;
         case Ship_Type::Pirate:
            if (IsShipSpawned(PIRATE_PROB)) 
            {
                x_grid = GetNode(num_x);
                y_grid = num_y - 1;
                Ship ship = Ship(x_grid, y_grid, num_pirates, type); 
                AddPirateShip(ship);               
            }
            break;
            
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
    num_cargos++;
}
   
void Ships::AddPirateShip(Ship ship) {
    ship_list.push_front (ship);
    num_pirates++;
}

void Ships::AddEscortShip(Ship ship) {
    ship_list.push_front (ship);
    num_escorts++;
}
 
void Ships::AddCapturedShip(Ship ship) {
    ship_list.push_front (ship);
    num_captureds++;
}

void Ships::RemoveShip(int val) {
    Ship* ship_ptr;
    auto prev_it = ship_list.before_begin();
    for (auto it = ship_list.begin(); it != ship_list.end(); it++) {
        if (it->Value() == val) {
            it = ship_list.erase_after(prev_it);
            break;
        }
        prev_it++;
    }
}

const std::forward_list<Ship>  Ships::GetList() const 
{
    return ship_list;
}

std::forward_list<Ship>::iterator Ships::Begin() 
{
    return ship_list.begin();
}

std::forward_list<Ship>::iterator Ships::End() 
{
    return ship_list.end();
}




        
