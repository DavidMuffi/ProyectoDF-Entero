#include "escritor.h"


void escritor::escribir() {

    sc_uint<8> dIn;
    sc_uint<19> memDir;

    memDir = 0;


    while (true) {
        //Se pasa el dato y se pasa la dir de memoria
        byteIn->read(dIn);
        byteOut->write(dIn);
        writeAddr->write(memDir);
        memDir++;
        if (memDir.value() > WIDTH * HEIGHT - 1) {
            memDir = 0;
        }
    }
}


