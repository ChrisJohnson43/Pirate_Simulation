#include"Ships.hpp"
#include"Ship.hpp"
#include <iostream>
#include"Ship_Type_Enum.hpp"
#include<forward_list>

int P_PROB = 40;
int CAR_PROB = 50;
int E_PROB = 25;
int num_x = 35;
int num_y=20;

int main()
{
    Ships p_ships = Ships(P_PROB, Ship_Type::Pirate);
    Ships car_ships = Ships(CAR_PROB, Ship_Type::Cargo);
    Ships e_ships = Ships(E_PROB, Ship_Type::Escort);
    Ships cap_ships = Ships(0, Ship_Type::Captured);

    for (int i =0; i < 10; i++)
    {
        Ship ship= Ship(i, num_y - 1, i, Ship_Type::Pirate);
        Ship car= Ship(0, i, i, Ship_Type::Cargo);
        Ship esc= Ship(num_x - 1, i, i, Ship_Type::Escort);
        Ship cap= Ship(i, num_y - 1, i, Ship_Type::Captured);

        p_ships.AddPirateShip(ship);
        car_ships.AddCargoShip(car);
        e_ships.AddEscortShip(esc);
        cap_ships.AddCapturedShip(cap);
    }     
   
    std::cout << "Print out all pirate ship (x, y)" << std::endl;
    
    const std::forward_list<Ship> pirate_list = p_ships.GetList();
    const std::forward_list<Ship> cargo_list = car_ships.GetList();
    const std::forward_list<Ship> escort_list = e_ships.GetList();
    const std::forward_list<Ship> captured_list = cap_ships.GetList();

    int i = 1;
    std::cout << "Pirate Ships: "<< std::endl;
    for (auto it = pirate_list.begin(); it != pirate_list.end(); it++)
    {
        Ship ship = *it;
        std::cout <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << std::endl;
        i++;
    }

    p_ships.Move();

    std::cout << "Move the pirate ships and print again." << std::endl;

    const std::forward_list<Ship> p_list = p_ships.GetList(); 
    i = 1;
    std::cout << "Pirate Ships: "<< std::endl;
    for (auto it = p_list.begin(); it != p_list.end(); it++)
    {
        Ship ship = *it;
        std::cout <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << std::endl;
        i++;
    }

}
