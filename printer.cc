#include "printer.h"
#include <iostream>
using namespace std;


Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
    numStudents( numStudents ), numVendingMachines( numVendingMachines ), numCouriers( numCouriers ) {
        total = 6 + numStudents + numVendingMachines + numCouriers;
        buffer = new info[ total ];
        cout << "Parent" << "\t" << "Gropoff" << "WATOff" << "\t" << "Names" << "\t" << "Truck" << "\t" << "Plant" << "\t";
        for ( unsigned int s = 0; s < numStudents; s++ ) {
            cout << "Stud" << s << "\t";
        }
        for ( unsigned int s = 0; s < numVendingMachines; s++ ) {
            cout << "Mach" << s << "\t";
        }

        for ( unsigned int s = 0; s < numCouriers-1; s++ ) {
            cout << "Cour" << s << "\t";
        }

        cout << "Cour" << ( numCouriers-1 )<< endl;

        for ( unsigned int s = 0; s < total; s++ ) {
            if ( s == 0 ) {
                cout << "*******";
            } else {
                cout << "\t*******";
            }
        }
        cout << "\n";
    }

Printer::~Printer() {
    flush(0,true);
    cout << "***********************"<<endl;
    delete [] buffer;
}
void Printer::init() {
    for ( unsigned int i=0; i < total; i++ ) {
        buffer[i] = info();
    }
}
void Printer::flush( unsigned int p, bool forced = false ) {
    if ( buffer[p].used || forced ) {
        for ( unsigned int i = 0; i < total; i++ ) {
            if ( length == 0 ) break;
            if ( i != 0 ) cout << "\t"; 
            if ( buffer[i].used ) {
                cout << buffer[i].state;
                if ( buffer[i].value1 != -1 ) cout << buffer[i].value1;
                if ( buffer[i].value2 != -1 ) cout << "," <<buffer[i].value2;
                length--;
            }
        }
        cout << "\n";
        init();
    }
    buffer[p].used = true;
    length++;
}

unsigned int Printer::position( unsigned int p, unsigned id ) {
    if ( p >= 6 ) {
        switch (p) {
            case 6: return ( 6 + id ;
            case 7: return ( 6 + numStudents + id );
            case 8: return ( 6 + numStudents + numVendingMachines + id );
            default: cerr<< "exc" <<endl; return -1;
        } 
    } else {
        return p;
    }
}
void Printer::print( Kind kind, char state ) {
    unsigned int pos = position(kind, 0);
    flush(pos);
    buffer[pos].state = state;

}
void Printer::print( Kind kind, char state, int value1 ) {
    unsigned int pos = position( kind, 0 );
    flush(pos);
    buffer[pos].state = state;
    buffer[pos].value1 = value1;
    assert (value1 != -1);

}
void Printer::print( Kind kind, char state, int value1, int value2 ){
    unsigned int pos = position( kind, 0 );
    flush(pos);
    buffer[pos].state = state;
    buffer[pos].value1 = value1;
    buffer[pos].value2 = value2;
    assert(value1 != -1);
    assert(value2 != -1);
    
}
void Printer::print( Kind kind, unsigned int lid, char state ) {
    unsigned int pos = position( kind, lid );
    flush(pos);
    buffer[pos].state = state;
}
void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
    unsigned int pos = position( kind, lid );
    flush(pos);
    buffer[pos].state = state;
    buffer[pos].value1 = value1;
    assert (value1 != -1);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
    unsigned int pos = position( kind, lid );
    flush(pos);
    buffer[pos].state = state;
    buffer[pos].value1 = value1;
    buffer[pos].value2 = value2;
    assert(value1 != -1);
    assert(value2 != -1);
}