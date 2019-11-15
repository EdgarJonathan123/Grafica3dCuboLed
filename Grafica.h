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

	Graficador(byte rclock, byte lacth, byte data); //rclock=reloj, data=datos,lacth=segundo reloj
	void init();									//Inicia los componentes del objeto
	void enviarData();								//lee el cubo y envia la data
	void actualizarData();							//Actualiza la matriz que se envia al cubo
	void SetFuncion(String entrada);				//Resuelve la Funcion3D y setea los datos en una matriz

private:

	byte rclock;									// to all registers
	byte latch;										// to all registers
	byte data;										// to first register


	Analizador ana;									//Analiza la funciones
	float ejex[8];									//vector escalado en el ejex
	float ejey[8];									//vector escalado en el ejey
	float ejez[8];									//vector escalado en el ejez
	byte** cubo;									//cubo el cual se va imprimir
	byte** Cuadrado;									//auxiliar mientras se analiza la funcion

	String Exyz;									//ecuacion 3 variables
	String Exy;										//ecuacion 2 variables
	String Ey;										//ecuacion 1 variable

	int linfx = 0;									//Limite Inferior x
	int lsupx = 0;									//Limite Superior x
	int linfy = 0;									//Limite Inferior y
	int lsupy = 0;									//Limite Superior y
	int linfz = 0;									//Limite Inferior z
	int lsupz = 0;									//Limite Superior z
		 

	byte nivel = 0;									//Define el nivel del cubo
	byte fila[8];									//define las filas de la capa que salen al cubo



	void escalar(float* vector,int linf,int lsup);
	void Ecuacion3Variables();
	void Ecucacion2variables(byte** capa);
	float ObtenerValorY(byte i,boolean* fxvalida);
	int GetPosJ(float fx,byte i,byte** capa);
	void toCubo(byte ** capa, byte* vector);

	int elevar(int n,int m);

	
	byte** nuevaMatriz(byte filas, byte columnas);
	void imprimirMatriz(byte**mat, byte fila, byte col);
	void llenarMatriz(byte** mat, byte f, byte c);
	void llenarCeros(float* vector);
	void llenarCeros(byte* vector);
	void printData();
	void setCapa(byte*capa);




};


#endif

