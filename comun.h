#ifndef COMUN_H
#define COMUN_H

#include"half.h"

#define WIDTH 640
#define HEIGHT 512


#define FtypeISfloatnotFloat

#define FtypeIShalf

#ifdef FtypeISfloat
	#define Ftype float 
#endif

#ifdef FtypeIShalf
	#define Ftype half 
#endif

#endif