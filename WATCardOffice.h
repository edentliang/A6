#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__
#include "printer.h"
#include "bank.h"
#include "WATCard.h"
#include "MPRNG.h"
extern MPRNG mprng;

_Task WATCardOffice {
	Printer &prt;
	Bank &bank;
	unsigned int numCouriers;


	struct Job {							// marshalled arguments and return future
		unsigned int id;
		unsigned int amount;
		WATCard *realCard;
		WATCard::FWATCard result;			// return future
		Job(unsigned int id, unsigned int amount, WATCard *realCard) : 
			 id(id), amount(amount), realCard(realCard) {}
	};
	
	_Task Courier {
		Printer &prt;
		Bank &bank;
		WATCardOffice &office;
		unsigned int id;
		void main();
	  public:
		Courier(Printer & prt, Bank & bank, WATCardOffice & office, unsigned int id);
	};					// communicates with bank

	Courier **courierPool;
	uCondition clk;
	Job *jobList[1000];
	_Event Quit {};
	int noJob = 0;
	int wantJob = 0;
	bool offWork = false;
	void main();
  public:
	_Event Lost {};							// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	WATCard::FWATCard create( unsigned int sid, unsigned int amount );
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card );
	Job * requestWork();
};

#endif