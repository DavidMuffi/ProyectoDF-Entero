#ifndef TRADUCIR_H
#define TRADUCIR_H


#include "systemc.h"
#include "fifo.h"
#include "comun.h"

SC_MODULE(expandir) {
public:
    sc_port<read_if_T<Ftype>>  dataIn;   // OJO! completa el tamaño del interfaz de entrada
    sc_port<write_if_T<Ftype>>  dataOut;

    void expansion();

    SC_CTOR(expandir) {
        cout << "expandir: " << name() << endl;

        SC_THREAD(expansion);  // OJO! qué falta aquí?
    }

};

#endif