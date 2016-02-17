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
#define RTC_SRC (*(uint32_t *)0x400E187C)
#define RTC_TIMR (*(uint32_t *)0x400E1868)
#define RTC_CALR (*(uint32_t *)0x400E186C)
#define RTC_VER (*(uint32_t *)0x400E188C)

// pins
#define SW0 {PIO_PA9, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PD26 {PIO_PD26, PIOD, ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT}
#define PA22 {PIO_PA22, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PC19 {PIO_PC19, PIOC, ID_PIOC, PIO_INPUT, PIO_DEFAULT}
#define PA6 {PIO_PA6, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}

// SET UP PINS
const Pin mypins[]= {SW0, PD26, PA22, PC19, PA6};


// This function prints a menu in to the debug window every time it is called.
extern void main_screen(void)
{
	//extra space
	printf("\n\r");
	
	// printing the menu
	printf("  Gabe's Title Should go here... \n\r");
	printf(" _______________________________ \n\r");
	printf("|                               |\n\r");
	printf("| To Toggle LED0 ----- press: 1 |\n\r");
	printf("| To Toggle LED1 ----- press: 2 |\n\r");
	printf("| To Get SW0 --------- press: 3 |\n\r");
	printf("| To Toggle Outputs -- press: 4 |\n\r");
	printf("| To Read Inputs ----- press: 5 |\n\r");
	printf("| For this Menu ------ press: * |\n\r");
	printf("|_______________________________|\n\r");
	printf("This menu is pretty and should impress you.\n\r");
	
}

// Menu Functions
extern void Get_SW0()
{
	//extra space
	printf("\n\r");
	
	bool pCheck;
	
	pCheck = PIO_Get(&mypins[0]);
	
	printf(" The Switch is: ");
	if (pCheck)
		printf("Not Pushed\n\r");
	else
		printf("Pushed\n\r");
	
	//extra space
	printf("\n\r");
}

extern void Toggle_Outputs()
{
	//extra space
	printf("\n\r");
	printf(" Toggling outputs...\r\n");
	
	// toggle
	PIO_Toggle(&mypins[1]);
	PIO_Toggle(&mypins[2]);
	
	//print new outputs
	printf(" New PD26 output: %d\r\n", PIO_Get(&mypins[1]));
	printf(" New PA22 output: %d\r\n", PIO_Get(&mypins[2]));
	
	//extra space
	printf("\n\r");
}

extern void Read_Inputs()
{
	//extra space
	printf("\n\r");
	
	//print new outputs
	printf(" PC19 output: %d\r\n", PIO_Get(&mypins[3]));
	printf(" PA6  output: %d\r\n", PIO_Get(&mypins[4]));
	
	//extra space
	printf("\n\r");
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
		case '1':
			LED_Toggle(0);
			break;
		case '2':
			LED_Toggle(1);
			break;
		case '3':
			Get_SW0();
			break;
		case '4':
			Toggle_Outputs();
			break;
		case '5':
			Read_Inputs();
			break;
		case '*':
			main_screen();
			break;
		default:
			printf(" Character not recognized\n\r\n\r");
	}
	
	// ask for the next input
	printf("> Now please enter an option: ");	
}


extern int main( void )
{

	/* Disable watchdog */
	WDT_Disable(WDT);
	
	// Set up wait timer
	TimeTick_Configure();
	
	// Setup LEDS
	for(int i = 0; i < LED_NUM; i++)
		LED_Configure(i);
	
	// SET UP PINS
	PIO_Configure(mypins, PIO_LISTSIZE(mypins));

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
		Wait(50);
	}
}
