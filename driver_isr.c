#include <xc.h>
#include "main.h"

extern unsigned char second_flag;
void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 20000)
		{
            second_flag = 1;
			count = 0;
		}
		TMR0IF = 0;
	}
}