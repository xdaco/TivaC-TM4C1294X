//*****************************************************************************
// The first blinky example to toggle any GPIO.
//
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

		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	    GPIOPinConfigure(GPIO_PC4_U7RX);
	    GPIOPinConfigure(GPIO_PC5_U7TX);
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
	    UARTClockSourceSet(UART7_BASE, UART_CLOCK_PIOSC);
	    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	    UARTStdioConfig(7, 115200, 16000000);
}

//*************** Setting UART7 as debug Port Ends here*********************************//

int main(){

		SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Enables PORT F
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH); // Enables PORT H
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM); // Enables PORT M
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL); // Enables PORT L
		GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, 0x0E); //PF1 , PF2, PF3 are set as Output
		GPIOPinTypeGPIOOutput(GPIO_PORTH_AHB_BASE, 0x06); //PH1, PH2 are set as output
		GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, 0x02); // PM1 is set as output
		GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, 0x30); // PL4,PL5 are set as output
		GPIOPadConfigSet(GPIO_PORTF_AHB_BASE, 0x0E, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD); // Requires only for PORT H & F
		GPIOPadConfigSet(GPIO_PORTH_AHB_BASE, 0x06, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD); // Requires only for PORT H & F

		InitConsole(); // Calls the UART debug config funtion
		UARTprintf("Blinky test program for TM4C1294X\n"); // General print for the code information.


    while(1){

    	UARTprintf("Making PF1,PF2,PF3,PH1,PH2,PM1,PL4 and PL5 high\n");
    	GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_1, GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_2, GPIO_PIN_2);
    	GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_3, GPIO_PIN_3);
    	GPIOPinWrite(GPIO_PORTH_AHB_BASE,GPIO_PIN_1, GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTH_AHB_BASE,GPIO_PIN_2, GPIO_PIN_2);
    	GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_1, GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_4, GPIO_PIN_4);
    	GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_5, GPIO_PIN_5);

    	SysCtlDelay((16000000*3) / 3); // 3 second delay

    	UARTprintf("Making PF1,PF2,PF3,PH1,PH2,PM1,PL4 and PL5 Low\n");
    	GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_1, ~GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_2, ~GPIO_PIN_2);
    	GPIOPinWrite(GPIO_PORTF_AHB_BASE,GPIO_PIN_3, ~GPIO_PIN_3);
    	GPIOPinWrite(GPIO_PORTH_AHB_BASE,GPIO_PIN_1, ~GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTH_AHB_BASE,GPIO_PIN_2, ~GPIO_PIN_2);
    	GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_1, ~GPIO_PIN_1);
    	GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_4, ~GPIO_PIN_4);
    	GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_5, ~GPIO_PIN_5);

    	SysCtlDelay((16000000*3) / 3); // 3 second delay


      }

}
