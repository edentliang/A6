#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__
#include "printer.h"
#include "WATCard.h"

_Task Groupoff {
    Printer &prt;
    unsigned int numStudents;
    unsigned int sodaCost;
    unsigned int groupoffDelay;

    // WATCard::FWATCard * giftCardList;
    WATCard::FWATCard curCard;
    unsigned int total =0;
    unsigned int cur = 0;
    void main();

  public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	WATCard::FWATCard giftCard();
};

#endif