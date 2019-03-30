#include "student.h"


void Student::main() {
    
    
}

Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
		          unsigned int id, unsigned int maxPurchases ) : 
    prt(prt), nameServer(nameServer), cardOffice(ardOffice), groupoff(groupoff),id(id), maxPurchase(maxPurchase) {}

