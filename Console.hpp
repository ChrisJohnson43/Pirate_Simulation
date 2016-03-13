//=======================================================================
// This is the console class.  It will only be used for testing.  It will have the same interface as the Graphical
// Display.
//
// Date:    Jan. 21, 2016
//=======================================================================


class Console
{
    private:
        static constexpr char pirate_sym;   // character that notates a Pirate ship on the display
        static constexpr char cargo_sym;
        static constexpr char captured_sym;
        static constexpr char escort_sym;
        Controller* control_ref;        // pointer to the Controller object
        void DisplayCounts();           // method used to output counts to console
        void DisplayMap();          // method used to output the map to console
        char UserIO();                                      // method used to get user input {[S]tart, [[P]ause, [E]nd,
                                                                   // s[I]ngle step}.
    public:
        Console(Controller& control_ref);   // constructor that recieves the address of the Controller object.
        ~Console();
}