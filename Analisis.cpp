
#include "Analisis.h"

Analizador::Analizador()
{
}

void Analizador::analizaEntrada(String data, String * Fxyz, int * linfx, int * lsupx, int * linfy, int * lsupy, int * linfz, int * lsupz)
{
	int pos = 0;
	String valores[7];

	for (size_t i = 0; i < data.length(); i++)
	{
		char caracter = data.charAt(i);
		if (caracter != ';') {
			valores[pos] += caracter;
		}
		else if (caracter == ' ') {}
		else {
			++pos;
		}
	}

	*Fxyz = valores[0];
	*linfx = valores[1].toInt();
	*lsupx = valores[2].toInt();
	*linfy = valores[3].toInt();
	*lsupy = valores[4].toInt();
	*linfz = valores[5].toInt();
	*lsupz = valores[6].toInt();
}

void Analizador::ReplaceNum(String * origen, String * destino, float reemplazo, String coincidencia)
{
	coincidencia.toLowerCase();
	char coincidenciaMinuscula = coincidencia.charAt(0);

	String part[2];
	String Reemplazo = "(";

	int Tamanio = origen->length();
	for (unsigned int i = 0; i < Tamanio; i++)
	{
		char caracter = origen->charAt(i);
		if (caracter == coincidenciaMinuscula) {
			part[0] = origen->substring(0, i);
			part[1] = origen->substring(i + 1, Tamanio);
			break;
		}
	}



	Reemplazo += (String)reemplazo;
	Reemplazo.concat(')');


	for (size_t i = 0; i < Reemplazo.length(); i++)
	{
		char caracter = Reemplazo.charAt(i);
		part[0].concat(caracter);
	}

	for (size_t i = 0; i < part[1].length(); i++)
	{
		part[0].concat(part[1].charAt(i));
	}

	*destino = part[0];

	Serial.println(*destino);

}




void Analizador::despejarFX(String * FXY, float x)
{
}

