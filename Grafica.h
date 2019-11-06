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
	Graficador(byte rclock, byte lacth, byte data);
	Graficador();

	//metodos
	void init();
	void imprimirCapa();
	void enviarData();
	void actualizarData();
	

private:

	//variables globales
	float ejex[8];
	float ejey[8];
	const int tamCol = 8;
	const int tamFila = 8;
	int** capa;

	//limites ejex
	int linfx = 0;
	int lsupx = 0;

	//limites ejey
	int linfy = 0;
	int lsupy = 0;

	//limites ejez
	int linfz = 0;
	int lsupz = 0;
		 

	//Salidas al cubo
	int nivel = 255;
	int fila[8];

	
	//metodos para el algoritmo de graficado
	void escalar(float* vector,int linf,int lsup);
	void valuafxy();
	float getfx(int i,boolean* fxvalida);
	int getPosj(int fx,int i);
	void toCubo();
	int elevar(int n,int m);

	
	//metodoa para crear una matriz
	void crearCapa();
	void imprimirMatriz(int**mat, int fila, int col);
	void llenarMatriz(int** mat, int f, int c);
	int** nuevaMatriz(int filas, int columnas);
	void llenarCeros(float* vector);
	void llenarCeros(int* vector);
	void printData();

			
	byte rclock;		// to all registers
	byte latch;			// to all registers
	byte data;			// to first register
};


#endif

