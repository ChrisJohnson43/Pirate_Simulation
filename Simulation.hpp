//=======================================================================
// Simulation class.  This class is responsible for interacting with the controller.  It provides the interface
// for the Model.
//
// Date:    Jan. 21, 2016
//=======================================================================


class Simulation
{
  private:
    counts Counters;        // Struct that holds the 9 counts
    static const int num_x; // number of columns in our grid (used to gen a spawned ships location)
    static const int num_y;     // number of rows in our grid (used to gen a spawned ships location)
    int pirate_prob;
    int cargo_prob;
    int escort_prob;
    int grid[num_x][num_y];          // dynamically allocated 2-D array that is initialized to -1's
    // The following 5 methods execute 1 time unit of the simulation and should be called in order by
    // Simulation::Update();
    void Move();            // Moves all active ships
    void Generate();        // Randomly generates ships for Cargos, Pirates, Escorts
    void Defeat();          // Determines if any Defeat actions occur
    void Capture();         // Determines if any Capture actions occur
    void Rescue();          // Determines if any Rescue actions occur
    void IncCargosCaptured();   // increment cargos_captured
    void IncPiratesDefeated();  // increment pirates_defeated
    void IncCapturedsRescued(); // increment captureds_rescued
    
  public:
    Simulation(int PIRATE_PROB, int CARGO_PROB, int ESCORT_PROB);
    virtual ~Simulation();
    const counts* Counters() const;     // returns reference to the Counters struct
    int[num_x][num_y] Grid();     // return pointer to grid of Map (location of all the ships)
    void Update();          // Runs one time unit of Simulation
    void IncEscortsExited();    // increment escorts_exited
    void IncCargosExited();     // increment cargos_exited
    void IncCargosEntered();    // increment cargos_entered
    void IncPiratesExited();    // increment pirates_exited
    void IncEscortsEntered();   // increment escorts_entered
    void IncCargosExited();     // increment cargos_exited
    void IncPiratesEntered();   // increment pirates_entered   
    void Reset();		// clears 2-D grid
}
