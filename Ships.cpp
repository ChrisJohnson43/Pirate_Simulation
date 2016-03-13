//=======================================================================
// File:  Ships class.  This is the container for all active ships.
//
// Date:    Jan. 21, 2016
//=======================================================================

#include"Ship_Type_Enum.hpp"
#include"Ships.hpp"
#include"Ship.hpp"


void Ships::Move() {
    for (auto it = ship_list.begin(); it != ship_list.end(); it++)
        it->Move();
}

void Ships::Gen() {
      
}

Ships::Ships(double prob, Ship_Type::Enum type){
    probability = prob;
    ship_type = type;
    std::forward_list<Ship> ship_list;

}

void Ships::AddCargoShip(Ship ship) {
    ship_list.push_front (ship);
}
   
void Ships::AddPirateShip(Ship ship) {
    ship_list.push_front (ship);
}

void Ships::AddEscortShip(Ship ship) {
    ship_list.push_front (ship);
}
 
void Ships::AddCapturedShip(Ship ship) {
    ship_list.push_front (ship);
}

void Ships::RemoveShip(int val) {
    Ship* ship_ptr;
    // the following for loop will initialize two iterators (it and prev_it) to
    // iterate through forward_list::ship_list looking for Ship with value equal
    // to val.  The prev_it is neccessary to pass to the
    // forward_list::erase_after().
    for (auto it = ship_list.begin(), auto prev_it = ship_list.before_begin(); it != ship_list.end(); prev_it++, it++) {
        if (it->value == val) {
            ship_list.erase_after(prev_it);
            break;
}
