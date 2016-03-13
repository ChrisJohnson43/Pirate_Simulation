//=======================================================================
// File:  Ships class.  This is the container for all active ships.
//
// Date:    Jan. 21, 2016
//=======================================================================

#ifndef SHIPS_H
#define SHIPS_H 

#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"

class Ships
{
public:
    Ships::Ships(double prob, Ship_Type::Enum type)
    virtual ~Ships ();
    void Move();            // iterates through forward_list and calls Move() for each ship
    void Gen();               // gen** methods handles random ship generation for each turn
    void RemoveShip(int val); // removes ship.value == val from ship_list 

private:
    Ship_Type::Enum type;           // holds the type of ship the forward_list contains
    forward_list<Ship> ship_list;  // forward_list instead of vector for the constant time delete
    double probability;       // 0 <= x < 1; value used in gen method
    static constexpr int num_x{35}; // number of columns in our grid (used to gen a spawned ships location)
    static constexpr int num_y{20};     // number of rows in our grid (used to gen a spawned ships location)
    void AddCargoShip(Ship ship);        // adds cargo ship
    void AddPirateShip(Ship ship);       // adds pirate ship
    void AddEscortShip(Ship ship);       // adds escort ship
    void AddCapturedShip(Ship ship);     // adds captured ship

};






#endif /* ifndef SHIPS_H */
