#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

_Task WATCardOffice {
	Printer &prt;
	Bank &bank;
	unsigned int numCouriers;


	struct Job {							// marshalled arguments and return future
		int type;								// 1 is create and 2 is transfer
		unsigned int id;
		unsigned int amount;
		WATCard::FWATCard result;			// return future
		Job( int type, unsigned int id, unsigned int amount ) : type( type ), id(id), amount(amount) {}
	};
	
	_Task Courier { 
		void main();
		public:
	};					// communicates with bank

	Courier courierPool[1000];
	Job jobList[1000];
	int noJob = 0;
	

	void main();
  public:
	_Event Lost {};							// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	WATCard::FWATCard create( unsigned int sid, unsigned int amount );
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card );
	Job * requestWork();
};