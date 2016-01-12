//*****************************************************************************
// This an UART ECHO example Over UART5
// This code verifies the functionality of UART5
//
//*****************************************************************************

//**************All Include file goes here ************************************//

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

//************** Include file Section Ends here ************************************//


//*************** Setting UART7 as debug Port*********************************//

void InitConsole(void){

		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); //Enables the PORT C
		GPIOPinConfigure(GPIO_PC4_U7RX); // Setting the Rx pin
		GPIOPinConfigure(GPIO_PC5_U7TX); // Setting the Tx pin
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7); //Enables UART7
		UARTClockSourceSet(UART7_BASE, UART_CLOCK_PIOSC); // Sets clock source
		GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5); // Setting UART PIN direction
		UARTStdioConfig(7, 115200, 16000000); //Setting baud rate
}


void
ConfigureUARTs(void) // This function configures UART5
{

	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); // Enables the particular port
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5); // Enables UART5
	ROM_GPIOPinConfigure(GPIO_PC6_U5RX); // Assigning UART Rx Pin
	ROM_GPIOPinConfigure(GPIO_PC7_U5TX); // Asigning UART Tx pin
	ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7); // congiguring PC6 and PC7 as UART GPIO
	UARTClockSourceSet(UART5_BASE, UART_CLOCK_PIOSC); // Setting clock source for UART5
	UARTConfigSetExpClk(UART5_BASE, 16000000, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); // Setting the com port parameter for UARt5
	UARTEnable(UART5_BASE); // Finally enabling UART5 with desired setting
	UARTprintf("UART5 initialization done.\n"); // information display on debug UART
}
//
// Prints a string (buf) followed by a CRLF (\r\n)
//
void
Any_UARTPrintln(const char *buf) // This function prints a string on UART
{
	while(*buf)
	{
		UARTCharPut(UART5_BASE, *buf++);
	}
	UARTCharPut(UART5_BASE, '\r');
	UARTCharPut(UART5_BASE, '\n');
}

int
main(void)
{
	int32_t c; // variable to store data after reading from UART
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); // Set the clocking to run directly from the crystal.
	InitConsole();// Initialize the debug UART
	UARTprintf("Example code to test UART5\n");
	ConfigureUARTs();
	Any_UARTPrintln("Testing UART5\n");
	UARTprintf("Setting UART5 in Echo mode\n\n");
	Any_UARTPrintln("Setting UART5 in Echo mode\n\n");
	UARTprintf("Now. Send any character from UART5. The character will be echoed on UART5 and Debug UARTn\n");


	while(1) {
		c = UARTCharGet(UART5_BASE); // Reads UART5
		UARTprintf("%c", c); // Prints the UART5 read data on debug UART
		UARTCharPut(UART5_BASE, c); // prints back the UART
	}

}
