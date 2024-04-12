#ifndef PANTALLA_H
#define PANTALLA_H

#include "systemc.h"
#include "fifo.h"
#include "comun.h"


SC_MODULE (pantalla) {
public:
sc_port<read_if_T<sc_uint<24>>>  color;

SC_HAS_PROCESS(pantalla);

void pintar();


pantalla(sc_module_name name_, char* fileName) : sc_module(name_) {
  
	int i; 

	cout<<"pantalla: "<<name()<< "  " << fileName << endl;
    
	fichero = fopen(fileName, "wb");
	if (!fichero) {
		fprintf(stderr, "No es posible abrir el fichero %s\n", fileName);
		exit(-1);
	}

	size1 = WIDTH * HEIGHT * 4; // *4 debido al upsamplig
	size2 = (size1 * 2); 
	size3 = (size1 * 3); 
	imagen = new unsigned char[size3];

	//for (i = size1; i < size2; ++i)		imagen[i] = 0; 

    SC_THREAD(pintar);

  }

private:
	int size1, size2, size3; 
	FILE* fichero;
	unsigned char* imagen; 
}; 

#endif;