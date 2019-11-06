// Analisis.h

#ifndef _ANALISIS_h
#define _ANALISIS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Analizador
{
public:


	Analizador();
	void analizaEntrada(String data,String* Fxyz,int* linfx,int*lsupx,int*linfy,int*lsupy,int*linfz,int*lsupz);



};


#endif

