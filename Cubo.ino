
#include "Grafica.h"
byte rclock = 2; // to all registers
byte latch = 3; // to all registers
byte data = 4; // to first register


Graficador* graf = new Graficador(rclock, latch, data);


void setup() {
	Serial.begin(9600);
	pinMode(latch, OUTPUT);
	pinMode(rclock, OUTPUT);
	pinMode(data, OUTPUT);
}

void loop() {
	digitalWrite(latch, LOW);
	shiftOut(data, rclock, LSBFIRST, B01110000); //Esta data queda en el ultimo shift register el que tiene el arreglo de transistores darlington ULN2803
	shiftOut(data, rclock, LSBFIRST, B01110000); //Esta data queda en el penultimo shift register
	shiftOut(data, rclock, LSBFIRST, B01110010);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, B01110000);
	shiftOut(data, rclock, LSBFIRST, B01110001); //Esta data queda en el primer shift register
	digitalWrite(latch, HIGH);

}