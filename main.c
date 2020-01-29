// USU Setup interface board
// Vahid Zahiri  06/2019
// All required header files are located in "Include" folder in the project directory


#include "F2802x_Device.h"
#include "USU_Global_Prototypes.h"


////////////////////////////////////////////////////////////////////////////////////////
int32 T_ON = 10;                              // in Second
int32 T_OFF = 10;                                // in Second

const int Current_Protection_Timer_Setpoint = 10;     // in Second

////////////////////////////////// Global Variables//////////////////////////////////////

uint16_t LoopCount;
int16 Counter=0;
uint16_t ErrorCount;
Uint16 ReceivedChar;
int32 Inverter_timer=0;
int Current_Protection_Status = 0;
int Current_Protection_Timer = 0;
int Cmd_Accepted = 0;




int Inverter_Status = 0;




void Strobe_Light(int Status)
{
    if (Status == 1)
            GpioDataRegs.GPASET.bit.GPIO12 = 1;
    if (Status == 0)
            GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;

}

void RaspPi_Reset(int Status)
{
    if (Status == 1)
            GpioDataRegs.GPASET.bit.GPIO6 = 1;
    if (Status == 0)
            GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;

}


void XInt_Setup()
{

    EALLOW;

    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 19;   // XINT1 is GPIO12

    EDIS;

    XIntruptRegs.XINT1CR.bit.POLARITY = 1;      // Rising edge interrupt

    XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable XINT1

    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;  // Enable
    IER |= 0x0001;

}




void Timer0_Setup()
{

    CpuTimer0Regs.TCR.bit.TSS = 1;   // StopCpuTimer0() can be used alternatively
    CpuTimer0Regs.TCR.bit.TIF=1;     // This flag gets set when the CPU-timer decrements to zero.
    CpuTimer0Regs.TCR.bit.TIE=1;     // The CPU-Timer interrupt is enabled
    CpuTimer0Regs.TCR.bit.FREE=1;    // Free run
    CpuTimer0Regs.TCR.bit.SOFT=1;

    // Prescale Register

    CpuTimer0Regs.TPR.bit.TDDR   = 0xFF;   //   1sec -->  60e6 = 0x03938700
    CpuTimer0Regs.TPRH.bit.TDDRH = 0xFF;
    CpuTimer0Regs.PRD.all = 915;           //

    CpuTimer0Regs.TCR.bit.TRB = 1;         // ReloadCpuTimer0 can be used alternatively



    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;     // Enable TINT0 (INTx7) Interrupt in PIE group 1

    IER |= 0x0001;                         // Enable PIE group 1


}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

void main(void)
{



    #ifdef _FLASH
      memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
    #endif

   InitSysCtrl();  //Initialize System Control:


   // Disable CPU interrupts for initialization
   DINT;

   InitPieCtrl();                             // Initialize PIE control registers to their default state.
   IER = 0x0000;                              // Disable CPU interrupts and clear all CPU interrupt flags:
   IFR = 0x0000;
   InitPieVectTable();                        // Initialize the PIE vector table with pointers to the shell Interrupt
                                              // Service Routines (ISR).
   InitGpio();
   XInt_Setup();

   InitEPwm1Gpio();
   InitEPwm2Gpio();
   Timer0_Setup();

   InitEPwm();




   EINT;                                     //--- Enable global interrupts
   Clear_OneShot();                          // Clear TZ Flag if its already set
   CpuTimer0Regs.TCR.bit.TSS = 0;

   while(1)
   {

       //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*   Inverter(0);
       Delay_ms(1000);
       Inverter(1);
       Delay_ms(1000);
*/

       /*
       //////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (Inverter_timer >= 0 &&   Inverter_timer <= T_OFF)
          {
            Inverter(0);
          }
        else if (Inverter_timer > T_OFF  &&  ( Inverter_timer < T_OFF + T_ON))
          {
            Inverter(1);
          }
        else if (Inverter_timer >= T_OFF + T_ON)
            Inverter_timer=0;

       //////////////////////////////////////////////////////////////////////////////////////////////////////
       */
       Inverter(1);


   }

}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INT1.4
interrupt void  XINT1_ISR(void)
{
/*
    EALLOW;
        EPwm1Regs.TZFRC.bit.OST = 1;
        EPwm2Regs.TZFRC.bit.OST = 1;
    EDIS;

    Current_Protection_Status = 1;
    Current_Protection_Timer = 0;
    Inverter(0);

  // To receive more interrupts from this PIE group, acknowledge this interrupt
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INT1.7
interrupt void  TINT0_ISR(void)      // CPU-Timer 0
{

   Inverter_timer++;

   /////////////////////////////////Protection ////////////////////
   /*
   Current_Protection_Timer += Current_Protection_Status;
   if (Current_Protection_Timer >= Current_Protection_Timer_Setpoint)
   {
       Current_Protection_Status = 0;
       Current_Protection_Timer = 0;
       Clear_OneShot();
   }
   */
   ///////////////////////////////////////////////////////////////


   CpuTimer0Regs.TCR.bit.TIF = 1;
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

