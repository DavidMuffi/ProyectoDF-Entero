#ifndef CONVBYTE_h
#define CONVBYTE_h

#include<stdio.h>

#include "comun.h"
#include "systemc.h"

SC_MODULE(convByte) {
public:

	sc_port<read_if_T<Ftype>>  halfIn;
	sc_port<write_if_T<sc_uint<8>>>  byteOut;


	void convertir() {
		Ftype floatingP;
		sc_uint<8> trueValue;

		while (true) {
			halfIn->read(floatingP);

			trueValue = (sc_uint<8>)floatingP.toFloat(); //convertimos de Ftype a float y de float a sc_uint<8>

			//acotamos los resultados
			if (trueValue < 0) {
				trueValue = 0;
			}

			if (trueValue > 255) {
				trueValue = 255;
			}

			byteOut->write(trueValue);
		}

	}



	SC_CTOR(convByte) {
		cout << "conByte : " << name() << endl;
		SC_THREAD(convertir);
	}

private:
	unsigned short myStream;

};

#endif
