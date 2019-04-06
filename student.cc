#include "student.h"
#include <iostream>
using namespace std;

void Student::createCard() {
    watCard = cardOffice.create( id, 5 );
    for(;;) {
        try {
            _Select(watCard){
                assert( watCard()->getBalance() == 5 );
                break;
            }
        } _Catch ( WATCardOffice::Lost &) {
            watCard.reset();
            prt.print( Printer::Kind::Student, id,'L' );
            watCard = cardOffice.create(id, 5);
        }
    }
}

void Student::main() {
    unsigned int noPurchase = mprng( 1,maxPurchases );
    unsigned int flavour = mprng( 1, 3 );
    prt.print( Printer::Kind::Student, id, 'S', flavour, noPurchase );
    
    giftCard = groupoff.giftCard();
    watCard = cardOffice.create( id, 5 );
    // VendingMachine *machine = nameServer.getMachine( id );
    //prt.print(Printer::Kind::Student, id, 'V', machine->getId());
    // unsigned int cost = machine->cost();


    for ( unsigned int k = 0; k < noPurchase; k++ ) {
        yield( mprng( 1, 10 ) );
        int cardType; // 0 is giftCard and 1 is watCard
        for (;;) {
            try {
                _Select ( giftCard ) {  //giftCard is available
                    assert(giftCard()->getBalance() != 0);
                    cardType = 0;
                    // machine->buy( (VendingMachine::Flavours) falvour, watCard);
                    prt.print( Printer::Kind::Student, id, 'G', flavour, giftCard()->getBalance() );
                    
                    giftCard.reset();
                    break;
                } or _Select ( watCard ) {  //watCard is available
                    cardType = 1;
                    // machine->buy( (VendingMachine::Flavours) falvour, watCard);
                    prt.print( Printer::Kind::Student, id, 'B', flavour, watCard()->getBalance() );
                    break;
                }
            } _Catch ( VendingMachine::Free & ){
                if ( cardType ) {
                    prt.print( Printer::Kind::Student, id, 'A', flavour, watCard()->getBalance() );
                } else {
                    prt.print( Printer::Kind::Student, id, 'a', flavour, giftCard()->getBalance() );
                }
                yield (4);

            } _Catch ( VendingMachine:: Funds & ) {
                try {
                    watCard = cardOffice.transfer( id, cost + 5, watCard() );
                } _Catch ( WATCardOffice::Lost & ) {
                    watCard.reset();
                    prt.print( Printer::Kind::Student, id, 'L' );
                    watCard = cardOffice.create( id, 5 );
                }
            } _Catch ( VendingMachine:: Stock & ) {
                // machine = nameServer.getMachine(id);
            }
        }
        // } _Else {
        //     try {
        //         if ( watCard()->getBalance() < cost ) {
        //             watCard = cardOffice.transfer(id, (cost - watCard()->getBalance()), watCard());   
        //         }
        //         for(;;) {
        //             _Select ( watCard ) {
        //                 assert (watCard()->getBalance() >= cost);
        //                 cout <<  k << " paid" <<endl;
        //                 watCard()->withdraw( cost );
        //                 prt.print(Printer::Kind::Student, id, 'B', watCard()->getBalance());
        //                 break;
        //             }
        //         }
        //     } _Catch ( WATCardOffice::Lost &) {
        //         watCard.reset();
        //         prt.print(Printer::Kind::Student, id, 'L');
        //         createCard();
        //         watCard()->withdraw(cost);
        //         prt.print(Printer::Kind::Student, id, 'B', watCard()->getBalance());
        //     }
        // } 
    }
    delete watCard();
    delete giftCard();
    prt.print( Printer::Kind::Student, id, 'F' );
}

Student::Student( Printer & prt,  WATCardOffice & cardOffice, Groupoff & groupoff,
		          unsigned int id, unsigned int maxPurchases ) : 
    prt( prt ), cardOffice( cardOffice ), groupoff( groupoff ), id (id ), maxPurchases( maxPurchases ) {}

