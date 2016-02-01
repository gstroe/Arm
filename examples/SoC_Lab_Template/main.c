/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include <stdbool.h>
#include <stdio.h>


extern int main( void )
{

	/* Disable watchdog */
	WDT_Disable(WDT);


	/* Enable I and D cache */
	SCB_EnableICache();
	SCB_EnableDCache();

	
	while (1) 
	{
		
	}
}
