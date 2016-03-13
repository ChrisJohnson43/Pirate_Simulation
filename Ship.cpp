



#include"Ship_Type_Enum"
#include"Ship.hpp"


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

    if (type == Pirate)  d_y = -1;
    else if ( type == Cargo) d_x = 1;
    else if ( type == Escort) d_x = -2;
    else 
        std::cout << "Error!  Invalid Ship_type::Enum ship_type passed to Ship::Ship()" << std::endl;
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
}
