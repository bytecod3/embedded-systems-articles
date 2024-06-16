
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

enum States {
    BOOTUP = 1, /* initialise all sub-systems */
    READY,      /* waiting for input  */
    MENU,       /* display menu */
    HEATING     /* heat food */
};

#endif


void menuButtonISR() {
    /* switch current state to MENU */
    currentState = States::MENU;

}
