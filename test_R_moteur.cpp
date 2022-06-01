#include "mbed.h"


PwmOut E1(P2_2);	// initialisation de E1 du moteur droit
PwmOut E2(P2_3);	// initialisation de E2 du moteur gauche
AnalogIn Photo1(P0_23);    // initialisation de la diode 1 en entrée
AnalogIn Photo2(P0_24);    //initialisation de la diode 2 en entrée



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
 E2.write(0.5); //gestion de la vitesse
 LPC_GPIO0->FIOSET0 = (1 << 7);
}

void trajectoire() // fonction test du changement de direction 
{
	float diff = Photo1 - Photo2;
	if (diff<=0){
		E1.write(0.1);
		E2.write(0.5);
	} else {
		E1.write(0.5); 
		E2.write(0.1);
	}
}

void trajectoire2(float diff) //fonction qui change le vitesse de chaque roue selon la différence entre les 2 photorésistances
{
	float diff1 =diff - Photo1 + Photo2 ; //différence de luminosité reçue entre les deux capteurs centraux 
	float valDeBase = 0.4;
	float coeff = 60;
	if (diff1<0)
    {
		//tourne vers capt2 (donc M1 > M2) 
		//tourne à gauche
		E1.write(valDeBase + diff1*coeff); 
		E2.write(valDeBase - diff1*coeff);
	} 
    else 
    {
		//tourne vers capt1 (donc M1 > M2)
		//tourne à droite
		E1.write(valDeBase + diff1*coeff); 
		E2.write(valDeBase - diff1*coeff);
	}
}

//void trajectoire3() //alternatif de trajectoire2 en palier
//{
//	float diff = Photo2 - Photo1 ; //différence de luminosité reçue entre les deux capteurs centraux
//	if (diff<-0.5)
//  {
//	    E1.write(0.5); 
//		E2.write(0.5);
//	}
//   else if(diff>0.5)
//  {
//		E1.write(0.3); 
//		E2.write(0.7);
//	}
//	else
//	{
//		E1.write(0.7); 
//		E2.write(0.3);
//	}
//}
	
int main (void)
 {

	 init_GPIO();
	 init_E1();
	 init_E2();
	 float diff = Photo1 - Photo2; //permet de calibrer les photos résistances
	 while(1){
			trajectoire2(diff);
	 }
	 
 }
