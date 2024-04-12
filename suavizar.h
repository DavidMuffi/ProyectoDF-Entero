#pragma once

#include "systemc.h"
#include "comun.h"
#include "fifo.h"

SC_MODULE(suavizar) {
public:
	sc_port<read_if_T<Ftype>>  dataIn00, dataIn01, dataIn02;
	sc_port<read_if_T<Ftype>>  dataIn10, dataIn11, dataIn12;
	sc_port<read_if_T<Ftype>>  dataIn20, dataIn21, dataIn22;

	sc_port<write_if_T<Ftype>>  dataOut;

	SC_CTOR(suavizar) {
		SC_THREAD(run);
	}

	void run();
};