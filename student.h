#ifndef __STUDENT_H__
#define __STUDENT_H__
#include "WATCardOffice.h"
#include "groupoff.h"
extern MPRNG mprng;

_Task Student {
    Printer &prt;
    // NameServer &nameServer;
    WATCardOffice &cardOffice;
    Groupoff &groupoff;
    unsigned int id;
    unsigned int maxPurchases;

    WATCard::FWATCard giftCard;
    WATCard::FWATCard watCard;
    void createCard();
	void main();
  public:
  //name Server
	Student( Printer & prt, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases );
};

#endif