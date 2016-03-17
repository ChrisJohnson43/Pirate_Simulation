//=======================================================================
// File:  Ships class.  This is the container for all active ships.
//
// Date:    Feb. 21, 2016
//=======================================================================

#ifndef SHIPS_H
#define SHIPS_H 

#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"

class Ships
{
public:
    Ships(int prob, Ship_Type::Enum ship_type);
    virtual ~Ships ();
    void Move();            // iterates through forward_list and calls Ship::Move() for each ship
    void Gen();               // Ship::Gen() methods handles random ship generation for each turn.  It will call Ships::Add*() after determining whether or not a Ship is generated and if so where it is generated. 
    void RemoveShip(int val); // removes ship.value == val from ship_list 
    // The following two methods will either be called by Simulation::Rescue(),
    // Simulation::Capture(), or Ships::Gen().
    void AddCargoShip(Ship ship);        // adds cargo ship
    void AddCapturedShip(Ship ship);     // adds captured ship
    void AddPirateShip(Ship ship);       // adds pirate ship
    void AddEscortShip(Ship ship);       // adds escort ship
    const std::forward_list<Ship>* Iterator();  // return ship_list iterator
  
private:
    static const int num_x;
    static const int num_y;    // num of vertical cells
    static int num_cargos;      // num of cargos generated for unique ID (Ship::value)
    static int num_pirates;     // num of pirates generated for unique ID (Ship::value)
    static int num_escorts;     // num of escorts generated for unique ID
    static int num_captureds;    // num of captureds created for unique ID
    Ship_Type::Enum type;           // holds the type of ship the forward_list contains
    std::forward_list<Ship> ship_list;  // forward_list instead of vector for the constant time delete
    int probability;       // value used in gen method
   // the following four methods inc num_{cargos, pirates, escorts, captureds}
    void IncNumPirates();
    void IncNumCargos();
    void IncNumCaptureds();
    void IncNumEscorts();
    bool IsOutOfBounds(Ship* ship_ptr);
};






#endif /* ifndef SHIPS_H */
