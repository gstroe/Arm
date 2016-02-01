/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "main.h"
#include <stdbool.h>
#include <stdio.h>

// Global Struct for CHIP_ID
struct CHIP_ID
{
	// these are user defind
	uint32_t CHIP_ID_REG;
	uint32_t CHIP_ID_EXT_REG;
};


// This function prints a menu in to the debug window every time it is called.
extern void main_screen(void)
{
	// printing the menu
	printf("  Gabe's Title Should go here... \n\r");
	printf(" _______________________________ \n\r");
	printf("|                               |\n\r");
	printf("| For Struct Test ---- press: 0 |\n\r");
	printf("| For Pointer Test --- press: 1 |\n\r");
	printf("| For array_test ----- press: 2 |\n\r");
	printf("| For phd3 ----------- press: 3 |\n\r");
	printf("| For phd4 ----------- press: 4 |\n\r");
	printf("| For this menu ------ press: * |\n\r");
	printf("|_______________________________|\n\r");
	printf("This menu is pretty and should impress you.\n\r");
	
}

// Place holder functions for later
extern void struct_test(void)
{
	// declare a new chip id
	struct CHIP_ID CHIP_ID1;
	
	// enter values
	CHIP_ID1.CHIP_ID_REG = 744234;
	CHIP_ID1.CHIP_ID_EXT_REG = 1337;
	
	// print values
	printf("CHIP ID Reg = %d\n\r", CHIP_ID1.CHIP_ID_REG);
	printf("CHIP ID Ext Reg = %d\n\r", CHIP_ID1.CHIP_ID_EXT_REG);
	
	//extra space
	printf("\n\r");
}

extern void pointer_test(void)
{
	// declare dog and cat
	uint32_t dog = 32;
	uint32_t* cat;
	
	// store memory location of dog in cat
	cat = &dog;
	
	// print crap
	printf("Dog's address: %d\n\r", (int)&dog); // should work... hopefully ---- and it did Hurrah!
	printf("The value cat is holding: %d\n\r", (int)cat);
	printf("The value cat is pointing to: %d\n\r", (int)(*cat));
	
	//extra space
	printf("\n\r");
}
extern void array_test(void)
{
	// heres the text
	char text[] = "Hello!";
	
	// printing it out the hard way...
	for (int i = 0; i < sizeof(text); i++)
		printf("%c",text[i]);
	
	//extra space
	printf("\n\r");
	
	// changing the text
	text[0] = 'S';
	text[1] = 'm';
	text[2] = 'e';
	text[3] = 'l';
	text[4] = 'l';
	text[5] = 'y';
	
	// now to print the normal way
	printf("%s\n\r",text);
	
	//extra space
	printf("\n\r");
}
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
			struct_test();
			break;
		case '1':
			pointer_test();
			break;
		case '2':
			array_test();
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
