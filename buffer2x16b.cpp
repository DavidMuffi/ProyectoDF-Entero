#include "buffer2x16b.h"


void buffer2x16b::procesar() {

	Ftype dIn, rec0, rec1;

	rdPt = wrPt = 0; 

	turno = 1;

	while (true) {

		dataIn->read(dIn);
		rec0 = mem0[rdPt];
		rec1 = mem1[rdPt];
		if (!turno) {	// escribimos datos entrantes en mem0
			mem0[wrPt] = dIn;
			dataOut0->write(rec0);
			dataOut1->write(rec1);
			dataOut2->write(dIn);
		}
		else {
			mem1[wrPt] = dIn;
			dataOut0->write(rec1);
			dataOut1->write(rec0);
			dataOut2->write(dIn);
		}
		if (rdPt == (anchura-1)) {
			rdPt = 0;
			turno = !turno; 
		}
		else
			++rdPt;
		wrPt = rdPt; //  es esto correcto?

	}

}


