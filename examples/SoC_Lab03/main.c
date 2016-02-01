/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "main.h"
#include <stdbool.h>
#include <stdio.h>

// This function prints a menu in to the debug window every time it is called.
extern void main_screen(void)
{
	// printing the menu
	printf("  Gabe's Title Should go here... \n\r");
	printf(" _______________________________ \n\r");
	printf("| For Struct Test ---- press: 0 |\n\r");
	printf("| For Pointer Test --- press: 1 |\n\r");
	printf("| For array_test ----- press: 2 |\n\r");
	printf("| For phd3 ----------- press: 3 |\n\r");
	printf("| For phd4 ----------- press: 4 |\n\r");
	printf("|_______________________________|\n\r");
	printf("This menu is pretty and should impress you.\n\r");
	
	
}

// Place holder functions for later
extern void phd0(void){printf("Place holder Function 0 called! \n\r\n\r");}
extern void phd1(void){printf("Place holder Function 1 called! \n\r\n\r");}
extern void phd2(void){printf("Place holder Function 2 called! \n\r\n\r");}
extern void phd3(void){printf("Place holder Function 3 called! \n\r\n\r");}
extern void phd4(void){printf("Place holder Function 4 called! \n\r\n\r");}


// This checks to see if a character was entered
static void _DBGU_Handler(void)
{
	// Check and see if characters are avalible, if not return from function
	if(!DBG_IsRxReady())
		return;
	
	// varable for checking
	uint8_t key;
	
	// get key
	key = DBG_GetChar();
	
	// Display the key to the user
	printf("%c\n\r", key);
	
	// execute aproprate function
	switch (key)
	{
		case '0':
			phd0();
			break;
		case '1':
			phd1();
			break;
		case '2':
			phd2();
			break;
		case '3':
			phd3();
			break;
		case '4':
			phd4();
			break;
		case '*':
			main_screen();
			break;
		default:
			printf("Character not recognized\n\r\n\r");
	}
	
	// ask for the next input
	printf("Now please enter an option: ");
	
	
}


extern int main( void )
{

	/* Disable watchdog */
	WDT_Disable(WDT);


	/* Enable I and D cache */
	SCB_EnableICache();
	SCB_EnableDCache();

	//display initial menu
	main_screen();
	// Ask user for input for the initial menu
	printf("Now please enter an option: ");
	
	// get char
	while (1) 
	{
		_DBGU_Handler();
	}
}
