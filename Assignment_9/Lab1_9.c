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

/*Make a LED chaser program. The idea is to have the LEDs light up in a
 * sequence one after another to give the impression that the light is moving
 * back and forth on the LED array.*/
void bonusAssignment() {
  uint16_t t = 50000;
  uint8_t led_tracker = 0;
  uint8_t led_array[] = {CLP_D1, CLP_D2, CLP_D3, CLP_D4};

  PinoutSet(false, false);
  ButtonsInit();

  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, CLP_D1_PIN | CLP_D2_PIN);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, CLP_D3_PIN | CLP_D4_PIN);

  while (1) {
    // Loop forward from D1 -> D4
    for (led_tracker = 0; led_tracker < 4; led_tracker++) {
      LEDWrite(led_array[led_tracker], led_array[led_tracker]);
      delay(t);
      LEDWrite(led_array[led_tracker], 0);
    }
    // A LEDs are off before going backwards
    // We start at LED D3, Then D2.
    // To stop same led light up twice we dont need to light D1,
    // It is enough to just restart from beginning with a delay at the end
    for (led_tracker = 2; led_tracker > 0; led_tracker--) {
      LEDWrite(led_array[led_tracker], led_array[led_tracker]);
      delay(t);
      LEDWrite(led_array[led_tracker], 0);
    }
    delay(t);
  }
}
int main(void) { bonusAssignment(); }
