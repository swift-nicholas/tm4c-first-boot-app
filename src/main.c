#include <stdint.h>
#include "memory_map.h"
#include <stdbool.h>

#include <driverlib/gpio.h>
#include <driverlib/interrupt.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>

/* System clock for component clocking */
uint32_t g_ui32SysClock;

void system_init(void);

int main(void)
{
  system_init();

  while (1)
    ;
}

void system_init(void)
{
  /* configure the clock for 120mhz */
  g_ui32SysClock = SysCtlClockFreqSet(
      (SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    ;

  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
}