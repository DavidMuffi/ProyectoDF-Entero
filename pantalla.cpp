#include"pantalla.h"



void pantalla::pintar(){

	int frames; 
	int i, j;

	sc_uint<24> pix;
	int R, G, B, Y, U, V;
	short suma; 
	unsigned char uv; 

	unsigned char* pt; 

	for(frames=0; frames<500; ++frames){

		pt = imagen; // se inicializa para cada fotograma


		for (i = 0; i < HEIGHT * 2; ++i) {
			for (j = 0; j < WIDTH * 2; ++j) {

				color->read(pix);
				R = pix(23, 16);
				G = pix(15, 8);
				B = pix(7, 0);

				Y = ( (  66 * (R) + 129 * (G) +  25 * (B) + 128) >> 8) +  16;
				U = ( ( -38 * (R) -  74 * (G) + 112 * (B) + 128) >> 8) + 128;
				V = ( ( 112 * (R) -  94 * (G) -  18 * (B) + 128) >> 8) + 128;

				if(Y<0) Y = 0;
				if(Y>255) Y = 255;
				if(U<0) U = 0;
				if(U>255) U = 255;
				if(V<0) V = 0;
				if(V>255) V = 255;

				*pt = (unsigned char)Y;
				*(pt+size1) = (unsigned char)U; 
				*(pt+size2) = (unsigned char)V; 
				++pt;
			}
		}

		fwrite(imagen, 1, size1, fichero);	// guarda en fichero 1 fotograma completo Y

		//for (i = 0; i < (size1 >> 1); ++i)			imagen[i] = 128;
		//fwrite(imagen, 1, size1>>1, fichero);

		
		pt = imagen + size1; 
		for (i = 0; i < HEIGHT; i++) {			// downscaling de U
			for (j = 0; j < WIDTH; j++) {
				suma = 2 + (*pt) + (*(pt+2*WIDTH));
				++pt;
				suma += (*pt) + (*(pt+ 2 * WIDTH));
				++pt;
				suma >>=2; 
				uv = (unsigned char)suma; 
				fwrite(&uv, 1, 1, fichero);		// guarda byte de U
			}
			pt += WIDTH * 2; // pasa a la siguiente línea
		}

		pt = imagen + size2; 
		for (i = 0; i < HEIGHT; i++) {			// downscaling de v
			for (j = 0; j < WIDTH; j++) {
				suma = 2 + (*pt) + (*(pt+ 2 * WIDTH));
				++pt;
				suma += (*pt) + (*(pt+ 2 * WIDTH));
				++pt;
				suma >>=2; 
				uv = (unsigned char)suma; 
				fwrite(&uv, 1, 1, fichero);		// guarda byte de V
			}
			pt += WIDTH * 2; // pasa a la siguiente línea
		}
		
	}

	fclose(fichero);
	delete imagen; 
	sc_stop();

}
