/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "main.h"
#include <stdbool.h>
#include <stdio.h>

// some globle definitions
// chip id
#define CHIPID_CIDR (*(uint32_t *)0x400E0940)
// random number
#define TRNG_CR (*(uint32_t *)0x40070000)
#define TRNG_STATUS (*(uint32_t *)0x4007001C)
#define TRNG_DATA (*(uint32_t *)0x40070050)
// System Write protection
#define SYSC_WPMR (*(uint32_t *)0x400E18E4)
// Real Time Clock
#define RTC_CR (*(uint32_t *)0x400E1860)
#define RTC_MR (*(uint32_t *)0x400E1864)
#define RTC_SR (*(uint32_t *)0x400E1878)


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
	//extra space
	printf("\n\r");
	
	// printing the menu
	printf("  Gabe's Title Should go here... \n\r");
	printf(" _______________________________ \n\r");
	printf("|                               |\n\r");
	printf("| For Struct Test ---- press: 0 |\n\r");
	printf("| For Pointer Test --- press: 1 |\n\r");
	printf("| For Array Test ----- press: 2 |\n\r");
	printf("| For Read Chip ID --- press: 3 |\n\r");
	printf("| For Trng Test ------ press: 4 |\n\r");
	printf("| For Setup RTC ------ press: 5 |\n\r");
	printf("| For Print Time ----- press: 6 |\n\r");
	printf("| For this Menu ------ press: * |\n\r");
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
	
	//extra space
	printf("\n\r");
	
	// print values
	printf(" CHIP ID Reg = %d\n\r", CHIP_ID1.CHIP_ID_REG);
	printf(" CHIP ID Ext Reg = %d\n\r", CHIP_ID1.CHIP_ID_EXT_REG);
	
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
	
	//extra space
	printf("\n\r");
	
	// print crap
	printf(" Dog's address: %d\n\r", (int)&dog); 
	printf(" The value cat is holding: %d\n\r", (int)cat);
	printf(" The value cat is pointing to: %d\n\r", (int)(*cat));
	
	//extra space
	printf("\n\r");
}
extern void array_test(void)
{
	//extra space
	printf("\n\r");
	
	// heres the text
	char text[] = " Hello!";
	
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
	printf(" %s\n\r",text);
	
	//extra space
	printf("\n\r");
}

// this fuction reads the chips ID and prints info about it
extern void read_chip_id(void)
{
	//extra space
	printf("\n\r");
	
	// create a temp variable
	uint32_t temp;
  temp = CHIPID_CIDR;
	
	// print out the id in hex
	printf(" The Chip ID is: %#X\n\r\n\r", temp);
	
	// now print each value on the data sheet in decimal
	printf(" The Version of the Device:                         %2d\n\r", (temp & 0x0000001F));
	printf(" The Embedded Processor Value:                      %2d\n\r", ((temp & 0x000000E0) >> 5));
	printf(" The Nonvolatile Program Memory Size Value:         %2d\n\r", ((temp & 0x00000F00) >> 8));
	printf(" The Second Nonvolatile Program Memory Size Value:  %2d\n\r", ((temp & 0x0000F000) >> 12));
	printf(" The Internal SRAM Size Value:                      %2d\n\r", ((temp & 0x000F0000) >> 16));
	printf(" The Architecture Identifier Value:                 %2d\n\r", ((temp & 0x0FF00000) >> 20));
	printf(" The Nonvolatile Program Memory Type Value:         %2d\n\r", ((temp & 0x70000000) >> 28));
	printf(" The Extension Flag Value:                          %2d\n\r", ((temp & 0x80000000) >> 31));
	
	//extra space
	printf("\n\r");
	
}


// generates random numbers
extern void trng_test(void)
{
	//extra space
	printf("\n\r");
	
	// enables the trig clock
	PMC_EnablePeripheral(ID_TRNG);
	
	// enable the random key generator
	TRNG_CR = 0x524E4701; 
	
	// create a temp register
	uint32_t check;
	check = TRNG_STATUS;
	
	// make sure the random number is ready
	while(!check)
	{
		check = TRNG_STATUS;
	}
	
	// print the number in hex (so we avoid negitive)
	printf(" Random Number: %#X\n\r", TRNG_DATA);

	// turn off the random number gen to save power
	PMC_DisablePeripheral(ID_TRNG);
	
	//extra space
	printf("\n\r");
}

extern void setup_rtc()
{
	//extra space
	printf("\n\r");
	
	// disable write protection
	SYSC_WPMR = 0x52544301;
		
	// set the clock settings
	RTC_MR = 0x00000001; // 12 hour mode, gregorian calender, no error correction, no output sources.
	
	// set the update bits
	RTC_CR = 0x00000003;
	
	// check var to see if we can make changes
	uint32_t check;
	check = (RTC_SR & 0x000000001);
	
	while (!check)
	{
		check = (RTC_SR & 0x000000001);
	}
		
	
}

extern void print_time()
{
	
}

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
			read_chip_id();
			break;
		case '4':
			trng_test();
			break;
		case '5':
			setup_rtc();
			break;
		case '6':
			print_time();
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
