// Analisis.h
#include <ListLib.h>

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
	void analizaEntrada(String data, String * Fxyz, int * linfx, int * lsupx, int * linfy, int * lsupy, int * linfz, int * lsupz);
	void ReplaceNum(String* origen, String* destino, float reemplazo, String coincidencia);
	void  Solve(String* Ecuacion, float* result, boolean* fxvalida);


private:
	

	void despeje(String*ladoA, String* ladoB , boolean* fxvalida);
	void AnalizaIzqY(String * ladoA, String* ladoB, boolean* fxvalida);
	void AnalizaDerY(String * ladoA, String* ladoB, boolean* fxvalida);
	void AnalizaMedioY(String * ladoA, String* ladoB, boolean* fxvalida);
	void despejeMedio(String* ladoA, String* ladoB);
	byte getIndiceExpresionY(List<String>* list);
	String agregarAlotroLado(String  destino, String  origen);
	void getExpresiones(String * expr, List<String>* expresiones);
	boolean existeY(String* Ecuacion);
	void operarLado(String*ladoA);



	//convierte a posfijo una expresion infija
	void toPosfijo(String* infija, String* result);

	//Analiza los operadores
	void AnalizOperador(char letra, char letraAnt, String* pila, String* result, size_t i);

	//Analiza los parentesis Cerrados
	int AnalizaParC(String* pila, String* result, char letra, size_t i);

	//Apila o desapila los operadores
	void converter(String* pila, String* result, char letra);

	//vacia la pila
	void vaciarPila(String* pila, String* result);

	void desapilaOperandos(List<float>* pila, size_t* i, char caracter);



	void EvaluaPosfijo(String* posfija, String* result);
	float Operacion(char operador, float a, float b);




	boolean esOperador(char letra);
	boolean esY(char letra);
	boolean esParC(char letra);
	boolean esParA(char letra);
	boolean esNumero(char letra);
	byte prioridadExpresion(char operador);
	byte prioridadEnPila(char operador);



	int freeRam()
	{
		extern int __heap_start, *__brkval;
		int v;
		return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
	}

};


#endif

