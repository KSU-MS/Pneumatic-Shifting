#include <Arduino.h>
//Output Pins
#define LAUNCH_CONTROL 19
#define NO_LIFT_SHIFT 20
#define UP_PIN 21
#define DOWN_PIN 22
#define CLUTCH_PIN 23
//Input Signals
#define PADDLE_SIGNAL 14
#define LAUNCH_BUTTON_SIGNAL 15
#define UP_SIGNAL 16
#define DOWN_SIGNAL 17
#define NEUTRAL_SIGNAL 18

class stateMachine {
    private:
    enum states{ //Not really sure what to do with this - Luis
        rest,
        up_shift,
        down_shift,
        launch
    };
    states current_state = rest;//Or this - Luis
    public:

    void upShift(){
        digitalWrite(NO_LIFT_SHIFT, HIGH);
        digitalWrite(UP_PIN, HIGH);
        delay(100); //Wait Function/Funky Pin read here
    }
    void downShift(){
        digitalWrite(CLUTCH_PIN, HIGH);
        digitalWrite(DOWN_PIN, HIGH);
        delay(100);//Wait Function/Funky Pin read here
    }
    void launchState(){
        digitalWrite(CLUTCH_PIN, HIGH);
        digitalWrite(LAUNCH_CONTROL, HIGH);
        delay(100);//Wait Function/Funcky Pin read here
    }
    void pinReset(){
        digitalWrite(CLUTCH_PIN, LOW);
        digitalWrite(UP_PIN, LOW);
        digitalWrite(DOWN_PIN, LOW);
        digitalWrite(NO_LIFT_SHIFT, LOW);
        digitalWrite(LAUNCH_CONTROL, LOW);
    }
};