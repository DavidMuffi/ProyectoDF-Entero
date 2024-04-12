#ifndef CONVHALF_H
#define CONVHALF_H

#include"comun.h"
#include "systemc.h"
#include "fifo.h"

SC_MODULE(convHalf) {
public:
	sc_port<read_if_T<sc_uint<8>>> dataIn;
	sc_port<write_if_T<Ftype>> dataOut;

	void conversionHalf();

	SC_CTOR(convHalf) {

		SC_THREAD(conversionHalf);
	}
};

#endif