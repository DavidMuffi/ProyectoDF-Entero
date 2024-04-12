#ifndef TRADUCIR_H
#define TRADUCIR_H


#include "systemc.h"
#include "fifo.h"
#include "comun.h"

SC_MODULE (traducir) {
public:
sc_port<read_if_T<sc_uint<8>>>  dataIn;
sc_port<write_if_T<sc_uint<24>>>  dataOut;   

void traduccion();

  SC_CTOR(traducir) {
    cout<<"traducir: "<<name()<<endl;

    SC_THREAD(traduccion);
  } 

}; 

#endif