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
void assignment2() {
  volatile uint32_t t = 200000;
  uint32_t status_of_ucLED;
  unsigned char ucDelta, ucState;
  PinoutSet(false, false);
  ButtonsInit();
  GPIOPinTypeGPIOOutput(CLP_D1_PORT, CLP_D1_PIN);
  GPIOPinTypeGPIOOutput(CLP_D2_PORT, CLP_D2_PIN);

  while (1) {
    // TODO: Program another button as on/off switch
    ucState = ButtonsPoll(&ucDelta, 0);

    // status of ucled will be a binary value depending on how many leds are on
    LEDRead(&status_of_ucLED);

    // Check for button presses
    if (BUTTON_PRESSED(LEFT_BUTTON, ucState, ucDelta)) {
      LEDWrite(CLP_D1, CLP_D1);
    } else if (BUTTON_RELEASED(LEFT_BUTTON, ucState, ucDelta)) {
      LEDWrite(CLP_D1, 0);
    }
    // Will turn on or off the light
    if (BUTTON_PRESSED(RIGHT_BUTTON, ucState, ucDelta)) {
      LEDWrite(CLP_D1, !status_of_ucLED);
    }
  }
}
int main(void) {
  assignment2();
  return 0;
}
