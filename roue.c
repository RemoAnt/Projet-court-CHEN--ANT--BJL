#include "mbed.h"


#define PCLOCK 25e6;

PwmOut E1(P2_2);
AnalogIn pot(A0);
 



void init_GPIO()
{
 LPC_GPIO0->FIODIR0 |= (1 << 7); //M1
 LPC_GPIO0->FIOCLR0 = 1;
}
void init_E1()
{
 E1.period(0.01);
 E1.write(0.5);
}


//extern "C" void Tim0IrqHandler()
//{
 //static float rapportCyclique = 0.5;
 //rapportCyclique += 0.1;
 //if(rapportCyclique > 1)
  //rapportCyclique = 0;
 //E1.write(rapportCyclique);
 //LPC_TIM0->IR = 1;
	
//}
extern "C" void Tim0IrqHandler()
{
 static float rapportCyclique = 0;
 if (pot>0 and pot <0.20f )
 {
  rapportCyclique += 0.1;
  E1.write(rapportCyclique);
  LPC_TIM0->IR = 1;
	
 }
 else if (pot>0.20f and pot <0.40f )
 {
  rapportCyclique += 0.5;
  E1.write(rapportCyclique);
  LPC_TIM0->IR = 1;
 }
}

 int main (void)
 ...
