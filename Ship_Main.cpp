#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"
#include <iostream>

int main()
{
    
    Ship pirate_ship = Ship(0, 0, 0, Ship_Type::Pirate);
    Ship cargo_ship = Ship(0, 0, 1, Ship_Type::Cargo);
    Ship captured_ship = Ship(0, 0, 2, Ship_Type::Captured);
    Ship escort_ship = Ship(0, 0, 3, Ship_Type::Escort);
    Ship ship = Ship(10, 10, 1, Ship_Type::Pirate);

    int x = pirate_ship.Xpos();
    int y = pirate_ship.Ypos();

    std::cout << "Pirate Ship X pos: "<< x << "\n";
    std::cout << "Pirate Ship Y pos: "<< y << "\n";

    pirate_ship.Move();

    x = pirate_ship.Xpos();
    y = pirate_ship.Ypos();
    
    bool pred = ship < pirate_ship;

    std::cout << "Pirate Ship X pos: "<< x << "\n";
    std::cout << "Pirate Ship Y pos: "<< y << "\n";
    std::cout << "Return (0, 0) < (10, 10): "<<pred<< std::endl;
}
