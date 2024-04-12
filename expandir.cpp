#include "expandir.h"



void expandir::expansion() {

	Ftype dIn;

	//fifo_T<Ftype> *buffer;

	//buffer = new fifo_T<Ftype>("Buffer", WIDTH);

	Ftype buffer[WIDTH];

	int i = 0;
	int j;

	while (true) {
		dataIn->read(dIn);

		// escritura
		dataOut->write(dIn);
		dataOut->write(dIn); // OJO! emite el resultado

		buffer[i] = dIn;
		

		if (i == WIDTH - 1) {
			for (j = 0; j < WIDTH; j++) {
				
				dataOut->write(buffer[j]);
				dataOut->write(buffer[j]);

				buffer[j] = (unsigned short)0;
			}
			i = 0;
		}
		else {
			i++;
		}
	}
}


