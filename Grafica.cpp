
#include "Grafica.h"


Graficador::Graficador(byte rclock, byte latch, byte data)
{
	this->ana = Analizador();
	this->rclock = rclock;
	this->latch = latch;
	this->data = data;
}
void Graficador::init()
{
	pinMode(latch, OUTPUT);
	pinMode(rclock, OUTPUT);
	pinMode(data, OUTPUT);

	llenarCeros(ejex);
	llenarCeros(ejey);
	llenarCeros(ejez);
	llenarCeros(fila);

	Cuadrado = nuevaMatriz(8,8);
	llenarMatriz(Cuadrado,8,8);


	cubo = nuevaMatriz(8, 8);
	llenarMatriz(cubo, 8, 8);

}



void Graficador::enviarData()
{

	digitalWrite(latch, LOW);
	shiftOut(data, rclock, LSBFIRST, nivel); //Esta data queda en el ultimo shift register el que tiene el arreglo de transistores darlington ULN2803
	shiftOut(data, rclock, LSBFIRST, fila[7]); //Esta data queda en el penultimo shift register
	shiftOut(data, rclock, LSBFIRST, fila[6]);
	shiftOut(data, rclock, LSBFIRST, fila[5]);
	shiftOut(data, rclock, LSBFIRST, fila[4]);
	shiftOut(data, rclock, LSBFIRST, fila[3]);
	shiftOut(data, rclock, LSBFIRST, fila[2]);
	shiftOut(data, rclock, LSBFIRST, fila[1]);
	shiftOut(data, rclock, LSBFIRST, fila[0]); //Esta data queda en el primer shift register

	digitalWrite(latch, HIGH);
}

void Graficador::imprimirMatriz(byte**mat, byte fila, byte col) {
	for (byte i = 0; i < fila; i++) {
		for (byte j = 0; j < col; ++j) {
			Serial.print("[");
			Serial.print(mat[i][j]);
			Serial.print("]");
		}
		Serial.println("");
	}
}

void Graficador::llenarMatriz(byte** mat, byte f, byte c) {
	for (byte i = 0; i < f; i++)
	{
		for (byte j = 0; j < c; j++)
		{
			//mat[i][j] = i*c + j;
			mat[i][j] = 0;
		}
	}
};

byte** Graficador::nuevaMatriz(byte filas, byte columnas) {

	byte** matriz;
	matriz = new byte*[filas];

	for (byte i = 0; i < filas; i++) {
		matriz[i] = new byte[columnas];
	}
	return matriz;
}

void Graficador::llenarCeros(float* vector) {
	for (byte i = 0; i < 8; i++)
	{
		vector[i] = 0.0;
	}
}

void Graficador::llenarCeros(byte * vector)
{
	for (byte i = 0; i < 8; i++)
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
	Serial.print(fila[0]);
	Serial.println(" ]");
	Serial.print("[fila1 = ");
	Serial.print(fila[1]);
	Serial.println(" ]");
	Serial.print("[fila2 = ");
	Serial.print(fila[2]);
	Serial.println(" ]");
	Serial.print("[fila3 = ");
	Serial.print(fila[3]);
	Serial.println(" ]");
	Serial.print("[fila4 = ");
	Serial.print(fila[4]);
	Serial.println(" ]");
	Serial.print("[fila5 = ");
	Serial.print(fila[5]);
	Serial.println(" ]");
	Serial.print("[fila6 = ");
	Serial.print(fila[6]);
	Serial.println(" ]");
	Serial.print("[fila7 = ");
	Serial.print(fila[7]);
	Serial.println(" ]");

}

void Graficador::setCapa(byte * capa)
{
	llenarCeros(fila);
	for (byte i = 0; i < 8; i++)
	{
		fila[i] = capa[i];
	}

}




//******Metodos del Algoritmo*******************


void Graficador::escalar(float* vector, int linf, int lsup) {

	int tamanio = lsup - linf;

	for (byte i = 0; i < 8; i++)
	{
		float escala = ((float)tamanio / 7.00);
		vector[i] = linf + i*escala;

		//Serial.print("[ escala = ");
		//Serial.print(escala);
		//Serial.print(" ]");

		//Serial.print("{ vector(");
		//Serial.print(i);
		//Serial.print(") = ");
		//Serial.print(vector[i]);
		//Serial.println(" }");
	}


}

void Graficador::Ecuacion3Variables()
{
	for (byte i = 0; i < 8; i++)
	{
		ana.ReplaceNum(&Exyz, &Exy, ejez[i], "Z");
		Ecucacion2variables(Cuadrado);
		toCubo(Cuadrado, cubo[i]);
	}
}

int Graficador::GetPosJ(float fx, byte i, byte** capa)
{
	int indice = -1;

	if ((fx >= ejey[0]) && (fx <= ejey[7])) {
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
			if (b < a) {
				if (j > 0) {
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
	}

	return indice;
}

//actualiza todos los valores enteros para enviarlos al cubo
void Graficador::toCubo(byte**matriz, byte* vector)
{
	int peso = 0;
	int potencia = 0;

	for (int i = 0; i < 8; i++) {
		potencia = 0;
		for (int j = 7; j > -1; --j, ++potencia) {
			peso = elevar(2, potencia);
			vector[i] += matriz[i][j] * peso;
		}

	}
}

int Graficador::elevar(int n, int m)
{
	int result = 1;
	for (size_t i = 0; i < m; i++)
		result = result*n;
	return result;
}

void Graficador::Ecucacion2variables(byte** capa) {
	llenarMatriz(capa,8,8);
	float fx = 0.0f;
	boolean fxvalida = false;

	for (byte i = 0; i < 8; i++)
	{

		ana.ReplaceNum(&Exy, &Ey, ejex[i], "x");
		fx = ObtenerValorY(i, &fxvalida);


		if (fxvalida) {

			Serial.println("fxvalida");

			int j = GetPosJ(fx, i, capa);
			if (j != -1) {
				capa[i][j] = 1;
			}

			j = GetPosJ(-fx, i, capa);
			if (j != -1) {
				capa[i][j] = 1;
			}
		}
	}

}

float Graficador::ObtenerValorY(byte i , boolean* fxvalida) {

	float result = 0.0;

	Serial.print("Ecucaion :");
	Serial.println(Ey);
	ana.Solve(&Ey,&result,fxvalida);

	return result;
}

//float Graficador::ObtenerValorY(int i, boolean* fxvalida)
//{
//	/*
//	String izq;
//	String der;*/
//
//	//Serial.println(Ey);
//
//	for (byte i = 0; i < 8; i++)
//	{
//		//ana.ReplaceNum(&Ey, &E, ejey[i], "y");
//
//		//ana.separaEcuacion(&E,&der,&izq);
//
//
//		/*Serial.print("[izq: ");
//		Serial.print(izq);
//		Serial.print("][der: ");
//		Serial.print(der);
//		Serial.println("]")*/;
//	}
//
//
//
//
//
//	return 0.00;
//
//
//
//
//
//	//*fxvalida = false;
//
//	////Se quemara la funcion:
//	////f(x)= sqrt(9-x^2)
//
//	//float fx = 0;
//	//float determinante = 0;
//	//float xcuadrado = 0;
//	//float x = 0.0f;
//
//	//x = ejex[i];
//
//	////Serial.print("[x = ");
//	////Serial.print(x);
//	////Serial.print(" ]");
//
//	//xcuadrado = elevar(x, 2);
//
//	////Serial.print("[x^2 = ");
//	////Serial.print(xcuadrado);
//	////Serial.print(" ]");
//
//	//determinante = 81 - xcuadrado;
//
//	////Serial.print("[det = ");
//	////Serial.print(determinante);
//	////Serial.print(" ]");
//
//	////si el  vamos a tener raices reales
//	//if (determinante >= 0) {
//	//	*fxvalida = true;
//	//	fx = sqrtf(determinante);
//
//	//	//Serial.print("[ f(");
//	//	//Serial.print(x);
//	//	//Serial.print(") = ");
//	//	//Serial.print(fx);
//	//	//Serial.println(" ]");	
//	//}
//	//return fx;
//
//
//}

void Graficador::actualizarData()
{
	byte potencia = 7;
	for (byte i = 0; i < 8; i++,--potencia)
	{
		nivel = elevar(2,i);
		setCapa(cubo[i]);
		enviarData();
		delay(100);
	}
}

void Graficador::SetFuncion(String entrada)
{
	ana.analizaEntrada(entrada, &Exyz, &linfx, &lsupx, &linfy, &lsupy, &linfz, &lsupz);
	escalar(ejex, linfx, lsupx);
	escalar(ejey, linfy, lsupy);
	escalar(ejez, linfz, lsupz);

	Ecuacion3Variables();

}
