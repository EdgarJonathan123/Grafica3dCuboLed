#include "Grafica.h"
byte rclock = 2;
byte latch	= 3; 
byte data	= 4; 

Graficador graf = Graficador(rclock, latch, data);


void setup() {
	Serial.begin(9600);
	graf.init();
	graf.actualizarData();
	//graf.getTamanio(-100,-8);
	//graf.imprimirCapa();
}

void loop() {
	graf.enviarData();
}