// Grafica.h

#ifndef _GRAFICA_h
#define _GRAFICA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Graficador
{

public:

	//constructores
	Graficador();
	Graficador::Graficador(byte rclock, byte lacth, byte data);

	void imprimirMatriz(int**mat, int fila, int col);
	void llenarMatriz(int** mat, int f, int c);
	int** nuevaMatriz(int filas, int columnas);


private:


	int8_t fila[8];		//
	byte rclock;		// to all registers
	byte latch;			// to all registers
	byte data;			// to first register
};


#endif

