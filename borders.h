#ifndef BORDERS_H
#define BORDERS_H

#include"comun.h"

#include "systemc.h"
#include "fifo.h"

SC_MODULE (borders) {
public:
sc_port<read_if_T<Ftype>>  dataIn0, dataIn1, dataIn2;
sc_port<write_if_T<Ftype>>  dataOut00, dataOut01, dataOut02;
sc_port<write_if_T<Ftype>>  dataOut10, dataOut11, dataOut12;
sc_port<write_if_T<Ftype>>  dataOut20, dataOut21, dataOut22;

SC_HAS_PROCESS(borders);

void procBorders();

  borders(sc_module_name name_, int _anchura, int _altura) : sc_module(name_) {
    cout<<"borders: "<<name()<<endl;

	anchura = _anchura;
	altura = _altura;

    SC_THREAD(procBorders);
  } 


private:
    Ftype data[2][3];
	unsigned short anchura, altura;
}; 

#endif