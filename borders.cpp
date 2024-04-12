#include "borders.h"


void borders::procBorders() {

	Ftype d0, d1, d2;
	Ftype prev[2][3];

	for (int j = 0; j < anchura; ++j) {	// basura y no produce salida
		dataIn0->read(d0);
		dataIn1->read(d1);
		dataIn2->read(d2);
	}

	// ahora aquí
	for (int j = 0; j < 1; ++j) {
		dataIn0->read(d0);			dataIn1->read(d1);			dataIn2->read(d2);
		prev[1][0] = prev[0][0];	prev[1][1] = prev[0][1];	prev[1][2] = prev[0][2];
		prev[0][0] = d0;			prev[0][1] = d1;			prev[0][2] = d2;
	}


	while (true) {

		for (int j = 0; j < anchura; ++j) {	// primera fila, la salida siempre es 0
			dataIn0->read(d0);
			dataIn1->read(d1);
			dataIn2->read(d2);
			dataOut00->write(0);		dataOut01->write(0);		dataOut02->write(0);
			dataOut10->write(0);		dataOut11->write(0);		dataOut12->write(0);
			dataOut20->write(0);		dataOut21->write(0);		dataOut22->write(0);

		}

		// estaba aquí

		for (int i = 0; i < (altura -2); ++i) {	

			dataIn0->read(d0);			dataIn1->read(d1);			dataIn2->read(d2);
			prev[1][0] = prev[0][0];	prev[1][1] = prev[0][1];	prev[1][2] = prev[0][2];
			prev[0][0] = d0;			prev[0][1] = d1;			prev[0][2] = d2;

			dataOut00->write(0);		dataOut01->write(0);		dataOut02->write(0);
			dataOut10->write(0);		dataOut11->write(0);		dataOut12->write(0);
			dataOut20->write(0);		dataOut21->write(0);		dataOut22->write(0);


			for (int j = 0; j < (anchura -2); ++j) {

				dataIn0->read(d0);		dataIn1->read(d1);			dataIn2->read(d2);

				dataOut00->write(d0);				dataOut01->write(d1);				dataOut02->write(d2);
				dataOut10->write(prev[0][0]);		dataOut11->write(prev[0][1]);		dataOut12->write(prev[0][2]);
				dataOut20->write(prev[1][0]);		dataOut21->write(prev[1][1]);		dataOut22->write(prev[1][2]);

				prev[1][0] = prev[0][0];	prev[1][1] = prev[0][1];	prev[1][2] = prev[0][2];
				prev[0][0] = d0;			prev[0][1] = d1;			prev[0][2] = d2;

				wait(SC_ZERO_TIME);
			}

			dataIn0->read(d0);			dataIn1->read(d1);			dataIn2->read(d2);
			prev[1][0] = prev[0][0];	prev[1][1] = prev[0][1];	prev[1][2] = prev[0][2];
			prev[0][0] = d0;			prev[0][1] = d1;			prev[0][2] = d2;


			dataOut00->write(0);		dataOut01->write(0);		dataOut02->write(0);
			dataOut10->write(0);		dataOut11->write(0);		dataOut12->write(0);
			dataOut20->write(0);		dataOut21->write(0);		dataOut22->write(0);

			wait(SC_ZERO_TIME);
		}

		for (int j = 0; j < anchura; ++j) {	// última fila, la salida siempre es 0
			dataIn0->read(d0);
			dataIn1->read(d1);
			dataIn2->read(d2);
			dataOut00->write(0);		dataOut01->write(0);		dataOut02->write(0);
			dataOut10->write(0);		dataOut11->write(0);		dataOut12->write(0);
			dataOut20->write(0);		dataOut21->write(0);		dataOut22->write(0);
		}

		wait(SC_ZERO_TIME);
		 
	}
}


