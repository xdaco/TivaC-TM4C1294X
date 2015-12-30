//*****************************************************************************
// The GPIO read (INPUT)  example
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

		SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // Enables PORT B
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // Enables PORT E
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP); // Enables PORT P
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ); // Enables PORT Q
		GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,  GPIO_PIN_2); // PB2 is set as input. By this method you can assign one pin at a time
		GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, 0x01); //PE0 set as Input
		GPIOPinTypeGPIOInput(GPIO_PORTQ_BASE, 0x1F); //PQ0,PQ1,PQ2,PQ3,PQ4 are set as Input
		GPIOPinTypeGPIOInput(GPIO_PORTP_BASE, 0x08);
		InitConsole(); // Calls the UART debug config funtion
		UARTprintf("Input tests for TM4C1294X\n"); // General print for the code information.


    while(1){

    	uint32_t PB2_STATE =  GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_2);
    	uint32_t PE0_STATE =  GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_0);
    	uint32_t PP3_STATE =  GPIOPinRead(GPIO_PORTP_BASE,GPIO_PIN_3);
    	uint32_t PQ0_STATE =  GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_0);
    	uint32_t PQ1_STATE =  GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_1);
    	uint32_t PQ2_STATE =  GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_2);
    	uint32_t PQ3_STATE =  GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_3);
    	uint32_t PQ4_STATE =  GPIOPinRead(GPIO_PORTQ_BASE,GPIO_PIN_4);
    	//Wait for a button press
    	do{
    		PB2_STATE =  GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_2);
    	  } while ((PB2_STATE&GPIO_PIN_2)!=0);

    	//Wait for the button to be let go
    	do{
    		PB2_STATE =  GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_2);
    	  } while ((PB2_STATE&GPIO_PIN_2)==0);


      }

}
