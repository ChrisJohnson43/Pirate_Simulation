//=======================================================================
// File:  Ship class.  The Ship class is used for all four types of Ships.
//
// Date:    Feb. 21, 2016
//=======================================================================

#define CATCH_CONFIG_MAIN
#include "/Users/chrisjohnson43/Pirate_Simulation/Catch/single_include/catch.hpp"
#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"

TEST_CASE( "Ship objects are tested", "[Ship]")
{
    
    Ship pirate_ship = Ship(0, 0, 0, Ship_Type::Pirate);
    Ship cargo_ship = Ship(0, 0, 1, Ship_Type::Cargo);
    Ship captured_ship = Ship(0, 0, 2, Ship_Type::Captured);
    Ship escort_ship = Ship(0, 0, 3, Ship_Type::Escort);

    REQUIRE( pirate_ship.Xpos() == 0 );
    REQUIRE( pirate_ship.Ypos() == 0 );
    
    SECTION( "Testing the Ship::Move() method" ) 
    {
        pirate_ship.Move();
        cargo_ship.Move();
        captured_ship.Move();
        escort_ship.Move();

        REQUIRE( pirate_ship.Xpos() == 0);
        REQUIRE( pirate_ship.Ypos() == -1);

        REQUIRE( cargo_ship.Xpos() == 1);
        REQUIRE( cargo_ship.Ypos() == 0);
        
        REQUIRE( captured_ship.Xpos() == 0);
        REQUIRE( captured_ship.Ypos() == -1);

        REQUIRE( escort_ship.Xpos() == 0);
        REQUIRE( escort_ship.Ypos() == -1);
    }
    SECTION( "Testing Ship::SetType()" ) 
    {
        pirate_ship.SetType(Ship_Type::Cargo);
        cargo_ship.SetType(Ship_Type::Pirate);
        captured_ship.SetType(Ship_Type::Escort);
        escort_ship.SetType(Ship_Type::Captured);

        REQUIRE( pirate_ship.Type() == Ship_Type::Cargo );
        REQUIRE( escort_ship.Type() == Ship_Type::Captured );
        REQUIRE( cargo_ship.Type() == Ship_Type::Pirate );
        REQUIRE( captured_ship.Type() == Ship_Type::Escort );
    }        
}

