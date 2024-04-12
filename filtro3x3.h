#ifndef FILTRO3x3_H
#define FILTRO3x3_H

#include "systemc.h"
#include "fifo.h"
#include "buffer2x16b.h"
#include "borders.h"
#include "comun.h"

SC_MODULE(filtro3x3) {
public:
	sc_port<read_if_T<Ftype>>  dataIn;
	sc_port<write_if_T<Ftype>>  dataOut00, dataOut01, dataOut02;
	sc_port<write_if_T<Ftype>>  dataOut10, dataOut11, dataOut12;
	sc_port<write_if_T<Ftype>>  dataOut20, dataOut21, dataOut22;


	SC_HAS_PROCESS(filtro3x3);



	filtro3x3(sc_module_name name_, int _anchura, int _altura) : sc_module(name_) {
		cout << "filtro3x3: " << name() << endl;
	
		Qdata0 = new fifo_T<Ftype>("Qdata0", 1);
		Qdata1 = new fifo_T<Ftype>("Qdata1", 1);
		Qdata2 = new fifo_T<Ftype>("Qdata2", 1);

		instBuffer = new buffer2x16b("instBuffer", _anchura);
		instBorders = new borders("instBorders", _anchura, _altura);

		instBuffer->dataIn(dataIn);
		instBuffer->dataOut0(*Qdata0);
		instBuffer->dataOut1(*Qdata1);
		instBuffer->dataOut2(*Qdata2);

		instBorders->dataIn0(*Qdata0);
		instBorders->dataIn1(*Qdata1);
		instBorders->dataIn2(*Qdata2);

		instBorders->dataOut00(dataOut00);
		instBorders->dataOut01(dataOut01);
		instBorders->dataOut02(dataOut02);
		instBorders->dataOut10(dataOut10);
		instBorders->dataOut11(dataOut11);
		instBorders->dataOut12(dataOut12);
		instBorders->dataOut20(dataOut20);
		instBorders->dataOut21(dataOut21);
		instBorders->dataOut22(dataOut22);

	}

private:
	buffer2x16b* instBuffer; 
	borders* instBorders; 
	fifo_T<Ftype> *Qdata0, *Qdata1, *Qdata2;
};

#endif
