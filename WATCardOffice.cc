#include "WATCardOffice.h"

void WATCardOffice::Courier::main() {
    Job job = requestWork();

    bank.withdraw(job.id, job.amount);
    job.result->deposit(job.amount);

}

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) :
    prt(prt), bank(bank), numCouriers(numCouriers) {
}

void WATCardOffice::main() {
    for ( ;; ) {
        _Accept( ~WATCardOffice ) return;
        or _Accept( create, trasfer );
    }
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job newJob{1,sid,amount};
    // WATCard::FWATCard newCard;
    // newJob.result = newCard;

    jobList[noJob]= newJob;
    noJob+=1;
    return newJob.result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    Job newJob{2,sid,amount};
    newJob.result = card;

    jobList[noJob]= newJob;
    noJob+=1;
    return newJob.result;
}

WATCardOffice::Job WATCardOffice::requestWork() {
    if ( noJob == 0 ) _Accept( create, transfer );
    noJob -=1;
    return jobList[noJob];

}