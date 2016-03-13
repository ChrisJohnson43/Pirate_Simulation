//=======================================================================
// Simulation class.  This class is responsible for interacting with the controller.  It provides the interface for the Model.
//
// Date:    Jan. 21, 2016
//=======================================================================

#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"
#include"Ships.hpp"
#include"Counts.hpp"
#include"Simulation.hpp"


Simulation::Simulation(Controller& control_ref) {
    this.control_ref = control_ref;
    pirate_ships = Ships(0.4, Ship_Type::Pirates);
    cargo_ships = Ships(0.5, Ship_Type::Cargo);
    captured_ships = Ships(0.0, Ship_Type::Captured);
    escort_ships = Ships(0.25, Ship_Type::Escort);

