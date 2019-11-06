#include "Grafica.h"


String inFuncion = "(x^2/4)+(y^2/8+2)+z^2=2^2*1;-9;9;-9;9;-10;10";
Graficador graf = Graficador(2, 3, 4);

void setup() {
	Serial.begin(9600);
	graf.init();
	graf.SetFuncion(inFuncion);
}

void loop() {
	graf.actualizarData();
	
}


//byte rclock = 2; // to all registers
//byte latch = 3; // to all registers
//byte data = 4; // to first register
//
//
//
//void setup() {
//	pinMode(latch, OUTPUT);
//	pinMode(rclock, OUTPUT);
//	pinMode(data, OUTPUT);
//}
//
//void loop() {
//	setear(1, 1, 1, 255, 255,128, 128,128, -128);
//	delay(4000);
//	
//	//setear(1, 1, 1, 1, 1, 1, 1, 1, B10000000);
//	//delay(1000);
//}
//
//void setear(int fila0, int fila1, int fila2, int fila3, int fila4, int fila5, int fila6, int fila7, int niveles) {
//	digitalWrite(latch, LOW);
//	shiftOut(data, rclock, LSBFIRST, niveles); //Esta data queda en el ultimo shift register el que tiene el arreglo de transistores darlington ULN2803
//	shiftOut(data, rclock, LSBFIRST, fila7); //Esta data queda en el penultimo shift register
//	shiftOut(data, rclock, LSBFIRST, fila6);
//	shiftOut(data, rclock, LSBFIRST, fila5);
//	shiftOut(data, rclock, LSBFIRST, fila4);
//	shiftOut(data, rclock, LSBFIRST, fila3);
//	shiftOut(data, rclock, LSBFIRST, fila2);
//	shiftOut(data, rclock, LSBFIRST, fila1);
//	shiftOut(data, rclock, LSBFIRST, fila0); //Esta data queda en el primer shift register
//	digitalWrite(latch, HIGH);
//
//}