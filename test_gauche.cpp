#include "mbed.h"


PwmOut E1(P2_2);	// initialisation de E1 du moteur droit
PwmOut E2(P2_3);	// initialisation de E2 du moteur gauche


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
 LPC_GPIO0->FIOSET0 = (1 << 6); //permet d'avancer
}

void init_E2()
{
 E2.period(0.01);
 E2.write(0.1); //gestion de la vitesse
 LPC_GPIO0->FIOSET0 = (1 << 7);
}

	
int main (void)
 {
	 init_GPIO();
	 init_E1();
	 init_E2();

	 
 }
