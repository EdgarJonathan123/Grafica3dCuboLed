
#include "grafica.h"


//#include "Analisis.h"

String infuncion = "x^2+y^2+z^2=9^2;-10;10;-10;10;-10;10";
Graficador graf = Graficador(2, 3, 4);

//String Ecuacion = "y^3=27";
//boolean fxvalida = false;
//float result = 0.0;
//
//Analizador ana = Analizador();

char dato = ' ';
String cadena = "";
boolean hayfuncion = false;



void setup() {

	Serial.begin(9600);
	//while (!Serial) {}
	//Serial.print("OK");
	//Serial1.begin(9600);


	graf.init();

	graf.SetFuncion(infuncion);



	//Serial.print("Ecuacion : ");
	//Serial.println(Ecuacion);

	//ana.Solve(&Ecuacion, &result, &fxvalida);

	//if (fxvalida) {
	//	Serial.print("Solucion: ");
	//	Serial.println(result);
	//}
	//else {
	//	Serial.print("La solucion no se encuentra en los reales");
	//}

}

void loop() {


	//if (Serial1.available()) {
	//	dato = Serial1.read();

	//	if (dato == 64) { //si recibe @ es fin de la cadena
	//		hayfuncion = true;
	//	}
	//	else {//si no es fin concatena
	//		cadena.concat(dato);
	//	}
	//}

	//;
	//if (hayfuncion) {
	//	Serial.println(cadena);
	//	graf.SetFuncion(cadena);
	//	cadena = "";
	//	dato = ' ';
	//	hayfuncion = false;
	//}

	graf.actualizarData();
}