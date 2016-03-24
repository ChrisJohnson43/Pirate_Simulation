#define CATCH_CONFIG_MAIN
#include"catch.hpp"
#include"Simulation.hpp"
#include"Ships.hpp"
#include"Ship.hpp"
//#include <iostream>
#include"Ship_Type_Enum.hpp"
#include<forward_list>
//#include<fstream>

const int num_x = 35;
const int num_y = 20;

using namespace std;

SCENARIO("Testing Simulation class."){
    GIVEN("A Simulation object"){
        Simulation sim{40, 50, 25};
        Counts* count_ptr;
        count_ptr = sim.GetCounters();

        REQUIRE(count_ptr->CargosExited() == 0);
        REQUIRE(count_ptr->CargosEntered() == 0);
        REQUIRE(count_ptr->EscortsExited() == 0);
        REQUIRE(count_ptr->EscortsEntered() == 0);
        REQUIRE(count_ptr->PiratesExited() == 0);
        REQUIRE(count_ptr->PiratesEntered() == 0);
        REQUIRE(count_ptr->PiratesDefeated() == 0);
        REQUIRE(count_ptr->CapturedsRescued() == 0);
        REQUIRE(count_ptr->CargosCaptured() == 0);
        
        WHEN("Each enter/exit count is incremented 3 times"){
            for (int i = 0; i < 3; i++){
               count_ptr->IncCargosExited();
               count_ptr->IncCargosEntered();
               count_ptr->IncEscortsExited();
               count_ptr->IncPiratesExited();
               count_ptr->IncEscortsEntered();
               count_ptr->IncPiratesEntered();
            }
            REQUIRE(count_ptr->CargosExited() == 3);
            REQUIRE(count_ptr->CargosEntered() == 3);
            REQUIRE(count_ptr->EscortsExited() == 3);
            REQUIRE(count_ptr->EscortsEntered() ==3);
            REQUIRE(count_ptr->PiratesExited() == 3);
            REQUIRE(count_ptr->PiratesEntered() == 3);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
            THEN("add 5 of each ship.  3 of them should be placed where they will exit next turn"){
                // 3 Pirate ships should be (x, 0)
                sim.AddPirateShip(3, 0);
                sim.AddPirateShip(15, 0);
                sim.AddPirateShip(25, 0);
                sim.AddPirateShip(30, 10);
                sim.AddPirateShip(10, 5);
                // 3 Escort ships should be (0, y)
                sim.AddEscortShip(0, 5);
                sim.AddEscortShip(0, 10);
                sim.AddEscortShip(0, 15);
                sim.AddEscortShip(10, 10);
                sim.AddEscortShip(30, 10);
                // 3 Cargo ships should be (num_x - 1, y)
                sim.AddCargoShip(num_x -1, 0);
                sim.AddCargoShip(num_x-1, 5);
                sim.AddCargoShip(num_x-1, 10);
                sim.AddCargoShip(10, 10);
                sim.AddCargoShip(30, 10);
                // 3 Captured ships should be (x, num_y-1)
                sim.AddCapturedShip(0, num_y-1);
                sim.AddCapturedShip(5, num_y-1);
                sim.AddCapturedShip(10, num_y-1);
                sim.AddCapturedShip(10, 10);
                sim.AddCapturedShip(30, 15);

                // entered counts should now be 8.  
                REQUIRE(count_ptr->CargosExited() == 3);
                REQUIRE(count_ptr->CargosEntered() == 8);
                REQUIRE(count_ptr->EscortsExited() == 3);
                REQUIRE(count_ptr->EscortsEntered() ==8);
                REQUIRE(count_ptr->PiratesExited() == 3);
                REQUIRE(count_ptr->PiratesEntered() == 8);
                REQUIRE(count_ptr->PiratesDefeated() == 0);
                REQUIRE(count_ptr->CapturedsRescued() == 0);
                REQUIRE(count_ptr->CargosCaptured() == 0);  
               
            }
        }
        WHEN("there is 5 of each ship and 3 placed where they should exit.  then call sim::Move()"){
            // 3 Pirate ships should be (x, 0)
            sim.AddPirateShip(3, 0);
            sim.AddPirateShip(15, 0);
            sim.AddPirateShip(25, 0);
            sim.AddPirateShip(30, 10);
            sim.AddPirateShip(10, 5);
            // 3 Escort ships should be (0, y)
            sim.AddEscortShip(0, 5);
            sim.AddEscortShip(0, 10);
            sim.AddEscortShip(0, 15);
            sim.AddEscortShip(10, 10);
            sim.AddEscortShip(30, 10);
            // 3 Cargo ships should be (num_x - 1, y)
            sim.AddCargoShip(num_x -1, 0);
            sim.AddCargoShip(num_x-1, 5);
            sim.AddCargoShip(num_x-1, 10);
            sim.AddCargoShip(10, 10);
            sim.AddCargoShip(30, 10);
            // 3 Captured ships should be (x, num_y-1)
            sim.AddCapturedShip(0, num_y-1);
            sim.AddCapturedShip(5, num_y-1);
            sim.AddCapturedShip(10, num_y-1);
            sim.AddCapturedShip(10, 10);
            sim.AddCapturedShip(30, 15);

            sim.Move();

            // three of each ship should have exited. entered counts should just
            // be 5
            REQUIRE(count_ptr->CargosExited() == 3);
            REQUIRE(count_ptr->CargosEntered() == 5);
            REQUIRE(count_ptr->EscortsExited() == 3);
            REQUIRE(count_ptr->EscortsEntered() ==5);
            REQUIRE(count_ptr->PiratesExited() == 3);
            REQUIRE(count_ptr->PiratesEntered() == 5);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
            THEN("then"){
                ;
            }
        }
        WHEN("a pirate and escort occupy the same point"){
            sim.AddPirateShip(0, 0);
            sim.AddEscortShip(0, 0);
            
            sim.Defeat();

            // 1 pirate and 1 escort have entered and 1 pirate should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 1);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("a pirate is diagonally opposite an escort"){
            sim.AddPirateShip(3, 1);
            sim.AddEscortShip(2, 0);
            
            sim.Defeat();

            // 1 pirate and 1 escort have entered and 1 pirate should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 1);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("a pirate is below an escort"){
            sim.AddPirateShip(5, 1);
            sim.AddEscortShip(5, 0);
            
            sim.Defeat();

            // 1 pirate and 1 escort have entered and 1 pirate should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 1);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("a pirate is above an escort"){
            sim.AddPirateShip(7, 0);
            sim.AddEscortShip(7, 1);
            
            sim.Defeat();

            // 1 pirate and 1 escort have entered and 1 pirate should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 1);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("there is a pirate ship both above and diagonally opposite an escort"){
            sim.AddPirateShip(0, 3);
            sim.AddPirateShip(1, 3);           
            sim.AddEscortShip(1, 4);
            
            sim.Defeat();

            // 2 pirates and 1 escort have entered and 1 pirate should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 2);
            REQUIRE(count_ptr->PiratesDefeated() == 1);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("an escort is surrounded by pirates"){
            sim.AddPirateShip(0, 0);
            sim.AddPirateShip(0, 1);           
            sim.AddPirateShip(0, 2);
            sim.AddPirateShip(1, 0);           
            sim.AddPirateShip(1, 1);
            sim.AddPirateShip(1, 2);           
            sim.AddPirateShip(2, 0);
            sim.AddPirateShip(2, 1);           
            sim.AddPirateShip(2, 2);
            sim.AddEscortShip(1, 1);
            
            sim.Defeat();

            // 1 pirate and 1 escort have entered and 1 pirate should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 9);
            REQUIRE(count_ptr->PiratesDefeated() == 1);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }

        WHEN("an escort is surrounded by pirates that are 2 grids away"){
            sim.AddPirateShip(0, 0);
            sim.AddPirateShip(0, 1);
            sim.AddPirateShip(0, 2);
            sim.AddPirateShip(0, 3);           
            sim.AddPirateShip(0, 4);
            sim.AddPirateShip(1, 4);
            sim.AddPirateShip(2, 4);           
            sim.AddPirateShip(3, 4);
            sim.AddPirateShip(4, 4);           
            sim.AddPirateShip(4, 3);
            sim.AddPirateShip(4, 2);           
            sim.AddPirateShip(4, 1);
            sim.AddPirateShip(4, 0);           
            sim.AddPirateShip(3, 0);
            sim.AddPirateShip(2, 0);           
            sim.AddPirateShip(1, 0);
            sim.AddEscortShip(2, 2);
            
            sim.Defeat();

            // 1 pirate and 1 escort have entered and 1 pirate should have been
            // defeated.
            /*
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 16);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
            */
        }
    }
}

