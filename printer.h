#ifndef __PRINTER_H__
#define __PRINTER_H__

_Monitor Printer {
    unsigned int numStudents; //6
    unsigned int numVendingMachines;//6+numStudents
    unsigned int numCouriers;
    unsigned int total;
    unsigned int length = 0;
    struct info {bool used = false; char state; int value1 = -1; int value2 = -1;};
    info * buffer;
    void init();
    void flush(unsigned int p, bool forced);
    unsigned int position(unsigned int p, unsigned id);
  public:
	enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
	Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
  ~Printer();
	void print( Kind kind, char state );
	void print( Kind kind, char state, int value1 );
	void print( Kind kind, char state, int value1, int value2 );
	void print( Kind kind, unsigned int lid, char state );
	void print( Kind kind, unsigned int lid, char state, int value1 );
	void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};
#endif