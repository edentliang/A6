#ifndef __PARENT_H__
#define __PARENT_H__
extern MPRNG mprng;

_Task Parent {
    Printer &prt;
    Bank &bank;
    unsigned int numStudents;
    unsigned int parentalDealy;
	void main();
  public:
	Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
};