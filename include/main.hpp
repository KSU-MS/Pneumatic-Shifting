#include <Arduino.h>
uint16_t Paddle_Value;
uint16_t Launch_Value;

// Output Pins
#define LAUNCH_CONTROL 10
#define NO_LIFT_SHIFT 9
#define UP_PIN 8
#define DOWN_PIN 7
#define CLUTCH_PIN 6

// Input Signals
#define PADDLE_SIGNAL 14
#define LAUNCH_BUTTON_SIGNAL 15
// NOTE: These are not populated yet
// #define UP_SIGNAL 16
// #define DOWN_SIGNAL 17
// #define NEUTRAL_SIGNAL 18

class PS3 {
public:
  void upShift() {
    digitalWrite(NO_LIFT_SHIFT, HIGH);
    delay(50); // Delay to give ECU time to spark cut
    digitalWrite(UP_PIN, HIGH);
    delay(150); // Delay to allow up cylinder to reach height
  }

  void downShift() {
    digitalWrite(CLUTCH_PIN, HIGH);
    digitalWrite(LAUNCH_CONTROL, HIGH);
    delay(150); // Delay to allow clutch pin to reach height
    digitalWrite(DOWN_PIN, HIGH);
    delay(150); // Delay to allow down cylinder to reach height
    digitalWrite(CLUTCH_PIN, LOW);
    delay(150); // Delay to allow clutch to drop
    digitalWrite(LAUNCH_CONTROL, LOW);
  }

  void launchStateActive() {
    digitalWrite(CLUTCH_PIN, HIGH);
    digitalWrite(LAUNCH_CONTROL, HIGH);
    delay(100); // Delay to allow clutch pin to reach height
  }

  void launchStateDisengage() {
    digitalWrite(LAUNCH_CONTROL, LOW);
    delay(2000); // Delay for the bleeder Valve to slowly Release Preasure
    digitalWrite(CLUTCH_PIN, LOW);
    delay(100); // Delay to allow clutch to drop
  }

  void pinReset() {
    digitalWrite(UP_PIN, LOW);
    digitalWrite(DOWN_PIN, LOW);
    digitalWrite(CLUTCH_PIN, LOW);
    digitalWrite(NO_LIFT_SHIFT, LOW);
    digitalWrite(LAUNCH_CONTROL, LOW);
  }
};
