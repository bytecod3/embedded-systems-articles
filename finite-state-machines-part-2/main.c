#include "state_machine.h"

enum STATE current_state;

int current_state = STATE::BOOTUP;

void setup(){
    Serial.begin(115200);

}

void loop() {
    /*====================call functions based on current state=================*/
    switch (current_state)
    {
    case States::READY:
        displayReadyMessage();
        break;

    case States::MENU:
        displayMenu();
        break;

    case States::HEATING:
        startMagnetron();
    
    default:
        /* define a default state here */
        break;
    }

    /*====================end of state machine switch case=================*/


    

}