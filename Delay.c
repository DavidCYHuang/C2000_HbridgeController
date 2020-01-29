#include "F2802x_Device.h"



void Delay_us(int32 D);
void Delay_ms(int32 D);


void Delay_us(int32 D)
{
    int32 i=D;
    for(;i;i--);
}

void Delay_ms(int32 D)
{
    Delay_us(D*1000);
}
