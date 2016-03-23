


#ifndef COUNTS_H
#define COUNTS_H 

struct Counts {
    unsigned int cargos_exited;
    unsigned int cargos_entered;
    unsigned int escorts_exited;
    unsigned int escorts_entered;
    unsigned int pirates_exited;
    unsigned int pirates_entered;
    unsigned int pirates_defeated;
    unsigned int captureds_rescued;
    unsigned int cargos_captured; 
    Counts() : cargos_exited(0),
                cargos_entered(0),
                escorts_entered(0),
                escorts_exited(0),
                pirates_exited(0),
                pirates_entered(0),
                pirates_defeated(0),
                captureds_rescued(0),
                cargos_captured(0) {}
};



#endif /* ifndef COUNTS_H */ 
