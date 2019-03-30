#include "bank.h"

Bank::Bank ( unsigned int numStudents ) : numStudents(numStudents) {
    for ( unsigned int k = 0; k < numStudents; k++ ) {  //initilize accounts
        accounts[k] = 0;
    } //for
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    accounts[id] += amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    //for loop When 
    while ( amount > accounts[id] ) _Accept( deposit ); //the courier waits until enough deposit
    accounts[id] -= amounts;
}