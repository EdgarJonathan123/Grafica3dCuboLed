
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
	capa = nuevaMatriz(tamFila, tamCol);
	llenarMatriz(capa, tamFila, tamCol);
}
void Graficador::imprimirCapa()
{
	imprimirMatriz(capa, tamFila, tamCol);
}
void Graficador::enviarData()
{
	digitalWrite(latch, LOW);
	shiftOut(data, rclock, LSBFIRST, nivel); //Esta data queda en el ultimo shift register el que tiene el arreglo de transistores darlington ULN2803
	shiftOut(data, rclock, LSBFIRST, fila7); //Esta data queda en el penultimo shift register
	shiftOut(data, rclock, LSBFIRST, fila6);
	shiftOut(data, rclock, LSBFIRST, fila5);
	shiftOut(data, rclock, LSBFIRST, fila4);
	shiftOut(data, rclock, LSBFIRST, fila3);
	shiftOut(data, rclock, LSBFIRST, fila2);
	shiftOut(data, rclock, LSBFIRST, fila1);
	shiftOut(data, rclock, LSBFIRST, fila0); //Esta data queda en el primer shift register
	digitalWrite(latch, HIGH);
}
void Graficador::imprimirMatriz(int**mat, int fila, int col) {
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < col; ++j) {
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

void Graficador::printData()
{
	Serial.print("[Nivel = ");
	Serial.print(nivel);
	Serial.println(" ]");
	Serial.print("[fila0 = ");
	Serial.print(fila0);
	Serial.println(" ]");
	Serial.print("[fila1 = ");
	Serial.print(fila1);
	Serial.println(" ]");
	Serial.print("[fila2 = ");
	Serial.print(fila2);
	Serial.println(" ]");
	Serial.print("[fila3 = ");
	Serial.print(fila3);
	Serial.println(" ]");
	Serial.print("[fila4 = ");
	Serial.print(fila4);
	Serial.println(" ]");
	Serial.print("[fila5 = ");
	Serial.print(fila5);
	Serial.println(" ]");
	Serial.print("[fila6 = ");
	Serial.print(fila6);
	Serial.println(" ]");
	Serial.print("[fila7 = ");
	Serial.print(fila7);
	Serial.println(" ]");

}


//******Metodos del Algoritmo*******************

void Graficador::escalar(float* vector, int linf, int lsup) {

	int tamanio = lsup - linf;

	for (size_t i = 0; i < 8; i++)
	{
		float escala = ((float)tamanio / 7.00);
		vector[i] = linf + i*escala;

		/*	Serial.print("[ Escala = ");
			Serial.print(escala);
			Serial.print(" ]");


			Serial.print("{ Vector(");
			Serial.print(i);
			Serial.print(") = ");
			Serial.print(vector[i]);
			Serial.println(" }");*/
	}


}

int Graficador::getPosj(int fx, int i)
{
	int indice = 0;
	float a = 0;
	float b = 0;
	float c = 0;

	for (size_t j = 0; j < 7; j++)
	{
		//a la resta entre la posicion j y la el valor fx
		a = abs(ejey[j] - fx);
		//Serial.print("[para i=");
		//Serial.print(i);
		//Serial.print("; |");
		//Serial.print(eje[i]);
		//Serial.print("-");
		//Serial.print(y);
		//Serial.print("| = ");
		//Serial.print(a);
		//Serial.print(" ]");
		//b la resta entre la posicion j+1 y la el valor fx
		b = abs(ejey[j + 1] - fx);
		//Serial.print("[para i+1=");
		//Serial.print(i + 1);
		//Serial.print("; |");
		//Serial.print(eje[i + 1]);
		//Serial.print("-");
		//Serial.print(y);
		//Serial.print("| = ");
		//Serial.print(b);
		//Serial.println(" ]");

		//si b<a entonces elegimos b
		// b esta asociado a i+1
		if (b<a) {
			if(j > 0) {
				c = abs(ejey[indice] - fx);
				if (b < c) {
					indice = j + 1;
				}
			}
			else {
				indice = j + 1;
			}
		}

		//si a < b entonces elegimos a
		// a esta asociado a i
		else if (a < b) {

			if (j > 0) {
				c = abs(ejey[indice] - fx);

				if (a < c) {
					indice = j;
				}
			}
			else {
				indice = j;
			}
		}
		else {
			capa[i][j + 1] = 1;
			capa[i][j] = 1;
			indice = j;
			break;
		}

	}

	//Serial.println("*************");
	//Serial.print("[i =");
	//Serial.print(indice);
	//Serial.print("; eje[i] = ");
	//Serial.print(eje[indice]);
	//Serial.println(" ]");

	return indice;
}

void Graficador::toCubo()
{
	fila0 = 0;
	fila1 = 0;
	fila2 = 0;
	fila3 = 0;
	fila4 = 0;
	fila5 = 0;
	fila6 = 0;
	fila7 = 0;

	int peso = 0;
	int potencia = 0;
	for (int i = 0; i < 8; i++) {

		potencia = 0;
		for (int j = 7; j > -1; --j) {

			if (i == 0) {
				peso = elevar(2, potencia);
				fila0 += capa[i][j] * peso;
			}
			else if (i == 1) {
				peso = elevar(2, potencia);
				fila1 += capa[i][j] * peso;
			}
			else if (i == 2) {
				peso = elevar(2, potencia);
				fila2 += capa[i][j] * peso;
			}
			else if (i == 3) {
				peso = elevar(2, potencia);
				fila3 += capa[i][j] * peso;
			}
			else if (i == 4) {
				peso = elevar(2, potencia);
				fila4 += capa[i][j] * peso;
			}
			else if (i == 5) {
				peso = elevar(2, potencia);
				fila5 += capa[i][j] * peso;
			}
			else if (i == 6) {
				peso = elevar(2, potencia);
				fila6 += capa[i][j] * peso;
			}
			else if (i == 7) {
				peso = elevar(2, potencia);
				fila7 += capa[i][j] * peso;
			}


			++potencia;
		}

	}
}

int Graficador::elevar(int n, int m)
{
	int result = 1;


	for (size_t i = 0; i < m; i++)
	{
		result = result*n;
	}

	return result;
}

void Graficador::valuafxy() {

	float fx = 0.0f;
	boolean fxvalida = false;

	for (size_t i = 0; i < 8; i++)
	{
		fx = getfx(i,&fxvalida);

		if (fxvalida) {
			int j = getPosj(fx, i);
			capa[i][j] = 1;
		}
		else {
		}
		
	}

}

float Graficador::getfx(int i,boolean* fxvalida)
{
	*fxvalida = false;

	//Se quemara la funcion:
	//f(x)= sqrt(9-x^2)

	float fx = 0;
	float determinante = 0;
	float xcuadrado = 0;
	float x = 0.0f;

	x = ejex[i];
	//Serial.print("[x = ");
	//Serial.print(x);
	//Serial.print(" ]");
	xcuadrado = elevar(x, 2);
	//Serial.print("[x^2 = ");
	//Serial.print(xcuadrado);
	//Serial.print(" ]");
	determinante = 81 - xcuadrado;
	//Serial.print("[det = ");
	//Serial.print(determinante);
	//Serial.print(" ]");
	//si el  vamos a tener raices reales
	if (determinante >= 0) {
		*fxvalida = true;
		fx = sqrtf(determinante);
		//Serial.print("[ f(");
		//Serial.print(x);
		//Serial.print(") = ");
		//Serial.print(fx);
		//Serial.println(" ]");	
	}

	return fx;
}

void Graficador::actualizarData()
{

	linfx = 0;
	lsupx = 9;
	escalar(ejex, linfx, lsupx);

	linfy = -9;
	lsupy = 9;
	escalar(ejey, linfy, lsupy);

	valuafxy();
	toCubo();
	//printData();

}