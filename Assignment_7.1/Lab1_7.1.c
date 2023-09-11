#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "drivers/buttons.h"
#include "drivers/pinout.h"

// The error routine that is called if the driver library
// encounters an error.
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
  while (1)
    ;
}
#endif

void delay(uint32_t number_of_loops) {
  volatile uint32_t i;
  for (i = 0; i < number_of_loops; i++) {
    // Just looping for delay
  }
}
/*Button input. The program should start blinking the LEDs as an action of
 * button events. i.e after a button press start blinking*/
void assignment1() {
  volatile uint32_t number_of_times_to_blink;
  volatile uint32_t t = 100000;
  unsigned char ucDelta, ucState;
  PinoutSet(false, false);
  ButtonsInit();
  GPIOPinTypeGPIOOutput(CLP_D1_PORT, CLP_D1_PIN);
  while (1) {

    ucState = ButtonsPoll(&ucDelta, 0);
    // Check for button presses
    if (BUTTON_PRESSED(LEFT_BUTTON, ucState, ucDelta)) {

      // Blink 5 times
      for (number_of_times_to_blink = 0; number_of_times_to_blink < 5;
           number_of_times_to_blink++) {
        // turn on LED
        LEDWrite(CLP_D1, CLP_D1);

        // Do some sleeping
        delay(t);

        // turnoff LED
        LEDWrite(CLP_D1, 0);
        delay(t);
      }
    }
  }
}
int main(void) {
  assignment1();
  return 0;
}
