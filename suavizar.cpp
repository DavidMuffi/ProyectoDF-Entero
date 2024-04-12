#pragma once
#include "suavizar.h"

void suavizar::run() {
	Ftype d00, d01, d02, d10, d11, d12, d20, d21, d22;
	while (true) {
		dataIn00->read(d00);
		dataIn01->read(d01);
		dataIn02->read(d02);
		dataIn10->read(d10);
		dataIn11->read(d11);
		dataIn12->read(d12);
		dataIn20->read(d20);
		dataIn21->read(d21);
		dataIn22->read(d22);

		dataOut->write((d00 + d01 + d02 + d10 + d11 + d12 + d20 + d21 + d22) * 0.11111);
	}
}