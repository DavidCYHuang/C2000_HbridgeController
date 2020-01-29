/**********************************************************************
* File: Gpio.c -- File for Lab 2, 3 and 4
* Devices: TMS320F2802x
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   03/30/09 - original
**********************************************************************/

//#include "DSP28x_Project.h"
#include "F2802x_Device.h"     // Headerfile Include File

/**********************************************************************
* Function: InitGpio()
*
* Description: Initializes the shared GPIO pins on the F2802x
**********************************************************************/
void InitGpio(void)
{
    asm(" EALLOW");                             // Enable EALLOW protected register access

//--- Group A pins
    GpioCtrlRegs.GPACTRL.all  = 0x00000000;     // QUALPRD = SYSCLKOUT for all group A GPIO
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 60 ;   // Sampling Period = 120 * TSYSCLKOUT ==> 2 us  (required for GPIO7)
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2 = 10 ;   // Sampling Period = 120 * TSYSCLKOUT ==> 2 us  (required for GPIO19)

    GpioCtrlRegs.GPAQSEL1.all = 0x00000000;     // No qualification for all group A GPIO 0-15


    GpioCtrlRegs.GPAQSEL2.all = 0x00000000;     // No qualification for all group A GPIO 16-31
    GpioCtrlRegs.GPADIR.all   = 0x00000000;     // All group A GPIO are inputs
    GpioCtrlRegs.GPAPUD.all   = 0xFFFFFFFF;     // Pullups disabled for Group A


    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;       // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;       // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3;       // Asynch input GPIO18 (SPICLKA)

    GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;         // Strobe Light
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;          // Raspberry Pi Reset
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;          // RTCC MF
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;          // Current sensor interrrupt


    GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1;        // 0=GPIO         1=EPWM1A     2=rsvd       3=rsvd  (used in Lab 3)
    GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1;        // 0=GPIO         1=EPWM1B     2=rsvd       3=COMP1OUT
    GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 1;        // 0=GPIO         1=EPWM2A     2=rsvd       3=rsvd
    GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1;        // 0=GPIO         1=EPWM2B     2=rsvd       3=COMP2OUT
    GpioCtrlRegs.GPAMUX1.bit.GPIO4  = 0;        // 0=GPIO         1=EPWM3A     2=rsvd       3=rsvd
    GpioCtrlRegs.GPAMUX1.bit.GPIO5  = 0;        // 0=GPIO         1=EPWM3B     2=rsvd       3=ECAP1
    GpioCtrlRegs.GPAMUX1.bit.GPIO6  = 0;        // 0=GPIO         1=EPWM4A     2=EPWMSYNCI  3=EPWMSYNCO
    GpioCtrlRegs.GPAMUX1.bit.GPIO7  = 0;        // 0=GPIO         1=EPWM4B     2=SCIRXDA    3=rsvd
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;        // 0=GPIO         1=TZ1        2=SCITXDA    3=rsvd

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;        // 0=GPIO         1=SPISIMOA   2=rsvd       3=TZ2
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;        // 0=GPIO         1=SPISOMIA   2=rsvd       3=TZ3
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;        // 0=GPIO         1=SPICLKA    2=SCITXDA    3=XCLKOUT
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;        // 0=GPIO/XCLKIN  1=SPISTEA    2=SCIRXDA    3=ECAP1
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;        // 0=GPIO         1=SCIRXDA    2=SDAA       3=TZ2
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;        // 0=GPIO         1=SCITXDA    2=SCLA       3=TZ3

//--- Group B pins
    GpioCtrlRegs.GPBCTRL.all  = 0x00000000;     // QUALPRD = SYSCLKOUT for all group B GPIO
    GpioCtrlRegs.GPBQSEL1.all = 0x00000000;     // No qualification for all group B GPIO 32-38
    GpioCtrlRegs.GPBDIR.all   = 0x00000000;     // All group B GPIO are inputs
    GpioCtrlRegs.GPBPUD.all   = 0x000000FF;     // All group B pullups disabled

    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;        // 0=GPIO               1=SDAA      2=EPWMSYNCI  3=ADCSOCAO
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;        // 0=GPIO               1=SCLA      2=EPWMSYNCO  3=ADCSOCBO
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;        // 0=GPIO               1=COMP2OUT  2=rsvd       3=rsvd
    GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 0;        // 0=GPIO (TDI)         1=rsvd      2=rsvd       3=rsvd
    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0;        // 0=GPIO (TMS)         1=rsvd      2=rsvd       3=rsvd
    GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 0;        // 0=GPIO (TDO)         1=rsvd      2=rsvd       3=rsvd
    GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 0;        // 0=GPIO/XCLKIN (TCK)  1=rsvd      2=rsvd       3=rsvd



// Analog I/O Mux pins
    GpioCtrlRegs.AIOMUX1.bit.AIO2 = 0;          // 0,1=AIO2             2,3=ADCINA2/COMP1A
    GpioCtrlRegs.AIOMUX1.bit.AIO4 = 0;          // 0,1=AIO4             2,3=ADCINA4/COMP2A
    GpioCtrlRegs.AIOMUX1.bit.AIO6 = 0;          // 0,1=AIO6             2,3=ADCINA6
    GpioCtrlRegs.AIOMUX1.bit.AIO10 = 0;         // 0,1=AIO10            2,3=ADCINB2/COMP1B
    GpioCtrlRegs.AIOMUX1.bit.AIO12 = 0;         // 0,1=AIO12            2,3=ADCINB4/COMP2B
    GpioCtrlRegs.AIOMUX1.bit.AIO14 = 0;         // 0,1=AIO14            2,3=ADCINB6

    GpioCtrlRegs.AIODIR.bit.AIO2 = 0;           // AIO2 is an input (when selected as digital function)
    GpioCtrlRegs.AIODIR.bit.AIO4 = 0;           // AIO2 is an input (when selected as digital function)
    GpioCtrlRegs.AIODIR.bit.AIO6 = 0;           // AIO2 is an input (when selected as digital function)
    GpioCtrlRegs.AIODIR.bit.AIO10 = 0;          // AIO2 is an input (when selected as digital function)
    GpioCtrlRegs.AIODIR.bit.AIO12 = 0;          // AIO2 is an input (when selected as digital function)
    GpioCtrlRegs.AIODIR.bit.AIO14 = 0;          // AIO2 is an input (when selected as digital function)
/*
//--- External interrupt selection
    GpioIntRegs.GPIOXINT1SEL.all = 0x0000;      // GPIO0 is XINT1 source
    GpioIntRegs.GPIOXINT2SEL.all = 0x0000;      // GPIO0 is XINT2 source
    GpioIntRegs.GPIOXINT3SEL.all = 0x0000;      // GPIO0 is XINT3 source

    XIntruptRegs.XINT1CR.all = 0x0000;          // XINT1 disabled
    XIntruptRegs.XINT2CR.all = 0x0000;          // XINT2 disabled
    XIntruptRegs.XINT3CR.all = 0x0000;          // XINT3 disabled

//--- Low-power mode selection
    GpioIntRegs.GPIOLPMSEL.all = 0x00000000;    // No pin selected for HALT and STANBY wakeup (reset default)

*/




    /* GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;       // Enable pull-up
     GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;         // Enable pull-up
     GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;*/

     GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;       // Asynch input
     GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;       // Asynch input

     GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 2;        // Qualification using 6 samples . RTCC MFC
     GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 2;       // Qualification using 6 samples
                                                 // (required for protection circuit)



     GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;         // Enable pull-up for GPIO32 (SDAA)
     GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;         // Enable pull-up for GPIO33 (SCLA)


     GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;       // Asynch input GPIO32 (SDAA)
     GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;       // Asynch input GPIO33 (SCLA)



////////////////////////////////////////////////////////////////////////////////////////////////
     GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;
     GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;
     GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;   // Enable Chip

     GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
     GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
     GpioDataRegs.GPASET.bit.GPIO4 = 1;   // Write Protection disabled
 //////////////////////////////////////////////////////////////////////////////////////////



//--- Finish up
    asm(" EDIS");                               // Disable EALLOW protected register access

} // end InitGpio()


//--- end of file -----------------------------------------------------
