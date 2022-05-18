#include "mbed.h"

#define PCLOCK 25e6;

PwmOut E1(P2_2);	// initialisation de E1 du moteur
PwmOut E2(P2_3);	// initialisation de E2 du moteur
//AnalogIn D1(P0.6);    // initialisation de la diode 1 en entrée
 
void init_GPIO()
{
 LPC_GPIO0->FIODIR0 |= (1 << 6); //initialisation de M1 du moteur
 LPC_GPIO0->FIODIR0 |= (1 << 7); //initialisation de M2 du moteur
 //LPC_GPIO0->FIOCLR0 = 1;
}
void init_E1()
{
 E1.period(0.01);
 E1.write(0.5); //gestion de la vitesse
 LPC_GPIO0->FIOCLR0 = (1 << 6); //permet d'avancer
}

void init_E2()
{
 E2.period(0.01);
 E2.write(0.5); //gestion de la vitesse
 LPC_GPIO0->FIOSET0 = (1 << 7); //permet de reculer
}

 int main (void)
 {
	 init_GPIO();
	 init_E1();
	 init_E2();
 }
 
