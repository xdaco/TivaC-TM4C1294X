//*****************************************************************************
// The GPIO read (INPUT)  example. This piece of code reads digital input from 
// PB2,PE0,PP3,PQ0,PQ1,PQ2,PQ3,PQ4 and prints their status on UART7. Also when any of
// this pins are high, a respective GPIO is also made high for an LED indications.
// These LEDs are connected on PF1,PF2,PF3,PH1,PH2,PM1,PL4 and PL5.
//*****************************************************************************

//**************All Include file goes here ************************************//

#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"
#include <string.h>

//************** Include Section Ends here************************************//

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

//*************** Setting UART7 as debug Port Ends here*********************************//

int main(){

		SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); //Initialize the clock
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // Enables PORT B
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // Enables PORT E
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Enables PORT F
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH); // Enables PORT H
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL); // Enables PORT L
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM); // Enables PORT M
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP); // Enables PORT P
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ); // Enables PORT Q
		
	//****************************Setting Input Pins**************************************//
	
		GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,  GPIO_PIN_2); // PB2 is set as input. By this method you can assign one pin at a time
		GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, 0x01); //PE0 set as Input
		GPIOPinTypeGPIOInput(GPIO_PORTQ_BASE, 0x1F); //PQ0,PQ1,PQ2,PQ3,PQ4 are set as Input
		GPIOPinTypeGPIOInput(GPIO_PORTP_BASE, 0x08);//PP3 set as Input
		
	//****************************Setting Output Pins**************************************//
	
		GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, 0x0E); //PF1 , PF2, PF3 are set as Output
		GPIOPinTypeGPIOOutput(GPIO_PORTH_AHB_BASE, 0x06); //PH1, PH2 are set as output
		GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, 0x02); // PM1 is set as output
		GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, 0x30); // PL4,PL5 are set as output
		GPIOPadConfigSet(GPIO_PORTF_AHB_BASE, 0x0E, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD); // Requires only for PORT H & F
		GPIOPadConfigSet(GPIO_PORTH_AHB_BASE, 0x06, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD); // Requires only for PORT H & F
		InitConsole(); // Calls the UART debug config funtion
		UARTprintf("Input tests for TM4C1294X\n"); // General print for the code information.

//Infinite loop starts here // you can also use for loop in thefollowing mannaer.//

//		for (; ; )
//		{
		    // ...your code goes here
//		}
    while(1){

       	uint32_t PB2_STATE =  0;
    	uint32_t PE0_STATE =  0;
    	uint32_t PP3_STATE =  0;
    	uint32_t PQ0_STATE =  0;
    	uint32_t PQ1_STATE =  0;
    	uint32_t PQ2_STATE =  0;
    	uint32_t PQ3_STATE =  0;
    	uint32_t PQ4_STATE =  0;
    	

    	if (GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_2)) // monitoring for Input status change for PB2
    	{
    		PB2_STATE =  1;
    		GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_1, GPIO_PIN_1); //Making PF1 High for LED indication
       	}
       	else 
       	{
    		PB2_STATE = 0;
    		GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_1, ~GPIO_PIN_1); //Making PF1 Low
    	}
    	if (GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_0))// monitoring for Input status change for PE0
    	{
    		PE0_STATE =  1;
    		GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_2, GPIO_PIN_2); //Making PF2 High for LED indication
    	}
    	else
    	{
    		PE0_STATE = 0;
    		GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_2, ~GPIO_PIN_2); //Making PF2 Low
    	}
    	if (GPIOPinRead(GPIO_PORTP_BASE,GPIO_PIN_3))// monitoring for Input status change for PP3
    	{
    		PP3_STATE =  1;
    		GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_3, GPIO_PIN_3); //Making PF3 High for LED indication
    	}
    	else
    	{
    		PP3_STATE = 0;
    		GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_3, ~GPIO_PIN_3); //Making PF3 Low
    	}
    	if (GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_0))// monitoring for Input status change for PQ0
    	{
    		PQ0_STATE =  1;
    		GPIOPinWrite(GPIO_PORTH_AHB_BASE,GPIO_PIN_1, GPIO_PIN_1); //Making PH1 High for LED indication
    	}
    	else
    	{
    		PQ0_STATE = 0;
    		GPIOPinWrite(GPIO_PORTH_AHB_BASE,GPIO_PIN_1, ~GPIO_PIN_1); //Making PH1 Low
    	}
    	if (GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_1))// monitoring for Input status change for PQ1
    	{
    		PQ1_STATE =  1;
    		GPIOPinWrite(GPIO_PORTH_AHB_BASE,GPIO_PIN_2, GPIO_PIN_2); //Making PH2 High for LED indication
    	}
    	else
    	{
    		PQ1_STATE = 0;
    		GPIOPinWrite(GPIO_PORTH_AHB_BASE,GPIO_PIN_2, ~GPIO_PIN_2); //Making PH2 Low
    	}
    	if (GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_2))// monitoring for Input status change for PQ2
    	    	{
    	    		PQ2_STATE =  1;
    	    		GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_1, GPIO_PIN_1); //Making PM1 High for LED indication
    	    	}
    	else
    	{
    		PQ2_STATE = 0;
    		GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_1, ~GPIO_PIN_1); //Making PM1 Low
    	}
    	if (GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_3))// monitoring for Input status change for PQ3
    	    	{
    	    		PQ3_STATE =  1;
    	    		GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_4, GPIO_PIN_4); //Making PL4 High for LED indication
    	    	}
    	else 
    	{
    		PQ3_STATE = 0;
    		GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_4, ~GPIO_PIN_4); //Making PL4 Low
    	}
    	if (GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_4))// monitoring for Input status change for PQ4
    	    	{
    	    		PQ4_STATE =  1;
    			GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_5, GPIO_PIN_5); //Making PL5 High for LED indication
    		}
    	else
    	{
    		PQ4_STATE =  0;
    		GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_5, ~GPIO_PIN_5); //Making PL5 Low
    	}
    	// Printing the input status as eight digit Binary
    	UARTprintf("%d%d%d%d%d%d%d%d\n",PB2_STATE,PE0_STATE,PP3_STATE,PQ0_STATE,PQ1_STATE,PQ2_STATE,PQ3_STATE,PQ4_STATE);



      }

}
