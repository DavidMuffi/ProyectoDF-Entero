#include "mem.h"


void mem::lectura() {

	sc_uint<19> dir;

	while (true) {
		readAddr->read(dir);
		dataOut->write(memData[dir]);
		//printf("%03d ", memData[dir]);
	}
}


void mem::escritura() {

	sc_uint<8> dato;
	sc_uint<19> dir;

	while (true) {
		writeAddr->read(dir);
		dataIn->read(dato);
		memData[dir] = (unsigned char)dato.to_uint();
//		printf("%03d ", dato.to_uint());
	}
}

