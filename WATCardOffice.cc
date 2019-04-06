#include "WATCardOffice.h"
#include <iostream>
using namespace std;

WATCardOffice::Courier::Courier(Printer &prt, Bank &bank, WATCardOffice &office, unsigned int id) : 
    prt(prt), bank(bank), office(office),id(id) {}

void WATCardOffice::Courier::main() {
    prt.print(Printer::Kind::Courier,id, 'S');
    for ( ;; ) {
        cout << id << " waiting" <<endl;
        try {
            Job *job = office.requestWork();
        } catch ( Quit & ) {
            cout << id  << " wait dead" <<endl;
            _Accept ( ~Courier ) {
                prt.print( Printer::Kind::Courier, id, 'F' );
                return;
            }
        }
        cout << id << " get job" << endl;
        prt.print( rinter::Kind::Courier, id, 't', job->id, job->amount );
        bank.withdraw( job->id, job->amount );

        if (mprng(1, 6) == 1){
            delete job->realCard; //current WATCard is deleted
            job->result.exception( new Lost );
            prt.print(Printer::Kind::Courier, id, 'L', job->id);
        } else {
            job->realCard->deposit( job->amount );
            job->result.delivery( job->realCard );
            prt.print( Printer::Kind::Courier, id, 'T', job->id, job->amount );
        }
        delete job;
    }//for

}

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) :
    prt( prt ), bank( bank ), numCouriers( numCouriers ) {
        courierPool = new Courier*[numCouriers];  
    for ( unsigned int c= 0; c < numCouriers; c++ ) {
        courierPool[c] = new Courier( prt, bank, *this, c );
    }
}

void WATCardOffice::main() {
    prt.print( Printer::Kind::WATCardOffice, 'S' );
    for ( ;; ) {
        _Accept ( requestWork ) {
            _Accept( ~WATCardOffice ) {
                cout << "destructor" <<endl;
                offWork = true;

                clk.signalBlock();  //signal the one requesting work 
                for ( unsigned int c= 0; c < numCouriers-1; c++ ) {
                    try {
                        _Accept( requestWork );   //let the rest exit requestwork busy wait
                    } catch ( uMutexFailure::RendezvousFailure & ){} //try
                }

                for ( unsigned int c= 0; c < numCouriers; c++ ) {
                    delete courierPool[c];
                }

                delete []courierPool;
                prt.print( Printer::Kind::WATCardOffice, 'F' );
                return;
            } or _When ( noJob == 0 && wantJob != 0 ) _Accept ( create, transfer) {
                clk.signalBlock();
            }
        }
    }
}


WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job *newJob = new Job( sid, amount, new WATCard() );
    jobList[noJob]= newJob;
    noJob+=1;
    prt.print( Printer::Kind::WATCardOffice, 'C', sid, amount );
    return newJob->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    Job *newJob = new Job( sid, amount, card );
    // newJob->result.delivery(card);
    jobList[noJob] = newJob;
    noJob+=1;
    prt.print( Printer::Kind::WATCardOffice, 'T', sid, amount );
    cout << "transfer" <<endl;
    return newJob->result;
}

WATCardOffice::Job * WATCardOffice::requestWork() {
    if ( offWork ) throw Quit();
    wantJob ++;
    cout << "want job " << wantJob << endl;
    if (noJob == 0) clk.wait();
    cout << "wake up "  << wantJob << endl;
    if ( offWork ) throw Quit();
    wantJob--;
    noJob--;
    prt.print( Printer::Kind::WATCardOffice, 'W' );
    return jobList[noJob];

}