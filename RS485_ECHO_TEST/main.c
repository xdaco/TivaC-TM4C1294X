//*****************************************************************************
// This an RS485 ECHO example Over UART2/UART3/UART4
// The RS485 TRXVR Read/Right Enable pins are PK5/PK6/PK7 respectively.........
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

uint32_t UART_BASE;

uint32_t RS485_RW;
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
ConfigureUARTs(uint32_t uart_no,uint32_t uart_base)
{
	switch ( uart_no ) {
		case 2:
			// Enable the GPIO Peripheral used by the UART2.
			ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
			ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
			ROM_GPIOPinConfigure(GPIO_PA6_U2RX);
			ROM_GPIOPinConfigure(GPIO_PA7_U2TX);
			ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
			UARTprintf(" RS485 on UART2 configured\n");
			break;
		case 3:
			// Enable the GPIO Peripheral used by the UART3.
			ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
			ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
			ROM_GPIOPinConfigure(GPIO_PA4_U3RX);
			ROM_GPIOPinConfigure(GPIO_PA5_U3TX);
			ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5);
			UARTprintf(" RS485 on UART3 configured\n");
			break;

		case 4:
			// Enable the GPIO Peripheral used by the UART4.
			ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
			ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
			ROM_GPIOPinConfigure(GPIO_PA2_U4RX);
			ROM_GPIOPinConfigure(GPIO_PA3_U4TX);
			ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);
			UARTprintf(" RS485 on UART4 configured\n");
			break;

		default:
			break;
	}
	// Setup UART at 115200 baud
	UARTClockSourceSet(uart_base, UART_CLOCK_PIOSC);
	UARTConfigSetExpClk(uart_base, 16000000, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTEnable(uart_base);
	UARTprintf(" RS485 on UARTconfiguration done\n");
}

///*************************************************************************************
//
//This function prints string on any UART
//
//
//************************************************************************************
void
Any_UARTPrintln(const char *buf, uint32_t UART_BASE, uint32_t RS485_RW)
{

			GPIOPinWrite(GPIO_PORTK_BASE, RS485_RW, RS485_RW);// This is required to enable transmit on RS485 IC
			while(*buf)
			{
				UARTCharPut(UART_BASE, *buf++);
			}
			UARTCharPut(UART_BASE, '\r');
			UARTCharPut(UART_BASE, '\n');
			SysCtlDelay((160000) / 3); // 0.01 second delay
			GPIOPinWrite(GPIO_PORTK_BASE, RS485_RW, ~RS485_RW); // This is required to eanble receive on the RS485 IC
}

int
main(void)
{

	unsigned char c;
	uint32_t UART_NO;
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); //Initialize the clock
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE,GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE,GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE,GPIO_PIN_7);
	// Initialize the UARTs
	InitConsole();
	UARTprintf("RS485 Echo Example code\n");
	UARTprintf("Please send me the UART no. as ascii from the debug terminal\n");
	UART_NO=UARTCharGet(UART7_BASE);
	UARTprintf("UART_NO=%c\n",UART_NO);
	while((UART_NO != '2')&&(UART_NO != '3')&&(UART_NO != '4')) {

		UARTprintf("Please enter a valid UART no. as ascii from the debug terminal\n");
		UART_NO=UARTCharGet(UART7_BASE);
	}
	if ( UART_NO== '2')
	{
		UART_NO=2;
		UARTprintf("UART2 has been selected\n");
		UART_BASE=UART2_BASE;
		RS485_RW=GPIO_PIN_5;

	}
	else if (UART_NO== '3')
	{

		UART_NO=3;
		UARTprintf("UART3 has been selected\n");
		UART_BASE=UART3_BASE;
		RS485_RW=GPIO_PIN_6;

	}
	else   if (UART_NO== '4')
	{
		UART_NO=4;
		UARTprintf("UART4 has been selected\n");
		UART_BASE=UART4_BASE;
		RS485_RW=GPIO_PIN_7;

	}
	UARTprintf("Configuring RS485 UART\n");
	ConfigureUARTs(UART_NO,UART_BASE);
	Any_UARTPrintln("Sending data over RS485 terminal \n",UART_BASE,RS485_RW);
	UARTprintf("Please send me START as ascii on RS485 Terminal\n");
	// wait for a device to connect and then enter streaming mode
	while(UARTCharGet(UART_BASE) != 'S') { }
	while(UARTCharGet(UART_BASE) != 'T') { }
	while(UARTCharGet(UART_BASE) != 'A') { }
	while(UARTCharGet(UART_BASE) != 'R') { }
	while(UARTCharGet(UART_BASE) != 'T') { }

	UARTprintf(" I am receving data on UART No. ");
	UARTprintf("%d",UART_NO);
	UARTprintf(". You have entered START\n");
	// wait for OK
	UARTprintf("Please send me OK as ascii on RS485 Terminal\n");
	while(UARTCharGet(UART_BASE) != 'O') { }
	while(UARTCharGet(UART_BASE) != 'K') { }
	UARTprintf(" You have sent OK\n");
	UARTprintf(" Now onward whatever you will send on RS485 terminal will be echoed on RS485 and debug terminal\n");
	Any_UARTPrintln(" Now onward whatever you will send on RS485 terminal will be echoed on RS485 and debug terminal\n",UART_BASE,RS485_RW);


	while(1) {

		if (UARTCharsAvail(UART_BASE))
		{
			c = UARTCharGet(UART_BASE);
			SysCtlDelay((160000) / 3); // 0.01 second delay
			GPIOPinWrite(GPIO_PORTK_BASE, RS485_RW, RS485_RW);
			UARTprintf("%c", c);
			UARTCharPut(UART_BASE, c);
			SysCtlDelay((160000) / 3); // 0.01 second delay
			GPIOPinWrite(GPIO_PORTK_BASE, RS485_RW, ~RS485_RW);
		}



	}

}
