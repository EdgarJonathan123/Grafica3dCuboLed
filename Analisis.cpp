
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

	*Fxyz  = valores[0];
	*linfx = valores[1].toInt();
	*lsupx = valores[2].toInt();
	*linfy = valores[3].toInt();
	*lsupy = valores[4].toInt();
	*linfz = valores[5].toInt();
	*lsupz = valores[6].toInt();


	

}

