#include <iostream>
#include <sstream>
#include "student.h"
#include "parent.h"
#include "config.h"
using namespace std;

MPRNG mprng{};

bool convert( int & val, char * buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    string temp;
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	! ( ss >> temp );				// characters after conversion all blank ?
} // convert

int main( int argc, char *argv[] ) {
    int seed = getpid();
    const char *configFile = "soda.config";
    try {
        switch ( argc ) {
            case 3:
                if ( strcmp( argv[2], "d" ) != 0 ) {	// default ?
		            if ( ! convert( seed, argv[2] ) || seed <= 0 ) throw 1; // invalid ?
	            } // if
	            // FALL THROUGH
            case 2:
                configFile = argv[1];
	            // FALL THROUGH
            case 1: break;
            default: throw 1;
            }
    } catch ( ... ) {
        cerr << "Usage: " << argv[0]
             << "soda [ config-file [ Seed (> 0)] ]" << endl;
        exit(EXIT_FAILURE); // TERMINATE
    }// try
    ConfigParms config{};
    processConfigFile( configFile, config );
    // unsigned int sodaCost = 3;             // MSRP per bottle
    // unsigned int numStudents = 4;          // number of students to create
    // unsigned int maxPurchases = 5;         // maximum number of bottles a student purchases
    // unsigned int numVendingMachines = 2;   // number of vending machines
    // unsigned int maxStockPerFlavour;   // maximum number of bottles of each flavour stocked
    // unsigned int maxShippedPerFlavour; // number of bottles of each flavour in a shipment
    // unsigned int timeBetweenShipments; // length of time between shipment pickup
    // unsigned int groupoffDelay = 2;        // length of time between initializing gift cards
    // unsigned int parentalDelay = 1;        // length of time between cash deposits
    // unsigned int numCouriers = 2;

    unsigned int processors = 1;
    mprng.set_seed( getpid() );
    uProcessor p[processors - 1]; // number of kernel threads
    Printer prt( config.numStudents, config.numVendingMachines, config.numCouriers );
    Bank bank( config.numStudents );

    Parent parent( prt, bank, config.numStudents, config.parentalDelay );
    WATCardOffice office(  prt, bank, config.numCouriers );
    Groupoff groupoff( prt, config.numStudents, config.sodaCost, config.groupoffDelay );

    Student *studentList[config.numStudents];

    for ( unsigned int s=0; s < config.numStudents; s++ ) {
        studentList[s] = new Student( prt, office, groupoff, s, config.maxPurchases );
    }
    for ( unsigned int s=0; s < config.numStudents; s++ ) {
        delete studentList[s];
    }
}


