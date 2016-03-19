#include"catch.hpp"
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

TEST_CASE( "Ship objects can be added and removed from Ships classes", "[Ships]")
{
    SECTION( "a Ships class for each type add ten ships to each one" )
    {
        Ships p_ships = Ships(P_PROB, Ship_Type::Pirate);
        Ships car_ships = Ships(CAR_PROB, Ship_Type::Cargo);
        Ships e_ships = Ships(E_PROB, Ship_Type::Escort);
        Ships cap_ships = Ships(0, Ship_Type::Captured);

        for (int i =0; i < 10; i++)
        {
            Ship ship= Ship(i, 0, i, Ship_Type::Pirate);
            Ship car= Ship(0, i, i, Ship_Type::Cargo);
            Ship esc= Ship(num_x - 1, i, i, Ship_Type::Escort);
            Ship cap= Ship(i, num_y - 1, i, Ship_Type::Captured);

            p_ships.AddPirateShip(ship);
            car_ships.AddCargoShip(car);
            e_ships.AddEscortShip(esc);
            cap_ships.AddCapturedShip(cap);
        }     
       
        
        const std::forward_list<Ship> pirate_list = p_ships.GetList();
        const std::forward_list<Ship> cargo_list = car_ships.GetList();
        const std::forward_list<Ship> escort_list = e_ships.GetList();
        const std::forward_list<Ship> captured_list = cap_ships.GetList();

        int i = 0;
        for (auto it = pirate_list.begin(); it != pirate_list.end(); it++)
        {
            Ship ship = *it;
            REQUIRE( ship.Xpos() == i);
            REQUIRE( ship.Ypos() == num_y - 1); 
            i++;
        }

        
        i = 0;
        for (auto it = cargo_list.begin(); it != cargo_list.end(); it++)
        {
            Ship ship = *it;
            REQUIRE( ship.Xpos() == 0);
            REQUIRE( ship.Ypos() == i); 
            i++;
        }

        i = 0;
        for (auto it = escort_list.begin(); it != escort_list.end(); it++)
        {
            Ship ship = *it;
            REQUIRE( ship.Xpos() == num_x - 1);
            REQUIRE( ship.Ypos() == i); 
            i++;
        }
 
        i = 0;
        for (auto it = captured_list.begin(); it != captured_list.end(); it++)
        {
            Ship ship = *it;
            REQUIRE( ship.Xpos() == i);
            REQUIRE( ship.Ypos() == 0); 
            i++;
        }
 
        p_ships.Move();
        car_ships.Move();
        e_ships.Move();
        cap_ships.Move();

        i = 0;
        for (auto it = pirate_list.begin(); it != pirate_list.end(); it++)
        {
            Ship ship = *it;
            REQUIRE( ship.Xpos() == i);
            REQUIRE( ship.Ypos() == num_y - 2); 
            i++;
        }

        
        i = 0;
        for (auto it = cargo_list.begin(); it != cargo_list.end(); it++)
        {
            Ship ship = *it;
            REQUIRE( ship.Xpos() == 1);
            REQUIRE( ship.Ypos() == i); 
            i++;
        }

        i = 0;
        for (auto it = escort_list.begin(); it != escort_list.end(); it++)
        {
            Ship ship = *it;
            REQUIRE( ship.Xpos() == num_x - 3);
            REQUIRE( ship.Ypos() == i); 
            i++;
        }
 
        i = 0;
        for (auto it = captured_list.begin(); it != captured_list.end(); it++)
        {
            Ship ship = *it;
            REQUIRE( ship.Xpos() == i);
            REQUIRE( ship.Ypos() == 1); 
            i++;
        }
 
    }
}
