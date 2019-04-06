#include "parent.h"

void Parent::main() {
    prt.print( Printer::Kind::Parent, 'S' );
    for( ;; ) {
        _Accept(~Parent) {
            prt.print( Printer::Kind::Parent, 'F') ;
            return;
        } _Else {
            yield( parentalDelay );
            unsigned int amount = mprng( 1, 3 );
            unsigned int id = mprng( numStudents-1 );
            prt.print( Printer::Kind::Parent, 'D', id, amount );
            bank.deposit( id, amount );
        }
    }
}

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) :
    prt( prt ), bank( bank ), numStudents( numStudents ), parentalDelay( parentalDelay ) {}
