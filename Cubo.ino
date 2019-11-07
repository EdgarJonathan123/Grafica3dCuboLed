#include "Grafica.h"


String inFuncion = "(x^2/4)+(y^2/8+2)+z^2=2^2*1;-9;9;-9;9;-30;45";

Graficador graf = Graficador(2, 3, 4);

void setup() {

	Serial.begin(9600);
	graf.init();

	//para usar el setFuncion 
	//usar un booleano para solo mandar a llamar cuando cambia la bandera 
	graf.SetFuncion(inFuncion);

}

void loop() {
	graf.actualizarData();
}