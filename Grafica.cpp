// 
// 
// 

#include "Grafica.h"

Graficador::Graficador(byte rclock, byte latch, byte data)
{
	this->rclock = rclock;
	this->latch = latch;
	this->data = data;
}

Graficador::Graficador()
{
}



void Graficador::imprimirMatriz(int**mat, int fila, int col) {
	for (int i = 0; i<fila; i++) {
		for (int j = 0; j<col; ++j) {
			Serial.print("[");
			Serial.print(mat[i][j]);
			Serial.println("]");
		}
		Serial.print('\n');
	}
}

void Graficador::llenarMatriz(int** mat, int f, int c) {
	for (int i = 0; i < f; i++)
	{
		for (int j = 0; j < c; j++)
		{
			mat[i][j] = i*c + j;
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
