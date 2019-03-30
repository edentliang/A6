#include "parent.h"

void Parent::main() {
    for( ;; ) {
        _Accept(~Parent) {
            return;
        } _Else {
            yield(parentalDealy);
            unsigned int amount = mprng(1,3);
            unsigned int id = mprng(numStudents-1);
            bank.deposit(id, amount);
        }
    }
}

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) :
    prt(prt), bank(bank), numStudents(numStudents), parentalDealy(parentalDealy) {}
