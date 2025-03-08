#include "main.hpp"
PS3 pneumaticMain;

void setup (){
    pinMode(UP_PIN, OUTPUT);
    pinMode(NO_LIFT_SHIFT, OUTPUT);
    pinMode(LAUNCH_CONTROL, OUTPUT);
    pinMode(DOWN_PIN, OUTPUT);
    pinMode(CLUTCH_PIN, OUTPUT);
    pneumaticMain.pinReset();//Sets all pins to low
}

void loop (){
    // Button Reads
    Paddle_Value = analogRead(PADDLE_SIGNAL);
    Launch_Value = analogRead(LAUNCH_BUTTON_SIGNAL);

    if (Launch_Value > 115 && Launch_Value < 126 /*Calculated Launch Button Voltages*/){
        pneumaticMain.launchStateActive();
        while (Launch_Value > 115 && Launch_Value < 126){
            Launch_Value = analogRead(LAUNCH_BUTTON_SIGNAL);
            serial_print("Launch Button is being held");
            delay(1);//Waiting to prevent sending too many messages
        }
        serial_print("Launch Button Released");
        pneumaticMain.launchStateDisengage();
    }
    else if (Paddle_Value > 108 && Paddle_Value < 117 /*Calculated Right Paddle Voltages*/){
        pneumaticMain.upShift();
        pneumaticMain.pinReset();//Resets the pins again to prevent constant up shifting
        while (Paddle_Value > 108 && Paddle_Value < 117){
            Paddle_Value = analogRead(PADDLE_SIGNAL);
            serial_print("Right Paddle is being held");
            delay(1);//Waiting to prevent sending too many messages
        }
        serial_print("Right Paddle Released");
    }
    else if (Paddle_Value > 96 && Paddle_Value < 106 /*Calculated Left Paddle Voltages*/){
        pneumaticMain.downShift();
        
        pneumaticMain.pinReset();//Resets the pins again to prevent constant down shifting
        while (Paddle_Value > 96 && Paddle_Value < 106){
            Paddle_Value = analogRead(PADDLE_SIGNAL);
            serial_print("Left Paddle is being held");
            delay(1);//Waiting to prevent sending too many messages
        }
        serial_print("Left Paddle Released");
    }
    else{
        pneumaticMain.pinReset();//Safety Guard
    }
    pneumaticMain.pinReset();//Extra Safety Guard
}