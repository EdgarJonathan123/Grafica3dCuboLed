
#include "Grafica.h"

Graficador::Graficador(byte rclock, byte latch, byte data)
{
	this->rclock = rclock;
	this->latch = latch;
	this->data = data;

	llenarCeros(ejex);
	llenarCeros(ejey);

	crearCapa();
}
void Graficador::init()
{
	pinMode(latch, OUTPUT);
	pinMode(rclock, OUTPUT);
	pinMode(data, OUTPUT);
}
Graficador::Graficador()
{
}
void Graficador::crearCapa()
{
	capa = nuevaMatriz(tamFila,tamCol);
	llenarMatriz(capa,tamFila,tamCol);
}
void Graficador::imprimirCapa()
{
	imprimirMatriz(capa,tamFila,tamCol);
}
void Graficador::enviarData()
{
	digitalWrite(latch, LOW);
	shiftOut(data, rclock, LSBFIRST, B01110000); //Esta data queda en el ultimo shift register el que tiene el arreglo de transistores darlington ULN2803
	shiftOut(data, rclock, LSBFIRST, B01110000); //Esta data queda en el penultimo shift register
	shiftOut(data, rclock, LSBFIRST, B01110010);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, 255); //Esta data queda en el primer shift register
	digitalWrite(latch, HIGH);
}
void Graficador::imprimirMatriz(int**mat, int fila, int col) {
	for (int i = 0; i<fila; i++) {
		for (int j = 0; j<col; ++j) {
			Serial.print("[");
			Serial.print(mat[i][j]);
			Serial.print("]");
		}
		Serial.println("");
	}
}
void Graficador::llenarMatriz(int** mat, int f, int c) {
	for (int i = 0; i < f; i++)
	{
		for (int j = 0; j < c; j++)
		{
			//mat[i][j] = i*c + j;
			mat[i][j] = 0;
		}
	}

};
int** Graficador::nuevaMatriz(int filas, int columnas) {

	int** matriz;
	matriz = new int*[filas];

	for (int i = 0; i < filas; i++) {
		matriz[i] = new int[columnas];
	}
	return matriz;
}
void Graficador::llenarCeros(float* vector) {
	for (size_t i = 0; i < 8; i++)
	{
		vector[i] = 0;
	}
}


//******Metodos del Algoritmo*******************

void Graficador::escalar(float* vector, int linf, int lsup) {

	int tamanio = lsup - linf;

	for (size_t i = 0; i < 8; i++)
	{
		float escala = ((float)tamanio/7.00);
		vector[i] = linf+i*escala;

		Serial.print("[ Escala = ");
		Serial.print(escala);
		Serial.print(" ]");


		Serial.print("{ Vector(");
		Serial.print(i);
		Serial.print(") = ");
		Serial.print(vector[i]);
		Serial.println(" }");
	}


}


void valuaFuncion(float* eje) {


}

void Graficador::actualizarData()
{
	linfx =  -100;
	lsupx =   100;
	escalar(ejex,linfx,lsupx);

	linfy = 0;
	lsupy = 200;
	escalar(ejey,linfy,lsupy);
}