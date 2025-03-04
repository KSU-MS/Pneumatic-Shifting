#include <Arduino.h>
#include "main.hpp"
uint16_t Paddle_Value;
uint16_t Launch_Value;
stateMachine main_state_machine;

void setup (){
    pinMode(UP_PIN, OUTPUT);
    pinMode(NO_LIFT_SHIFT, OUTPUT);
    pinMode(LAUNCH_CONTROL, OUTPUT);
    pinMode(DOWN_PIN, OUTPUT);
    pinMode(CLUTCH_PIN, OUTPUT);
    main_state_machine.pinReset();//Sets all pins to low
}

void loop (){
    // Button Reads
    Paddle_Value = analogRead(PADDLE_SIGNAL);
    Launch_Value = analogRead(LAUNCH_BUTTON_SIGNAL);

    if (Launch_Value == 1){
        main_state_machine.launchState();
        while (Launch_Value == 1){
            Launch_Value = analogRead(LAUNCH_BUTTON_SIGNAL);
            delay(100);//Wait Function/Funcky Pin read here
        }
    }
    else if (Paddle_Value == 1/*Paddled value to be decided later, upshift */){
        main_state_machine.upShift();
        while (Paddle_Value == 1){
            Paddle_Value = analogRead(PADDLE_SIGNAL);
            delay(100);//Wait Function/Funcky Pin read here
        }
    }
    else if (Paddle_Value == 2/*Paddled value to be decided later, downshift */){
        main_state_machine.downShift();
        while (Paddle_Value == 2){
            Paddle_Value = analogRead(PADDLE_SIGNAL);
            delay(100);//Wait Function/Funcky Pin read here
        }
    }
    else{
        main_state_machine.pinReset();//Safety Guard
    }
    main_state_machine.pinReset();
}