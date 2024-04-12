#ifndef PROYECTO_ESCRITOR_H
#define PROYECTO_ESCRITOR_H

#include "systemc.h"
#include "fifo.h"
#include "comun.h"

SC_MODULE(escritor) {
public:
    //Conexiones del módulo
    sc_port<read_if_T<sc_uint<8>>> byteIn;
    sc_port<write_if_T<sc_uint<8>>> byteOut;
    sc_port<write_if_T<sc_uint<19>>> writeAddr;

    void escribir();

    SC_CTOR(escritor) {
        cout << "escribir: " << name() << endl;

        SC_THREAD(escribir);
    }
};

#endif


