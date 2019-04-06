#include "groupoff.h"
#include <iostream>
using namespace std;

void Groupoff::main() {
    prt.print( Printer::Kind::Groupoff, 'S' );
    for( ;;) {
        _Accept( ~Groupoff ) {
            prt.print( Printer::Kind::Groupoff, 'F' );
            delete []giftCardList;
            return;
        } _Else {
            _When (cur < numStudents) _Accept ( giftCard ) {
                yield( groupoffDelay );
                WATCard *card =  new WATCard();
                card->deposit( sodaCost );
                curCard.delivery( card ) ;
                prt.print( Printer::Kind::Groupoff, 'D', sodaCost );
            }
        }
    }
}

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ):
    prt( prt ), numStudents( numStudents ), sodaCost( sodaCost ), groupoffDelay( groupoffDelay ) {
    //    giftCardList = new WATCard::FWATCard[numStudents];
    //    for ( unsigned int g =0; g < numStudents; g++ ) {
    //        giftCardList[g] = WATCard::FWATCard(); 
    //    }
    }

WATCard::FWATCard Groupoff::giftCard() {
    curCard = WATCard::FWATCard();
    return curCard;
}