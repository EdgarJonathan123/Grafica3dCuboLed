
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

	//Serial.println(*destino);


}

void Analizador::Solve(String * Ecuacion, float * result, boolean* fxvalida)
{
	byte pos = 0;
	String izq = "";
	String der = "";

	for (size_t i = 0; i < Ecuacion->length(); i++)
	{
		char caracter = Ecuacion->charAt(i);
		if (caracter != '=') {
			if (pos == 0) {
				izq.concat(caracter);
			}
			else {
				der.concat(caracter);
			}
		}
		else {
			++pos;
		}
	}


	if (existeY(&izq)) {
		despeje(&izq, &der, fxvalida);
		*result = der.toFloat();
	}
	else if (existeY(&der)) {
		despeje(&der, &izq, fxvalida);

		*result = izq.toFloat();
	}


	//Serial.print("Respuesta Final: ");
	//Serial.println(*result);

	Serial.print("Ecuacion : ");
	Serial.print(izq);
	Serial.print(" = ");
	Serial.println(der);


}

void Analizador::despeje(String * ladoA, String* ladoB, boolean* fxvalida)
{
	despejeMedio(ladoA, ladoB);


	String izqY = "";
	String derY = "";
	String medioY = "";

	byte pos = 0;
	for (size_t i = 0; i < ladoA->length(); i++)
	{
		char letra = ladoA->charAt(i);



		if ((letra == '^') || esNumero(letra) || (letra == 'y') || (letra == 'Y'))
		{
			medioY.concat(letra);
		}
		else	if ((letra != 'y') && (letra != 'Y')) {

			if (pos == 0) {
				izqY.concat(letra);
			}
			else {
				derY.concat(letra);
			}

		}
		else {
			pos++;
		}


	}

	if (izqY.length() > 0) {
	}

	if (derY.length() > 0) {
	}

	if (medioY.length() > 0) {
		AnalizaMedioY(&medioY, ladoB, fxvalida);
	}

	*ladoA = "y";

	//Serial.print("izqY = ");
	//Serial.print(izqY);
	//Serial.println(";");

	//Serial.print("medioY = ");
	//Serial.print(medioY);
	//Serial.println(";");

	//Serial.print("derY = ");
	//Serial.print(derY);
	//Serial.println(";");
}

void Analizador::AnalizaIzqY(String * ladoA, String* ladoB)
{
}

void Analizador::AnalizaDerY(String * ladoA, String* ladoB)
{
}

void Analizador::AnalizaMedioY(String * ladoA, String* ladoB, boolean* fxvalida)
{
	for (size_t i = 0; i < ladoA->length(); i++)
	{
		char letra = ladoA->charAt(i);
		if (letra == '^') {
			i++;
			letra = ladoA->charAt(i);
			//Serial.print("lETRA: ");
			//Serial.println(letra);
			if (letra == '2') {

				float aux = 0.0;
				aux = ladoB->toFloat();
				//Serial.print("Aux: ");
				//Serial.println(aux);
				if (aux > 0) {
					*fxvalida = true;
					aux = sqrt(aux);
				}


				//Serial.print("Aux: ");
				//Serial.println(aux);

				*ladoB = (String)aux;
				break;
			}


		}


	}
}

void Analizador::despejeMedio(String * ladoA, String * ladoB)
{
	List<String>* expresiones = new List<String>();
	getExpresiones(ladoA, expresiones);
	byte indice = getIndiceExpresionY(expresiones);

	for (size_t i = 0; i < expresiones->Count(); i++)
	{
		String exp = (*expresiones)[i];
		if (i != indice) {
			for (size_t j = 0; j < exp.length(); j++)
			{
				char letra = exp.charAt(j);
				ladoB->concat(letra);
			}

			String aux = "";
			toPosfijo(ladoB, &aux);
			*ladoB = aux;
			aux = "";
			EvaluaPosfijo(ladoB, &aux);
			*ladoB = aux;

		}
	}
	*ladoA = "";
	char letra = expresiones->operator[](indice).charAt(0);
	if (letra == '+') {

		for (size_t i = 0; i < expresiones->operator[](indice).length(); i++)
		{
			char caracter = expresiones->operator[](indice).charAt(i);
			if (i > 0) {
				ladoA->concat(caracter);
			}
			else {
				ladoA->concat('-');
			}
		}
	}
	else {

		for (size_t i = 1; i < expresiones->operator[](indice).length(); i++)
		{
			char caracter = expresiones->operator[](indice).charAt(i);
			ladoA->concat(caracter);
		}

	}


	//Serial.print("Ecuacion = ");
	//Serial.print(*ladoA);
	//Serial.print(" = ");
	//Serial.println(*ladoB);




	expresiones->~List();



}

byte Analizador::getIndiceExpresionY(List<String>* list)
{

	for (size_t i = 0; i < list->Count(); i++)
	{
		String aux = list->operator[](i);

		if (existeY(&aux)) {
			return i;
		}
	}


	return 0;
}


String Analizador::agregarAlotroLado(String  destino, String  origen)
{
	for (size_t i = 0; i < origen.length(); i++)
	{
		char letra = origen.charAt(i);
		destino.concat(letra);
	}

	return destino;
}

void Analizador::getExpresiones(String * expr, List<String>* expresiones)
{
	String pila = "";
	String cadena = "";

	for (int i = 0; i < expr->length(); i++)
	{
		char letra = expr->charAt(i);

		if (i == 0) {
			if (letra == '-') {
			}
			else {
				cadena.concat('+');
			}

			if (esParA(letra)) {
				pila.concat('(');
			}
		}
		else {

			if (esParA(letra)) {
				pila.concat('(');
			}

			if (esParC(letra)) {
				pila.remove(pila.length() - 1);
			}

			if (pila.length() == 0) {
				if (letra == '+') {
					expresiones->Add(cadena);
					cadena = "";
				}
				else if (letra == '-') {
					expresiones->Add(cadena);
					cadena = "";
				}
				else if ((i) == (expr->length() - 1)) {
					cadena.concat(letra);
					expresiones->Add(cadena);
					cadena = "";
					break;
				}
			}


		}


		cadena.concat(letra);

		//Serial.print("expr[");
		//Serial.print(i);
		//Serial.print("] = ");
		//Serial.print(letra);
		//Serial.print("; cadena = [");
		//Serial.print(cadena);
		//Serial.println("];");

	}



	for (size_t i = 0; i < expresiones->Count(); i++)
	{
		char letra = (*expresiones)[i].charAt(0);

		if (letra == '+') {
			(*expresiones)[i][0] = '-';
		}
		else if (letra == '-') {
			(*expresiones)[i][0] = '+';
		}
	}

}

boolean Analizador::existeY(String * Ecuacion)
{
	char letra;
	for (size_t i = 0; i < Ecuacion->length(); i++)
	{
		letra = Ecuacion->charAt(i);
		if (esY(letra)) {
			return true;
		}
	}
	return false;
}

void Analizador::toPosfijo(String * infija, String * result)
{
	String pila = "";
	char letra = ',';
	char letraAnt = ',';

	for (size_t i = 0; i < infija->length(); i++)
	{
		letra = infija->charAt(i);
		//Serial.print("Caracter[");
		//Serial.print(i);
		//Serial.print("] = ");
		//Serial.print(letra);
		//Serial.println(";");
		//
		//Serial.print("Result = ");
		//Serial.print(*result);
		//Serial.println(";");
		//
		//Serial.print("Pila : [");
		//Serial.print(pila);
		//Serial.println("]");

		while (esParC(letra)) {
			i = AnalizaParC(&pila, result, letra, i);
			letra = infija->charAt(i);
		}

		if (i == infija->length()) {
			break;
		}


		AnalizOperador(letra, letraAnt, &pila, result, i);

		letraAnt = letra;
	}

	vaciarPila(&pila, result);

}

void Analizador::AnalizOperador(char letra, char letraAnt, String* pila, String* result, size_t i)
{
	if (esOperador(letra))
	{
		if ((esNumero(letraAnt) || esParC(letraAnt)) && (i > 0)) {
			converter(pila, result, letra);
		}
		else {

			if (esParA(letra)) {
				converter(pila, result, letra);
			}
			else {
				result->concat(letra);
			}
		}
	}
	else {
		result->concat(letra);
	}

}

int  Analizador::AnalizaParC(String* pila, String* result, char letra, size_t i)
{
	char elementotope = pila->charAt(pila->length() - 1);

	while (elementotope != '(') {

		result->concat(',');
		result->concat(elementotope);

		pila->remove(pila->length() - 1);
		elementotope = pila->charAt(pila->length() - 1);
	}

	pila->remove(pila->length() - 1);

	i++;

	return i;
}

void Analizador::converter(String* pila, String* result, char letra)
{

	if (pila->length() == 0) {
		pila->concat(letra);

		if (!esParA(letra)) {
			result->concat(',');
		}

	}
	else {
		byte pe = prioridadExpresion(letra);
		byte pp = prioridadEnPila(pila->charAt(pila->length() - 1));

		//Serial.print("[ caracter = ");
		//Serial.print(letra);
		//Serial.print(", Prioridad = ");
		//Serial.print(pe);
		//Serial.print(", elmentoTope = ");
		//Serial.print(pila->charAt(pila->length() - 1));
		//Serial.print(", Prioridad = ");
		//Serial.print(pp);
		//Serial.println(" ]");

		//si la prioriodad en el tope de la pila es mayor a la prioridad de la expresion
		if (pe > pp) {
			pila->concat(letra);
			if (!esParA(letra)) {
				result->concat(',');
			}
		}
		else {

			//desapilamos y concatenamos en el string resultante
			char elementoTope = pila->charAt(pila->length() - 1);

			result->concat(',');
			result->concat(elementoTope);
			result->concat(',');

			pila->remove(pila->length() - 1);
			pila->concat(letra);
		}
	}
}

void Analizador::vaciarPila(String* pila, String* result)
{
	while (pila->length() != 0)
	{
		char elementoTope = pila->charAt(pila->length() - 1);
		result->concat(',');
		result->concat(elementoTope);
		pila->remove(pila->length() - 1);
	}
}


void Analizador::EvaluaPosfijo(String * posfija, String * result)
{
	List<float>  pila;

	float num1 = 0.0;
	float num = 0.0;

	String Operando = "";



	for (size_t i = 0; i < posfija->length(); i++)
	{
		char caracter = posfija->charAt(i);

		//Serial.print("Caracter[");
		//Serial.print(i);
		//Serial.print("] = [");
		//Serial.print(caracter);
		//Serial.print("] ->");

		if (caracter == ',') {

			//Serial.print("Operando: ");
			//Serial.println(Operando);

			num = Operando.toFloat();
			pila.Add(num);
			Operando = "";

		}
		else if (!esOperador(caracter)) {
			//Serial.println(" No es un operador");
			Operando.concat(caracter);
		}
		else if (caracter == '-') {

			//verficando anterior
			if ((i - 1) <= 0) {
				//Serial.println(" No es un operador");
				Operando.concat(caracter);
			}
			else if ((i + 1) < posfija->length()) {
				char letrasig = posfija->charAt(i + 1);

				if (esNumero(letrasig)) {
					//Serial.println(" No es un operador");
					Operando.concat(caracter);
				}
				else {
					desapilaOperandos(&pila, &i, caracter);
				}
			}
			else {
				desapilaOperandos(&pila, &i, caracter);
			}

		}
		else {
			desapilaOperandos(&pila, &i, caracter);

		}

	}


	*result = (String)pila[pila.Count() - 1];
}

void Analizador::desapilaOperandos(List<float>* pila, size_t* i, char caracter) {

	float num1 = 0.0;
	float num = 0.0;
	num1 = pila->operator[](pila->Count() - 1);
	pila->RemoveLast();
	num = pila->operator[](pila->Count() - 1);
	pila->RemoveLast();

	//Serial.print("[");
	//Serial.print(num);
	//Serial.print(" ");
	//Serial.print(caracter);
	//Serial.print(" ");
	//Serial.print(num1);
	//Serial.println("]");


	num = Operacion(caracter, num, num1);
	pila->Add(num);
	*i = *i + 1;
}

float Analizador::Operacion(char operador, float a, float b)
{

	switch (operador)
	{
	case '^':
		return (float)pow(a, b);
		break;
	case '*':
		return a*b;
		break;
	case '%':
		return (int)a % (int)b;
		break;
	case '/':
		return a / b;
		break;
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	}

	return 0.0f;
}




boolean Analizador::esOperador(char letra)
{


	switch (letra)
	{
	case '^':
	case '*':
	case '%':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
		return true;
	}

	return false;
}
boolean Analizador::esY(char letra)
{
	if (letra == 'y') {
		return true;
	}
	return false;
}
boolean Analizador::esParC(char letra)
{
	if (letra == ')') {
		return true;
	}
	return false;
}
boolean Analizador::esParA(char letra)
{
	if (letra == '(') {
		return true;
	}
	return false;
}
boolean Analizador::esNumero(char letra)
{
	if ((letra > 47) && (letra < 58)) {
		return true;
	}


	switch (letra)
	{
	case 'x':
	case 'X':
	case 'y':
	case 'Y':
	case 'z':
	case 'Z':
		return true;
	}


	return false;
}
byte Analizador::prioridadExpresion(char operador)
{
	switch (operador)
	{
	case '^':
		return  4;
	case '*':
	case '%':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	case '(':
		return 5;
	}

	return 0;
}
byte Analizador::prioridadEnPila(char operador)
{
	switch (operador)
	{
	case '^':
		return  3;
	case '*':
	case '%':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	case '(':
		return 0;
	}

	return 0;
}
