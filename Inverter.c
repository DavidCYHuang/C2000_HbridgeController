#include "F2802x_Device.h"
#include "Inverter.h"


extern void Strobe_Light(int Status);
extern void RaspPi_Reset(int Status);
extern void Sci_Msg(char * msg);
extern void Delay_us(int32 D);
extern void Delay_ms(int32 D);



extern int Inverter_Status;
extern int Current_Protection_Status;
extern char M[100];



void Force_OneShot()
{
    EALLOW;
        EPwm1Regs.TZFRC.bit.OST = 1;
        EPwm2Regs.TZFRC.bit.OST = 1;
    EDIS;
}
void Clear_OneShot()
{
    EALLOW;
        EPwm1Regs.TZCLR.bit.OST=1;
        EPwm2Regs.TZCLR.bit.OST=1;
    EDIS;
 }


void PSM_ON ()  // Phase shift modulation ON
{
    int i=0;

    if (EPwm1Regs.TZFLG.bit.OST == 1 || EPwm1Regs.TZFLG.bit.OST == 1)
    {
        EPwm2Regs.TBPHS.half.TBPHS = 0;
        Clear_OneShot();
    }
    i =  EPwm2Regs.TBPHS.half.TBPHS ;
    for (; i < 313 ; i++)                   //352 represents 180 degrees. 160 degree =
      {
         EPwm2Regs.TBPHS.half.TBPHS = i;    // Set timer phase
         Delay_us(100);
      }
}




void PSM_OFF ()  // Phase shift modulation ON
{
    int i=0;

    i = EPwm2Regs.TBPHS.half.TBPHS;        // current Phase Shift

    for (; i ; i--)
    {
        EPwm2Regs.TBPHS.half.TBPHS = i;    // Set timer phase
        Delay_us(100);
    }
    Delay_ms(100);
    Force_OneShot();
}



void Inverter(int S)         // S is status command ; S = 1 turns ON the inverter and S=0 turns it OFF
{
    if (S == 1 && Current_Protection_Status == 0)
    {
        PSM_ON ();
        Inverter_Status = 1;
        Strobe_Light(1);
    }
    else
    {
        PSM_OFF ();
        Inverter_Status = 0;
        Strobe_Light(0);
    }
}


