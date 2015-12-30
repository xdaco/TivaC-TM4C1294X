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
#include <string.h>

//************** Include Section Ends here************************************//

#define LEDbase GPIO_PORTF_BASE
#define LEDred GPIO_PIN_1
#define LEDblue GPIO_PIN_2
#define LEDgreen GPIO_PIN_3

void InitConsole(void)
{

		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	    GPIOPinConfigure(GPIO_PC4_U7RX);
	    GPIOPinConfigure(GPIO_PC5_U7TX);
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
	    UARTClockSourceSet(UART7_BASE, UART_CLOCK_PIOSC);
	    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	    UARTStdioConfig(7, 115200, 16000000);
}


int main(){

  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlDelay(16000000 / 3); /* 1 Second Delay */
  GPIOPinTypeGPIOOutput(LEDbase, LEDred|LEDblue|LEDgreen);
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);

    while(1){


      }

}
