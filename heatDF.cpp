#include "systemc.h"
#include "fifo.h"
#include "comun.h"

#include "mem.h"
#include "heatEq.h"
#include "convHalf.h"
#include "filtro3x3.h"
#include "expandir.h"
#include "suavizar.h"
#include "convByte.h"
#include "traducir.h"
#include "pantalla.h"
#include "escritor.h"


class producer : public sc_module
{
public:
	sc_port<write_if_T<sc_uint<19>>> readAddr; // , writeAddr; // producer output port
//sc_port<write_if_T<sc_uint<8>>> dummy;

SC_CTOR(producer) // module constructor
{
	SC_THREAD(main); // start the process
}
void main() // the producer process
{
	int i, j;

	while (true) {
		for (i = 0; i < HEIGHT; ++i) {
			for (j = 0; j < WIDTH; ++j) {
				readAddr->write(j + i * WIDTH);
				wait(SC_ZERO_TIME);
			}
		}
	}
}
};



class top : public sc_module
{
public:
fifo_T<sc_uint<19>> *QreadAddr, *QwriteAddr;
fifo_T<sc_uint<8>> *QmemIn, *QmemOut, *Qnivel, *Qretorno;
fifo_T<sc_uint<24>>* Qpixel;
fifo_T<Ftype> *QhalfConv, *Qcalculado, * Qexpandido, *Qsuavizado, *QretornoFloat;

fifo_T<Ftype>* Qdata00, * Qdata01, * Qdata02;
fifo_T<Ftype>* Qdata10, * Qdata11, * Qdata12;
fifo_T<Ftype>* Qdata20, * Qdata21, * Qdata22;

fifo_T<Ftype>* QdataX00, * QdataX01, * QdataX02;
fifo_T<Ftype>* QdataX10, * QdataX11, * QdataX12;
fifo_T<Ftype>* QdataX20, * QdataX21, * QdataX22;

producer* instProducer;
mem* instMem;
heatEq* instHeatEq;
convHalf* instConvHalf;
filtro3x3* instFiltroEq; 
filtro3x3* instFiltroSuavizar; 

expandir* instExpandir;
suavizar* instSuavizar;
convByte* instConvByteRetorno, *instConvBytePantalla;
traducir* instTraducir;
pantalla* instPantalla;
escritor* instEscritor;


SC_CTOR(top) // the module constructor
{

QreadAddr = new fifo_T<sc_uint<19>>("QreadAddr", 1);
QwriteAddr = new fifo_T<sc_uint<19>>("QwriteAddr", 1);

QmemIn = new fifo_T<sc_uint<8>>("QmemIn", 1);
QmemOut = new fifo_T<sc_uint<8>>("QmemOut",1);
Qretorno = new fifo_T<sc_uint<8>>("Qretorno", 1);

Qnivel = new fifo_T<sc_uint<8>>("Qnivel", 1);
Qpixel = new fifo_T<sc_uint<24>>("Qpixel", 1);

QhalfConv = new fifo_T<Ftype>("QhalfConv", 1);
Qcalculado = new fifo_T<Ftype>("Qcalculado", 1);
Qexpandido = new fifo_T<Ftype>("Qexpandido", 1);
Qsuavizado = new fifo_T<Ftype>("Qsuavizado", 1);
QretornoFloat = new fifo_T<Ftype>("QretornoFloat", 1);

Qdata00 = new fifo_T<Ftype>("Qdata00", 1);
Qdata01 = new fifo_T<Ftype>("Qdata01", 1);
Qdata02 = new fifo_T<Ftype>("Qdata02", 1);
Qdata10 = new fifo_T<Ftype>("Qdata10", 1);
Qdata11 = new fifo_T<Ftype>("Qdata11", 1);
Qdata12 = new fifo_T<Ftype>("Qdata12", 1);
Qdata20 = new fifo_T<Ftype>("Qdata20", 1);
Qdata21 = new fifo_T<Ftype>("Qdata21", 1);
Qdata22 = new fifo_T<Ftype>("Qdata22", 1);

QdataX00 = new fifo_T<Ftype>("QdataX00", 1);
QdataX01 = new fifo_T<Ftype>("QdataX01", 1);
QdataX02 = new fifo_T<Ftype>("QdataX02", 1);
QdataX10 = new fifo_T<Ftype>("QdataX10", 1);
QdataX11 = new fifo_T<Ftype>("QdataX11", 1);
QdataX12 = new fifo_T<Ftype>("QdataX12", 1);
QdataX20 = new fifo_T<Ftype>("QdataX20", 1);
QdataX21 = new fifo_T<Ftype>("QdataX21", 1);
QdataX22 = new fifo_T<Ftype>("QdataX22", 1);

instProducer = new producer("instProducer");
instMem = new mem("instMem");
instConvHalf = new convHalf("instConvHalf");
instFiltroEq = new filtro3x3("instFiltroEq", WIDTH, HEIGHT);
instHeatEq = new heatEq("instHeatEq");

instExpandir = new expandir("instExpandir");
instFiltroSuavizar = new filtro3x3("instFiltroSuavizar", WIDTH*2, HEIGHT*2);
instSuavizar = new suavizar("instSuavizar");
instConvByteRetorno = new convByte("instConvByteRetorno");
instConvBytePantalla = new convByte("instConvBytePantalla");
instTraducir = new traducir("instTraducir");
instPantalla = new pantalla("instPantalla", "videoCalor.yuv");
instEscritor = new escritor("instEscritor");

instProducer->readAddr(*QreadAddr);

instMem->readAddr( *QreadAddr);
instMem->writeAddr( *QwriteAddr);
instMem->dataIn( *QmemIn);
instMem->dataOut(*QmemOut);

instConvHalf->byteIn(*QmemOut);
instConvHalf->halfOut(*QhalfConv);

instFiltroEq->dataIn(*QhalfConv);
instFiltroEq->dataOut00(*Qdata00);
instFiltroEq->dataOut01(*Qdata01);
instFiltroEq->dataOut02(*Qdata02);
instFiltroEq->dataOut10(*Qdata10);
instFiltroEq->dataOut11(*Qdata11);
instFiltroEq->dataOut12(*Qdata12);
instFiltroEq->dataOut20(*Qdata20);
instFiltroEq->dataOut21(*Qdata21);
instFiltroEq->dataOut22(*Qdata22);


instHeatEq->dataIn00(*Qdata00);
instHeatEq->dataIn01(*Qdata01);
instHeatEq->dataIn02(*Qdata02);
instHeatEq->dataIn10(*Qdata10);
instHeatEq->dataIn11(*Qdata11);
instHeatEq->dataIn12(*Qdata12);
instHeatEq->dataIn20(*Qdata20);
instHeatEq->dataIn21(*Qdata21);
instHeatEq->dataIn22(*Qdata22);
instHeatEq->dataOut(*Qcalculado);
instHeatEq->retorno(*QretornoFloat);	// es una copia de Qcalculado

instConvByteRetorno->halfIn(*QretornoFloat);
instConvByteRetorno->byteOut(*Qretorno);

instEscritor->byteIn(*Qretorno);
instEscritor->byteOut(*QmemIn);
instEscritor->writeAddr(*QwriteAddr);

instExpandir->dataIn(*Qcalculado);
instExpandir->dataOut(*Qexpandido);

instFiltroSuavizar->dataIn(*Qexpandido);
instFiltroSuavizar->dataOut00(*QdataX00);
instFiltroSuavizar->dataOut01(*QdataX01);
instFiltroSuavizar->dataOut02(*QdataX02);
instFiltroSuavizar->dataOut10(*QdataX10);
instFiltroSuavizar->dataOut11(*QdataX11);
instFiltroSuavizar->dataOut12(*QdataX12);
instFiltroSuavizar->dataOut20(*QdataX20);
instFiltroSuavizar->dataOut21(*QdataX21);
instFiltroSuavizar->dataOut22(*QdataX22);


instSuavizar->dataIn00(*QdataX00);
instSuavizar->dataIn01(*QdataX01);
instSuavizar->dataIn02(*QdataX02);
instSuavizar->dataIn10(*QdataX10);
instSuavizar->dataIn11(*QdataX11);
instSuavizar->dataIn12(*QdataX12);
instSuavizar->dataIn20(*QdataX20);
instSuavizar->dataIn21(*QdataX21);
instSuavizar->dataIn22(*QdataX22);
instSuavizar->dataOut(*Qsuavizado);

instConvBytePantalla->halfIn(*Qsuavizado);
instConvBytePantalla->byteOut(*Qnivel);

instTraducir->dataIn(*Qnivel);
instTraducir->dataOut(*Qpixel);

instPantalla->color(*Qpixel);

}
};






int sc_main(int nargs, char* vargs[]){



	top instTop("top");	
	sc_start();

	return 0;

}


