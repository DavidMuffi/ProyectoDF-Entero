#ifndef buffer2x16b_H
#define buffer2x16b_H

#include"comun.h"

#include "systemc.h"
#include "fifo.h"

SC_MODULE (buffer2x16b) {
public:
sc_port<read_if_T<Ftype>>  dataIn;
sc_port<write_if_T<Ftype>>  dataOut0, dataOut1, dataOut2;


SC_HAS_PROCESS(buffer2x16b);

void procesar();

	buffer2x16b(sc_module_name name_, int _anchura) : sc_module(name_) {
    cout<<"buffer2x16b: "<<name()<<endl;

	anchura = _anchura;

	mem0 = new Ftype[_anchura];
	mem1 = new Ftype[_anchura];

	 
    SC_THREAD(procesar);
  } 

~buffer2x16b(){
	delete mem0;
	delete mem1;
}

private:
	Ftype *mem0;		
	Ftype *mem1;
	bool turno;
	unsigned short rdPt, wrPt, anchura;
}; 

#endif