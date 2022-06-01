#include "mbed.h"


PwmOut E1(P2_2);	// initialisation de E1 du moteur droit
PwmOut E2(P2_3);	// initialisation de E2 du moteur gauche
DigitalIn Infra1(P2_4); //init de l'infra 
DigitalIn Infra2(P2_5);


void init_GPIO()
{
 LPC_GPIO0->FIODIR0 |= (1 << 6); //initialisation de M1 du moteur
 LPC_GPIO0->FIODIR0 |= (1 << 7); //initialisation de M2 du moteur
}
void init_E1()
{
 E1.period(0.01);
 E1.write(0.3); //gestion de la vitesse
 LPC_GPIO0->FIOSET0 = (1 << 6); //permet d'avancer
}

void init_E2()
{
 E2.period(0.01);
 E2.write(0.3); //gestion de la vitesse
 LPC_GPIO0->FIOSET0 = (1 << 7);
}

void diode()
{
	if (Infra1 ==0 and Infra2==0)
	{
		 E1.write(0.5);
		 E2.write(0.5);
	}
	else
	{
		 E1.write(0);
		 E2.write(0);
	}
}
	
int main (void)
 {
	 init_GPIO();
	 init_E1();
	 init_E2();
	 while(1){
			diode();
	 }
	 
 }
