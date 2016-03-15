//=======================================================================
// File:  Ship class.  The Ship class is used for all four types of Ships.
//
// Date:    Feb. 21, 2016
//=======================================================================

#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"
#include<iostream>

void Ship::Move() {
    x_pos += d_x; 
    y_pos += d_y;
}

Ship::Ship(int x, int y, int val, Ship_Type::Enum ship_type) 
{
    x_pos = x;
    y_pos = y;
    value = val;
    type = ship_type;
    d_x = 0;
    d_y = 0;

    if (type == Ship_Type::Pirate)  d_y = -1;
    else if ( type == Ship_Type::Cargo) d_x = 1;
    else if ( type == Ship_Type::Escort) d_x = -2;
    else 
        d_y = 1;
       // std::cout << "Error!  Invalid Ship_type::Enum ship_type passed to Ship::Ship()" << std::endl;
}

int Ship::Xpos() {
    return x_pos;
}

int Ship::Ypos() 
{
    return y_pos;
}

void Ship::SetType(Ship_Type::Enum ship_type) {
   type = ship_type; 
   switch (type)
   {
       case Ship_Type::Pirate:{ 
                        d_x = -1;
                        d_y = 0; 
                        break;
                   }
       case Ship_Type::Cargo:{    d_x = 1;
                        d_y = 0;
                        break;
                   }
       case Ship_Type::Captured:{   d_x = 1;
                          d_y = 0;
                          break;
                      }
       case Ship_Type::Escort:{   d_x = -2;
                        d_y = 0;
                        break;   
                    }
        default: break;
   }
}

Ship_Type::Enum Ship::Type() 
{
    return type;
}

Ship::~Ship()
{
}
