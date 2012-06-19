
#include "INTRINS.H"


void Delay10Us(unsigned int t) //delay 50us
{
	t *= 14;
	while(--t)
	{
		_nop_();
		_nop_();
		_nop_();		
	}
 
}


void DelayMs(unsigned int ms)
{
	Delay10Us(20 * ms);
}