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
                sim.AddCargoShip(num_x -1, 0, true);
                sim.AddCargoShip(num_x-1, 5, true);
                sim.AddCargoShip(num_x-1, 10, true);
                sim.AddCargoShip(10, 10, true);
                sim.AddCargoShip(30, 10, true);
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

                count_ptr = sim.GetCounters();

                REQUIRE(count_ptr->Cargos() == 5);
                REQUIRE(count_ptr->Pirates() == 5);
                REQUIRE(count_ptr->Captureds() == 5);
                REQUIRE(count_ptr->Escorts() == 5);
               
                
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
            sim.AddCargoShip(num_x -1, 0, true);
            sim.AddCargoShip(num_x-1, 5, true);
            sim.AddCargoShip(num_x-1, 10, true);
            sim.AddCargoShip(10, 10, true);
            sim.AddCargoShip(30, 10, true);
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

            count_ptr = sim.GetCounters();

//            REQUIRE(count_ptr->Cargos() == 2);
            REQUIRE(count_ptr->Pirates() == 2);
            REQUIRE(count_ptr->Captureds() == 2);
            REQUIRE(count_ptr->Escorts() == 2);
           
            // 3-D int array to check the Simulation::Grid()
            Simulation::gridXxYx4 grid = sim.Grid();            
            
            REQUIRE(grid[8][10][Ship_Type::Escort] == 1);
            REQUIRE(grid[28][10][Ship_Type::Escort] == 1);
            REQUIRE(grid[10][4][Ship_Type::Pirate] == 1);
            REQUIRE(grid[30][9][Ship_Type::Pirate] == 1);
            REQUIRE(grid[10][11][Ship_Type::Captured] == 1);
            REQUIRE(grid[30][16][Ship_Type::Captured] == 1);
            REQUIRE(grid[11][10][Ship_Type::Cargo] == 1);
            REQUIRE(grid[31][10][Ship_Type::Cargo] == 1);
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
            //sim.AddEscortShip(3, 3);
            
            sim.Defeat();

            // 1 pirate and 1 escort have entered and 1 pirate should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 16);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("an escort is surrounded by pirates that are 2 grids away and another escort is adjacent to the first"){
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
            sim.AddEscortShip(3, 3);
            
            sim.Defeat();

            // 1 pirate and 1 escort have entered and 1 pirate should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==2);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 16);
            REQUIRE(count_ptr->PiratesDefeated() == 1);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }


        //==================================Test Capture()=====================
        WHEN("a pirate and cargo occupy the same point"){
            sim.AddPirateShip(0, 0);
            sim.AddCargoShip(0, 0, true);
            
            sim.Capture();

            // 1 pirate and 1 cargo have entered and 1 cargo should have been
            // captured. 
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 1);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==0);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 1);  
        }
        WHEN("a pirate is diagonally opposite a cargo"){
            sim.AddPirateShip(3, 1);
            sim.AddCargoShip(2, 0, true);
            
            sim.Capture();

            // 1 pirate and 1 cargo have entered and 1 cargo should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 1);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==0);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 1);  
        }
        WHEN("a pirate is below a cargo"){
            sim.AddPirateShip(5, 1);
            sim.AddCargoShip(5, 0, true);
            
            sim.Capture();

            // 1 pirate and 1 cargo have entered and 1 cargo should have been
            // captured.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 1);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==0);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 1);  
        }
        WHEN("a pirate is above a cargo"){
            sim.AddPirateShip(7, 0);
            sim.AddCargoShip(7, 1, true);
            
            sim.Capture();

            // 1 pirate and 1 cargo have entered and 1 cargo should have been
            // captured.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 1);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==0);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 1);  
        }
        WHEN("there is a cargo ship both above and diagonally opposite a pirate"){
            sim.AddCargoShip(0, 3, true);
            sim.AddCargoShip(1, 3, true);           
            sim.AddPirateShip(1, 4);
            
            sim.Capture();

            // 2 cargos and 1 pirate have entered and 1 cargo should have been
            // captured.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 2);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==0);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 1);  
        }
        WHEN("a pirate is surrounded by cargos"){
            sim.AddCargoShip(0, 0, true);
            sim.AddCargoShip(0, 1, true);           
            sim.AddCargoShip(0, 2, true);
            sim.AddCargoShip(1, 0, true);
            sim.AddCargoShip(1, 1, true);
            sim.AddCargoShip(1, 2, true);
            sim.AddCargoShip(2, 0, true);
            sim.AddCargoShip(2, 1, true);
            sim.AddCargoShip(2, 2, true);
            sim.AddPirateShip(1, 1);
            
            sim.Capture();

            // 1 pirate and 9 cargos have entered and 1 cargo should have been
            // captured.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 9);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==0);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 1);  
        }

        WHEN("a pirate is surrounded by cargos that are 2 grids away"){
            sim.AddCargoShip(0, 0, true);
            sim.AddCargoShip(0, 1, true);
            sim.AddCargoShip(0, 2, true);
            sim.AddCargoShip(0, 3, true);
            sim.AddCargoShip(0, 4, true);
            sim.AddCargoShip(1, 4, true);
            sim.AddCargoShip(2, 4, true);
            sim.AddCargoShip(3, 4, true);
            sim.AddCargoShip(4, 4, true);
            sim.AddCargoShip(4, 3, true);
            sim.AddCargoShip(4, 2, true);
            sim.AddCargoShip(4, 1, true);
            sim.AddCargoShip(4, 0, true);
            sim.AddCargoShip(3, 0, true);
            sim.AddCargoShip(2, 0, true);
            sim.AddCargoShip(1, 0, true);
            sim.AddPirateShip(2, 2);
            
            sim.Capture();

            // 1 pirate and 16 cargos have entered and 0 cargo should have been
            // captured.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 16);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==0);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 1);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("an pirate is surrounded by cargos that are 2 grids away and another pirate is adjacent to the first"){
            sim.AddCargoShip(0, 0, true);
            sim.AddCargoShip(0, 1, true);
            sim.AddCargoShip(0, 2, true);
            sim.AddCargoShip(0, 3, true);
            sim.AddCargoShip(0, 4, true);
            sim.AddCargoShip(1, 4, true);
            sim.AddCargoShip(2, 4, true);
            sim.AddCargoShip(3, 4, true);
            sim.AddCargoShip(4, 4, true);
            sim.AddCargoShip(4, 3, true);
            sim.AddCargoShip(4, 2, true);         
            sim.AddCargoShip(4, 1, true);
            sim.AddCargoShip(4, 0, true);
            sim.AddCargoShip(3, 0, true);
            sim.AddCargoShip(2, 0, true);
            sim.AddCargoShip(1, 0, true);
            sim.AddPirateShip(2, 2);
            sim.AddPirateShip(3, 3);
            
            sim.Capture();

            // 2 pirate and 16 cargos have entered and 1 cargo should have been
            // captured.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 16);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==0);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 2);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 1);  
        }



        //==================================Test Rescue()=====================
        WHEN("a captured and escort occupy the same point"){
            sim.AddCapturedShip(0, 0);
            sim.AddEscortShip(0, 0);
            
            sim.Rescue();

            // 1 escort and 1 captured have entered and 1 captured should have been
            // rescued. 
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 0);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 1);
            REQUIRE(count_ptr->CargosCaptured() == 0);  

            THEN("Simulation::Move() is called"){
                sim.Move();
                Simulation::gridXxYx4 grid = sim.Grid();            

                REQUIRE(grid[1][0][Ship_Type::Cargo] == 1);
            }
        }
        WHEN("a escort is diagonally opposite a captured"){
            sim.AddEscortShip(3, 1);
            sim.AddCapturedShip(2, 0);
            
            sim.Rescue();

            // 1 escort and 1 captured have entered and 1 captured should have been
            // defeated.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 0);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 1);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("a escort is below a captured"){
            sim.AddEscortShip(5, 1);
            sim.AddCapturedShip(5, 0);
            
            sim.Rescue();

            // 1 escort and 1 captured have entered and 1 captured should have been
            // rescued.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 0);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 1);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("a escort is above a captured"){
            sim.AddEscortShip(7, 0);
            sim.AddCapturedShip(7, 1);
            
            sim.Rescue();

            // 1 escort and 1 captured have entered and 1 captured should have been
            // rescued.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 0);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 1);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("there is a captured ship both above and diagonally opposite a escort"){
            sim.AddCapturedShip(0, 3);
            sim.AddCapturedShip(1, 3);           
            sim.AddEscortShip(1, 4);
            
            sim.Rescue();

            // 2 captured and 1 escort have entered and 1 captured should have been
            // rescued.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 0);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 1);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("a escort is surrounded by captured"){
            sim.AddCapturedShip(0, 0);
            sim.AddCapturedShip(0, 1);           
            sim.AddCapturedShip(0, 2);
            sim.AddCapturedShip(1, 0);           
            sim.AddCapturedShip(1, 1);
            sim.AddCapturedShip(1, 2);           
            sim.AddCapturedShip(2, 0);
            sim.AddCapturedShip(2, 1);           
            sim.AddCapturedShip(2, 2);
            sim.AddEscortShip(1, 1);
            
            sim.Rescue();

            // 1 escort and 9 captured have entered and 1 captured should have been
            // rescued.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 0);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 1);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }

        WHEN("a escort is surrounded by captured that are 2 grids away"){
            sim.AddCapturedShip(0, 0);
            sim.AddCapturedShip(0, 1);
            sim.AddCapturedShip(0, 2);
            sim.AddCapturedShip(0, 3);           
            sim.AddCapturedShip(0, 4);
            sim.AddCapturedShip(1, 4);
            sim.AddCapturedShip(2, 4);           
            sim.AddCapturedShip(3, 4);
            sim.AddCapturedShip(4, 4);           
            sim.AddCapturedShip(4, 3);
            sim.AddCapturedShip(4, 2);           
            sim.AddCapturedShip(4, 1);
            sim.AddCapturedShip(4, 0);           
            sim.AddCapturedShip(3, 0);
            sim.AddCapturedShip(2, 0);           
            sim.AddCapturedShip(1, 0);
            sim.AddEscortShip(2, 2);
            
            sim.Rescue();

            // 1 escort and 16 captured have entered and 0 captured should have been
            // rescued.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==1);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 0);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 0);
            REQUIRE(count_ptr->CargosCaptured() == 0);  
        }
        WHEN("an escort is surrounded by captured that are 2 grids away and another escort is adjacent to the first"){
            sim.AddCapturedShip(0, 0);
            sim.AddCapturedShip(0, 1);
            sim.AddCapturedShip(0, 2);
            sim.AddCapturedShip(0, 3);           
            sim.AddCapturedShip(0, 4);
            sim.AddCapturedShip(1, 4);
            sim.AddCapturedShip(2, 4);           
            sim.AddCapturedShip(3, 4);
            sim.AddCapturedShip(4, 4);           
            sim.AddCapturedShip(4, 3);
            sim.AddCapturedShip(4, 2);           
            sim.AddCapturedShip(4, 1);
            sim.AddCapturedShip(4, 0);           
            sim.AddCapturedShip(3, 0);
            sim.AddCapturedShip(2, 0);           
            sim.AddCapturedShip(1, 0);
            sim.AddEscortShip(2, 2);
            sim.AddEscortShip(3, 3);
            
            sim.Rescue();

            // 2 escort and 16 captured have entered and 1 captured should have been
            // rescued.
            REQUIRE(count_ptr->CargosExited() == 0);
            REQUIRE(count_ptr->CargosEntered() == 0);
            REQUIRE(count_ptr->EscortsExited() == 0);
            REQUIRE(count_ptr->EscortsEntered() ==2);
            REQUIRE(count_ptr->PiratesExited() == 0);
            REQUIRE(count_ptr->PiratesEntered() == 0);
            REQUIRE(count_ptr->PiratesDefeated() == 0);
            REQUIRE(count_ptr->CapturedsRescued() == 1);
            REQUIRE(count_ptr->CargosCaptured() == 0);  

            
        }
        WHEN("a pirate is one grid directly to the west of an Escort"){
            sim.AddPirateShip(33, 16);
            sim.AddEscortShip(34, 16);

            sim.Defeat();

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
    }
}

