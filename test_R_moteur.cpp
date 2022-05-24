#include "mbed.h"

#define PCLOCK 25e6;

PwmOut E1(P2_2);	// initialisation de E1 du moteur
PwmOut E2(P2_3);	// initialisation de E2 du moteur
AnalogIn Photo1(P0_23);    // initialisation de la diode 1 en entr�e
AnalogIn Photo2(P0_24);

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

void trajectoire()
{
	float diff = Photo1 - Photo2;
	if (diff<=0){
		E1.write(0.2);
		E2.write(0.6);
	} else {
		E1.write(0.6); 
		E2.write(0.2);
	}
}

void trajectoire2()
{
	float diff = Photo1 - Photo2; //diff�rence de luminosit� re�ue entre les deux capteurs centraux
	float valDeBase = 0.4;
	float coeff = 1;
	if (diff<0){
		//tourne vers capt2 (donc M1 > M2)
		E1.write(valDeBase - diff*coeff); 
		E2.write(valDeBase + diff*coeff);
	} else {
		//tourne vers capt1 (donc M1 > M2)
		E1.write(valDeBase - diff*coeff); 
		E2.write(valDeBase + diff*coeff);
	}
	// SI ON Y ARRIVE PAS FAIRE PAR PALIERS
}
	
int main (void)
 {
	 init_GPIO();
	 init_E1();
	 init_E2();
	 while(1){
		 trajectoire2();
	 }
	 
 }
