#include "grafica.h"


String infuncion = "(x^2/4)+(y^2/8+2)+z^2=2^2*1;0;9;0;9;-30;9";
Graficador graf = Graficador(2, 3, 4);

void setup() {

	Serial.begin(9600);
	graf.init();
	graf.SetFuncion(infuncion);
}

void loop() {
	graf.actualizarData();
}


