// Grafica.h
#include "Analisis.h"
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
	void printCubo();
	//envia los datos al cubo
	void enviarData();
	//recorre la data y lo envia al cubo
	void actualizarData();
	//setea una funcion en 3d al cubo 
	void SetFuncion(String entrada);
	

private:

	//variables globales
	Analizador ana;
	float ejex[8];
	float ejey[8];
	float ejez[8];
	byte*** cubo;
	//byte** capa;

	//funciones
	String Exyz;	//ecuacion 3 variables
	String Exy;		//ecuacion 2 variables
	String Ey;		//ecuacion 1 variable

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
	byte nivel = 0;
	byte fila[8];
	
	//metodos para el algoritmo de graficado
	void escalar(float* vector,int linf,int lsup);

	void valuafxy(byte** capa);
	float getfx(int i,boolean* fxvalida);
	int getPosj(int fx,int i,byte** capa);
	void toCubo(byte ** capa);
	int elevar(int n,int m);

	
	//metodoa para crear una matriz
	void crearCubo();
	
	byte*** nuevoCubo(byte filas,byte columnas,byte caras);
	byte** nuevaMatriz(byte filas, byte columnas);

	void imprimirCubo(byte***cubo,byte fila,byte columnas,byte caras);
	void imprimirMatriz(byte**mat, byte fila, byte col);
	
	void llenarCubo(byte*** cubo,byte filas,byte columnas, byte caras);
	void llenarMatriz(byte** mat, byte f, byte c);

	void llenarCeros(float* vector);
	void llenarCeros(byte* vector);
	void printData();

			
	byte rclock;		// to all registers
	byte latch;			// to all registers
	byte data;			// to first register
};


#endif

