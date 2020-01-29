// TI File $Revision: /main/3 $
// Checkin $Date: September 23, 2009   15:34:12 $
//###########################################################################
//
// FILE:   DSP2802x_EPwm.c
//
// TITLE:  DSP2802x EPwm Initialization & Support Functions.
//
//###########################################################################
// $TI Release: LaunchPad f2802x Support Library v100 $
// $Release Date: Wed Jul 25 10:45:39 CDT 2012 $
//###########################################################################

#include "F2802x_Device.h"     // Headerfile Include File







#define Do_Nothing  0
#define Clear       1
#define Set         2
#define Toggle      3


void Setup_ePWM4()
{
    int32 Frequency =  1000;
    int32 Peroid   =   (int32)(60e6 / Frequency);
    int32 Duty_cycle = 50;
    int32 CMPA_Val  =  (int32)(Duty_cycle*Peroid/100);

    //---------------------------------------------------------------------
    //--- Configure ePWM4
    //---------------------------------------------------------------------

    EPwm4Regs.TBCTL.bit.CTRMODE = 0x3;  // Disable the Counter
    EPwm4Regs.TBCTL.bit.FREE_SOFT = 3;  // Ignore Emulation suspend
    EPwm4Regs.TBCTL.bit.PHSDIR = 0;     // Count down after sync. event, only in up/down mode
    EPwm4Regs.TBCTL.bit.CLKDIV = 0;     // CLKDIV= 1      TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0;  // HSPCLKDIV= 1   TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwm4Regs.TBCTL.bit.SWFSYNC = 0;    // NO Software Forced Synchronization Pulse
    EPwm4Regs.TBCTL.bit.SYNCOSEL = 3;   // Sync-out disabled
    EPwm4Regs.TBCTL.bit.PRDLD = 0;      // Period Register load form its Shadow
    EPwm4Regs.TBCTL.bit.PHSEN = 1;      // Phase shift Enabled
    EPwm4Regs.TBCTL.bit.CTRMODE = 0;    // Up-count mode

    EPwm4Regs.TBCTR = 0x0000;               // Clear timer counter
    EPwm4Regs.TBPRD = Peroid;               // Set timer period
    EPwm4Regs.TBPHS.half.TBPHS = 0;         // Set timer phase
    EPwm4Regs.CMPA.half.CMPA = CMPA_Val;    // Set PWM duty cycle


    EPwm4Regs.CMPCTL.bit.SHDWBFULL = 0;       // CMPB Shadow Register Full Status Flag
    EPwm4Regs.CMPCTL.bit.SHDWAFULL = 0;       // CMPA Shadow Register Full Status Flag
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = 0;     // CMPB Shadow mode
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = 0;     // CMPA Shadow mode
    EPwm4Regs.CMPCTL.bit.LOADBMODE = 0;      // CMPB Load From Shadow Select Mode : Load on CTR = Zero
    EPwm4Regs.CMPCTL.bit.LOADAMODE = 2;     // CMPA Load From Shadow Select Mode : Load on CTR = Zero

    EPwm4Regs.AQCTLA.bit.CBD = Do_Nothing;
    EPwm4Regs.AQCTLA.bit.CBU = Do_Nothing;
    EPwm4Regs.AQCTLA.bit.CAD = Do_Nothing;
    EPwm4Regs.AQCTLA.bit.CAU = Clear;
    EPwm4Regs.AQCTLA.bit.PRD = Do_Nothing;
    EPwm4Regs.AQCTLA.bit.ZRO = Set;

    EPwm4Regs.AQSFRC.all = 0x0000;      // Action-qualifier s/w force register



    EPwm4Regs.DBCTL.bit.HALFCYCLE = 1;     // Resolution is doubled
    EPwm4Regs.DBCTL.bit.IN_MODE  = 0;      // EPWMxA is the source for both falling and rising edge
    EPwm4Regs.DBCTL.bit.POLSEL   = 2;      // Active high complementary (AHC). EPWMxB is inverted.
    EPwm4Regs.DBCTL.bit.OUT_MODE = 3;

    EPwm4Regs.DBRED = 12;     // 100nS Rising  Edge delay
    EPwm4Regs.DBFED = 12;     // 100nS Falling Edge delay

    EPwm4Regs.PCCTL.bit.CHPEN = 0;      // PWM chopper unit disabled
    EPwm4Regs.TZDCSEL.all = 0x0000;     // All trip zone and DC compare actions disabled
    EPwm4Regs.TBCTL.bit.CTRMODE = 0x00;  // Enable the timer in count up-count mode


    /****************************************ADC Triggering*****************************************/

    EPwm4Regs.ETSEL.all=0x00000000;
    EPwm4Regs.ETSEL.bit.SOCAEN = 1;     // Enable EPWM2SOCA pulse.
    EPwm4Regs.ETSEL.bit.SOCASEL = 2;    //Enable event time-base counter equal to period


    EPwm4Regs.ETPS.all = 0x00000000;
    EPwm4Regs.ETPS.bit.SOCAPRD = 1;

    EPwm4Regs.DBCTL.bit.OUT_MODE = 3;
}



void Setup_ePWM2()
{
    int32 Frequency =  85000;
    int32 Peroid   =   (int32)(60e6 / Frequency);
    int32 Duty_cycle = 50;
    int32 CMPA_Val  =  (int32)(Duty_cycle*Peroid/100);

    //---------------------------------------------------------------------
    //--- Configure ePWM2
    //---------------------------------------------------------------------

    EPwm2Regs.TBCTL.bit.CTRMODE = 0x3;  // Disable the Counter
    EPwm2Regs.TBCTL.bit.FREE_SOFT = 3;  // Ignore Emulation suspend
    EPwm2Regs.TBCTL.bit.PHSDIR = 0;     // Count down after sync. event, only in up/down mode
    EPwm2Regs.TBCTL.bit.CLKDIV = 0;     // CLKDIV= 1      TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;  // HSPCLKDIV= 1   TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwm2Regs.TBCTL.bit.SWFSYNC = 0;    // NO Software Forced Synchronization Pulse
    EPwm2Regs.TBCTL.bit.SYNCOSEL = 3;   // Sync-out disabled
    EPwm2Regs.TBCTL.bit.PRDLD = 0;      // Period Register load form its Shadow
    EPwm2Regs.TBCTL.bit.PHSEN = 1;      // Phase shift Enabled
    EPwm2Regs.TBCTL.bit.CTRMODE = 0;    // Up-count mode

    EPwm2Regs.TBCTR = 0x0000;               // Clear timer counter
    EPwm2Regs.TBPRD = Peroid;               // Set timer period
    EPwm2Regs.TBPHS.half.TBPHS = 0;         // Set timer phase
    EPwm2Regs.CMPA.half.CMPA = CMPA_Val;    // Set PWM duty cycle


    EPwm2Regs.CMPCTL.bit.SHDWBFULL = 0;       // CMPB Shadow Register Full Status Flag
    EPwm2Regs.CMPCTL.bit.SHDWAFULL = 0;       // CMPA Shadow Register Full Status Flag
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = 0;     // CMPB Shadow mode
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0;     // CMPA Shadow mode
    EPwm2Regs.CMPCTL.bit.LOADBMODE = 0;      // CMPB Load From Shadow Select Mode : Load on CTR = Zero
    EPwm2Regs.CMPCTL.bit.LOADAMODE = 2;     // CMPA Load From Shadow Select Mode : Load on CTR = Zero

    EPwm2Regs.AQCTLA.bit.CBD = Do_Nothing;
    EPwm2Regs.AQCTLA.bit.CBU = Do_Nothing;
    EPwm2Regs.AQCTLA.bit.CAD = Do_Nothing;
    EPwm2Regs.AQCTLA.bit.CAU = Clear;
    EPwm2Regs.AQCTLA.bit.PRD = Do_Nothing;
    EPwm2Regs.AQCTLA.bit.ZRO = Set;

    EPwm2Regs.AQSFRC.all = 0x0000;      // Action-qualifier s/w force register



    EPwm2Regs.DBCTL.bit.HALFCYCLE = 1;     // Resolution is doubled
    EPwm2Regs.DBCTL.bit.IN_MODE  = 0;      // EPWMxA is the source for both falling and rising edge
    EPwm2Regs.DBCTL.bit.POLSEL   = 2;      // Active high complementary (AHC). EPWMxB is inverted.
    EPwm2Regs.DBCTL.bit.OUT_MODE = 3;

    EPwm2Regs.DBRED = 12;     // 100nS Rising  Edge delay
    EPwm2Regs.DBFED = 12;     // 100nS Falling Edge delay

    EPwm2Regs.PCCTL.bit.CHPEN = 0;      // PWM chopper unit disabled
    EPwm2Regs.TZDCSEL.all = 0x0000;     // All trip zone and DC compare actions disabled


    EALLOW;

  //  EPwm2Regs.TZSEL.bit.OSHT1 = 1;      // Enable TZ1 as a one-shot trip source for this ePWM module

    EPwm2Regs.TZCTL.bit.TZA  = 2;       // Force EPWMxA to a low state
    EPwm2Regs.TZCTL.bit.TZB  = 2;       // Force EPWMxB to a low state

    EDIS;


    EPwm2Regs.TBCTL.bit.CTRMODE = 0x00;  // Enable the timer in count up-count mode

    /****************************************ADC Triggering*****************************************/

}



void Setup_ePWM1()
{

    int32 Frequency =  85000;
    int32 Peroid   =   (int32)(60e6 / Frequency);
    int32 Duty_cycle = 50;
    int32 CMPA_Val  =  (int32)(Duty_cycle*Peroid/100);

    //---------------------------------------------------------------------
    //--- Configure ePWM1 for 85 kHz symmetric PWM on EPWM1A pin
    //---------------------------------------------------------------------

    EPwm1Regs.TBCTL.bit.CTRMODE = 0x3;  // Disable the Counter
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 3;  // Ignore Emulation suspend
    EPwm1Regs.TBCTL.bit.PHSDIR = 0;     // Count down after sync. event, only in up/down mode
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;     // CLKDIV= 1      TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;  // HSPCLKDIV= 1   TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwm1Regs.TBCTL.bit.SWFSYNC = 0;    // NO Software Forced Synchronization Pulse
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 1;   // Sync-out when CTR = 0
    EPwm1Regs.TBCTL.bit.PRDLD = 0;      // Period Register load form its Shadow
    EPwm1Regs.TBCTL.bit.PHSEN = 0;      // Phase shift disabled
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;    // Up-count mode

    EPwm1Regs.TBCTR = 0x0000;               // Clear timer counter
    EPwm1Regs.TBPRD = Peroid;               // Set timer period
    EPwm1Regs.TBPHS.half.TBPHS = 0x0000;    // Set timer phase
    EPwm1Regs.CMPA.half.CMPA = CMPA_Val;  // Set PWM duty cycle


    EPwm1Regs.CMPCTL.bit.SHDWBFULL = 0;       // CMPB Shadow Register Full Status Flag
    EPwm1Regs.CMPCTL.bit.SHDWAFULL = 0;       // CMPA Shadow Register Full Status Flag
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0;     // CMPB Shadow mode
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;     // CMPA Shadow mode
    EPwm1Regs.CMPCTL.bit.LOADBMODE = 0;      // CMPB Load From Shadow Select Mode : Load on CTR = Zero
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 2;     // CMPA Load From Shadow Select Mode : Load on CTR = Zero

    EPwm1Regs.AQCTLA.bit.CBD = Do_Nothing;
    EPwm1Regs.AQCTLA.bit.CBU = Do_Nothing;
    EPwm1Regs.AQCTLA.bit.CAD = Do_Nothing;
    EPwm1Regs.AQCTLA.bit.CAU = Clear;
    EPwm1Regs.AQCTLA.bit.PRD = Do_Nothing;
    EPwm1Regs.AQCTLA.bit.ZRO = Set;

    EPwm1Regs.AQSFRC.all = 0x0000;      // Action-qualifier s/w force register



    EPwm1Regs.DBCTL.bit.HALFCYCLE = 1;     // Resolution is doubled
    EPwm1Regs.DBCTL.bit.IN_MODE  = 0;      // EPWMxA is the source for both falling and rising edge
    EPwm1Regs.DBCTL.bit.POLSEL   = 2;      // Active high complementary (AHC). EPWMxB is inverted.
    EPwm1Regs.DBCTL.bit.OUT_MODE = 3;

    EPwm1Regs.DBRED = 12;     // 100nS Rising  Edge delay
    EPwm1Regs.DBFED = 12;     // 100nS Falling Edge delay

    EPwm1Regs.PCCTL.bit.CHPEN = 0;      // PWM chopper unit disabled


    EPwm1Regs.TZDCSEL.all = 0x0000;     // All trip zone and DC compare actions disabled


    EALLOW;

   // EPwm1Regs.TZSEL.bit.OSHT1 = 1;      // Enable TZ1 as a one-shot trip source for this ePWM module

    EPwm1Regs.TZCTL.bit.TZA  = 2;       // Force EPWMxA to a low state
    EPwm1Regs.TZCTL.bit.TZB  = 2;       // Force EPWMxB to a low state

    EDIS;


    EPwm1Regs.TBCTL.bit.CTRMODE = 0x00;  // Enable the timer in count up-count mode


}

//---------------------------------------------------------------------------
// InitEPwm:
//---------------------------------------------------------------------------
// This function initializes the EPwm(s) to a known state.
//
void InitEPwm(void)
{

//---------------------------------------------------------------------
//--- Must disable the clock to the ePWM modules if you
//--- want all ePMW modules synchronized.
//---------------------------------------------------------------------
    asm(" EALLOW");                     // Enable EALLOW protected register access
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    asm(" EDIS");                       // Disable EALLOW protected register access


    Setup_ePWM1();
    Setup_ePWM2();
    //Setup_ePWM4();

    asm(" EALLOW");                         // Enable EALLOW protected register access
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;  // TBCLK to ePWM modules enabled
    asm(" EDIS");                           // Disable EALLOW protected register access

} // end InitEPwm()




void InitEPwm1Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)

/* Configure EPwm-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

void InitEPwm2Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)

/* Configure EPwm-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

    EDIS;
}

void InitEPwm3Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Disable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Disable pull-up on GPIO5 (EPWM3B)

/* Configure EPwm-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM3 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    EDIS;
}

#if DSP28_EPWM4
void InitEPwm4Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;    // Disable pull-up on GPIO7 (EPWM4B)

/* Configure EPWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM4 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B

    EDIS;
}
#endif // endif DSP28_EPWM4

//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as EPwm Synch pins
//

void InitEPwmSyncGpio(void)
{

//   EALLOW;

/* Configure EPWMSYNCI  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;// Enable pull-up on GPIO32 (EPWMSYNCI)

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Configures GPIO6 for EPWMSYNCI operation
// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Configures GPIO32 for EPWMSYNCI operation.

/* Configure EPWMSYNC0  */

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWMSYNCO)
// GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;    // Disable pull-up on GPIO33 (EPWMSYNCO)

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Configures GPIO6 for EPWMSYNCO
// GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;   // Configures GPIO33 for EPWMSYNCO

}

//---------------------------------------------------------------------------
// Example: InitTzGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitTzGpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
   GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ2)
// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ2)
   GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ3)
// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ3)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ2)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ3)


/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ2
// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ2
   GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ3
// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ3

   EDIS;

}

//===========================================================================
// End of file.
//===========================================================================
