#include"catch.hpp"
#include"Ships.hpp"
#include"Ship.hpp"
#include <iostream>
#include"Ship_Type_Enum.hpp"

using namespace std;

int P_PROB = 40;
int CAR_PROB = 50;
int E_PROB = 25;

SCENARIO( "Ship objects can be added and removed from Ships classes", "[Ships]")
{
    GIVEN( "a Ships class for each type add ten ships to each one" )
    {
        Ships p_ships {P_PROB, Ship_Type::Pirate};
        Ships car_ships {CAR_PROB, Ship_Type::Cargo};
        Ships e_ships {E_PROB, Ship_Type::Escort};
        Ships cap_ships {0, Ship_Type::Captured};

        for (int i =0; i < 10; i++)
        {
            Ship ship {i, 0, i, Ship_Type::Pirate};
            Ship car {0, i, i, Ship_Type::Cargo};
            Ship esc {num_x - 1, i, i, Ship_Type::Escort};
            Ship cap {i, num_y - 1, i, Ship_Type::Captured};

            p_ships.AddPirateShip(ship);
            car_ships.AddCargoShip(car);
            e_ships.AddEscortShip(esc);
            cap_ships.AddCapturedShip(cap);
        }     
        
        REQUIRE( p_ships.Size() == 10);
        REQUIRE ( car_ships.Size() == 10);
        REQUIRE( e_ships.Size() == 10);
        REQUIRE( cap_ships.Size() == 10);
        
