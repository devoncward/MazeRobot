#include "Navigation.h"
#include "QTRSensors.h"
#include <stdio.h>
#include <stdbool.h>


static bool navFinished;

static enum NavigationState {
    init_st,
    forward_st,
    left_st,
    right_st,
    backward_st,
    finished_st
} currentState;

void Navigation_init() {
    currentState = init_st;
    printf("We are now initializing the navigation state machine\n");
    //initializing variables
    navFinished = false;
}

// Displays changes of states in the state machine
void Navigation_debugStateMachine() {
    static bool firstPass = true;
    static enum NavigationState previousState;
    // on first pass, previousState is undefined, so could cause undefined
    // behavior. To prevent: firstPass is true upon first pass to guarantee
    // first execution here
    if (previousState != currentState || firstPass) {
        firstPass = false;
        previousState = currentState;
        switch (currentState) {
        case init_st:
            printf("Entering Navigation Init State\n");
            break;
        case forward_st:
            printf("Entering Navigation Forward State\n");
            break;
        case left_st:
            printf("Entering Navigation Left State\n");
            break;
        case right_st:
            printf("Entering Navigation Right State\n");
            break;
        case backward_st:
            printf("Entering Navigation Backward State\n");
            break;
        case finished_st:
            printf("Entering Navigation Finished State\n");
            break;
        }
    }
}

void Navigation_tickFunction() {
    //Transitions for the Navigation State machine
    switch (currentState) {
    case init_st:
        currentState = forward_st;
        break;
    case forward_st:
        currentState = left_st;
        break;
    case left_st:
        currentState = right_st;
        break;
    case right_st:
        currentState = backward_st;
        break;
    case backward_st:
        currentState = finished_st;
        break;
    case finished_st:
        currentState = finished_st;
        break;
    }

    Navigation_debugStateMachine(); //debug the state machine to display current state

    //Actions for the Navigation State Machine
    switch (currentState) {
    case init_st:
        //keep empty, refer to init() function
        break;
    case forward_st:
        break;
    case left_st:
        break;
    case right_st:
        break;
    case backward_st:
        break;
    case finished_st:
        navFinished = true;
        break;
    }
}

bool Navigation_finished() {
    return navFinished;
}
