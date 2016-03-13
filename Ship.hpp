





#ifndef SHIP_H
#define SHIP_H 

#include"Ship_Type_Enum.hpp"


class Ship
{
public:
    Ship (int x, int y, int val, Ship_Type::Enum ship_type);
    virtual ~Ship ();
    void move(){};
    int Xpos() {};
    int Ypos() {};
    void SetType(Ship_Type::Enum ship_type);
private:
    int x_pos;
    int y_pos;
    int d_x;                        // Change of the x-cord per time unit
    int d_y;                        // Change of the y-cord per time unit
    Ship_Type::Enum type;           // The ship type {Captured, Cargo, Escort, Pirate}
    int value;                      // Unique value (eg. nth cargoe ship created) used for Ships::Remove(value)
};




#endif /* ifndef SHIP_H */  
