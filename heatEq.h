
#ifndef PROYECTO_CHS_HEATEQ_H
#define PROYECTO_CHS_HEATEQ_H
#include "systemc.h"
#include "fifo.h"
#include "half.h"
#include "comun.h"

SC_MODULE(heatEq){
public:
    sc_port<read_if_T<Ftype>> dataIn00, dataIn01, dataIn02;
    sc_port<read_if_T<Ftype>> dataIn10, dataIn11, dataIn12;
    sc_port<read_if_T<Ftype>> dataIn20, dataIn21, dataIn22;

    sc_port<write_if_T<Ftype>> dataOut;

    void calculo();

    SC_CTOR(heatEq){
        cout << "heatEq: " << name() << endl;

        SC_THREAD(calculo);
    }
private:
    Ftype dx=0.01,dy=0.01,a=0.5;
    Ftype dt=(dx*dx*dy*dy)/(dx*dx+dy*dy);
    Ftype adtidx2 = a*dt/(dx*dx);
    Ftype adtidy2 = a*dt/(dy*dy);
};
#endif //PROYECTO_CHS_HEATEQ_H
