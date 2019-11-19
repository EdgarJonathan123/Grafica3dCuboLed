
#include "grafica.h"
String infuncion = "z^2=x^2+y^2;-8;8;-8;8;0;8";
Graficador graf = Graficador(2, 3, 4);

void setup() { 
	Serial.begin(9600);
	graf.init();
	graf.SetFuncion(infuncion);
	//Serial.print("Si compilo o solo pajas :(");
}

void loop() {
	graf.actualizarData();
}

