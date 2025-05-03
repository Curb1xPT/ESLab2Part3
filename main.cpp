#include "mbed.h"
#include "arm_book_lib.h"

#define BLINKING_RATE   100ms

int main()
{
    int c = 0;    

    DigitalIn enterButton(BUTTON1);
    DigitalIn gasDetect(D2);
    DigitalIn overTemp(D3);
    DigitalIn aButton(D4);
    DigitalIn bButton(D5);
    DigitalIn cButton(D6);
    DigitalIn dButton(D7);

    DigitalOut alarmLed(LED2);
    DigitalOut alarmEmergency(LED3);
    DigitalOut incorrectCodeLed(LED1);

    gasDetect.mode(PullDown);
    overTemp.mode(PullDown);
    aButton.mode(PullDown);
    bButton.mode(PullDown);
    cButton.mode(PullDown);
    dButton.mode(PullDown);

    alarmLed = OFF;

    alarmEmergency = OFF;

    incorrectCodeLed = OFF;

    while (true) {
        if (gasDetect == ON && c == 0 || overTemp == ON && c == 0) {
            alarmLed = ON;
        } else {
            alarmLed = OFF;
        }

        if (gasDetect == ON && overTemp == ON) {
            alarmLed = OFF;
            c = c + 1;
        } 
        
        while (c >= 1) {
            alarmEmergency = !alarmEmergency;
            ThisThread::sleep_for(BLINKING_RATE);
            

                if (enterButton && !incorrectCodeLed && alarmEmergency) {
                    if (!aButton && !bButton && !cButton && dButton) {
                        c = 0;
                        alarmEmergency = OFF;
                        incorrectCodeLed = OFF;
                        } else {
                        incorrectCodeLed = !incorrectCodeLed;
                        ThisThread::sleep_for(BLINKING_RATE*5);
                        incorrectCodeLed = !incorrectCodeLed;
                    }
                }
            }
        }
} 