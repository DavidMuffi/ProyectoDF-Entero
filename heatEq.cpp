#include "heatEq.h"

void heatEq::calculo() {
    Ftype resultado, retorno;
    Ftype value00, value01, value02, value10, value11, value12, value20, value21, value22;
    while (true) {
        dataIn00->read(value00);
        dataIn01->read(value01);
        dataIn02->read(value02);
        dataIn10->read(value10);
        dataIn11->read(value11);
        dataIn12->read(value12);
        dataIn20->read(value20);
        dataIn21->read(value21);
        dataIn22->read(value22);

        resultado = value11 + adtidx2 * (value21 - (value11 * 2.0) + value01) + adtidy2 * (value10 - (value11 * 2.0) + value12);
        dataOut->write(resultado);
        dataOut->write(retorno);
    }
}