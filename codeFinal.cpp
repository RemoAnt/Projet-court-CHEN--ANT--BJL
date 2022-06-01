#include "mbed.h"


PwmOut E1(P2_2);	// initialisation de E1 du moteur droit
PwmOut E2(P2_3);	// initialisation de E2 du moteur gauche
AnalogIn Photo1(P0_23);    // initialisation de la diode 1 en entr�e
AnalogIn Photo2(P0_24);    //initialisation de la diode 2 en entr�e
AnalogIn Photo3(P1_30);    // initialisation de la photor�sistance de priorit� � droite
AnalogIn Photo4(P1_31);		// initialisation de la photor�sistance pour diff�rencier l'intersection et la ligne de priorit�
DigitalIn Infra1(P2_4); //init de l'infrarouge
DigitalIn Infra2(P2_5);



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

void trajectoire2(float diff) //fonction qui change le vitesse de chaque roue selon la diff�rence entre les 2 photor�sistances
{
	float diff1 = diff - Photo1 + Photo2 ; //diff�rence de luminosit� re�ue entre les deux capteurs centraux 
	float valDeBase = 0.3;	// si pile charg�e r�duire la vitesse
	float coeff = 15;			// coeff proportionnelle � la vitesse sinon hors piste
	
	if (diff1<0)
    {
		//tourne vers capt2 (donc M1 > M2) 
		//tourne � gauche
		E1.write(valDeBase + diff1*coeff); 
		E2.write(valDeBase - 0.5*diff1*coeff); //acc�leration plus basse
	} 
    else 
    {
		//tourne vers capt1 (donc M1 > M2)
		//tourne � droite
		E1.write(valDeBase + 0.5*diff1*coeff*1.75); //acc�leration plus basse
		E2.write(valDeBase - diff1*coeff*1.75);
	}
}

//void trajectoire3() //alternatif de trajectoire2 en palier
//{
//	float diff = Photo2 - Photo1 ; //diff�rence de luminosit� re�ue entre les deux capteurs centraux
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

void prioriteDroite(float diff){
	if (Infra1==0){
		
				E1.write(0);
				E2.write(0);
	}
	else if (Photo3>0.89)	// difficile � moduler (essayer de r�ussir intersetions ???)
	{
		if(Infra2 == 0){
			E1.write(0);
			E2.write(0);
			for(int i = 0; i<100000000; i++); //attendre environ 6sec si il y a qqn a priort�
			trajectoire2(diff);
		}
		else 
		{
			trajectoire2(diff);
		}
	}
	else {
		trajectoire2(diff);
	}
}

int main (void)
 {
	 init_GPIO();
	 init_E1();
	 init_E2();
	 float Sdiff; //permet de calibrer les photos r�sistances
	 for(int i=0; i<100; i++){
			Sdiff = Sdiff + Photo1 - Photo2;
	 }
	 float diff = Sdiff/100;  //Moyenne des 100 �talonnages
	 
	 while(1){
			prioriteDroite(diff);
	 }
	 
 }
