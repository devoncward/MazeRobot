#include "Navigation.h"
#include "QTRSensors.h"
#include <stdio.h>
#include <stdbool.h>

static bool navFinished;

#define LED_CUTOFF_RANGE 300

static uint16_t LED_1;
static uint16_t LED_2;
static uint16_t LED_3;
static uint16_t LED_4;
static uint16_t LED_5;
static uint16_t LED_6;

static uint8_t currentNavCase;

/*

LED Readings Example

Centered to go straight     Case #1

    1    2   3   4   5   6
            -------
    1    2   3   4   5   6

Turn Right                  Case #2

    1    2   3   4   5   6
        -------
    1    2   3   4   5   6

Turn Left                   Case #3

    1    2   3   4   5   6
                -------
    1    2   3   4   5   6

Stop, Turn Hard Right       Case #4

    1    2   3   4   5   6
   --------
    1    2   3   4   5   6

Stop, Turn Hard Left        Case #5

    1    2   3   4   5   6
                    -------
    1    2   3   4   5   6

Stop, Back-up, missed line  Case #6

    1    2   3   4   5   6
                    
    1    2   3   4   5   6
*/

static enum NavigationState {
    init_st,
    select_movement_st,
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
    currentNavCase = 0;
}

void Navigation_readSensorReadings() {
    //Init the sensor readings here
}

static void determineNavigationCaseNum() {
    // Case 1
    if(LED_3 >= LED_CUTOFF_RANGE && LED_4 >= LED_CUTOFF_RANGE) {
        currentNavCase = 1;
    } else
    // Case 2
    if(LED_2 >= LED_CUTOFF_RANGE && LED_3 >= LED_CUTOFF_RANGE) {
        currentNavCase = 2;
    } else
    // Case 3
    if(LED_4 >= LED_CUTOFF_RANGE && LED_5 >= LED_CUTOFF_RANGE) {
        currentNavCase = 3;
    } else
    // Case 4
    if(LED_1 >= LED_CUTOFF_RANGE && LED_2 >= LED_CUTOFF_RANGE) {
        currentNavCase = 4;
    } else
    // Case 5
    if(LED_5 >= LED_CUTOFF_RANGE && LED_6 >= LED_CUTOFF_RANGE) {
        currentNavCase = 5;
    } else
    // Case 6
    {
        currentNavCase = 6;
    }
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
        case select_movement_st:
            printf("Entering Navigation Select Movement State\n");
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
    Navigation_readSensorReadings(); //Get current LED values

    //Transitions for the Navigation State machine
    switch (currentState) {
    case init_st:
        currentState = select_movement_st;
        break;
    case select_movement_st:
        if(ballFound == true) {
            currentState = finished_st;
        } else {
            switch (currentNavCase) {
                case 1:
                    currentState = forward_st;
                    break;
                case 2:
                    currentState = right_st;
                    break;
                case 3:
                    currentState = left_st;
                    break;
                case 4:
                    currentState = right_st;
                    break;
                case 5:
                    currentState = left_st;
                    break;
                case 6:
                    currentState = backward_st;
                    break;
                default:
                    printf("Error in selecting navigation state case\n");
                    currentState = backward_st; //attempt to back up and try again
                    break;
            }
        }
        break;
    case forward_st:
        currentState = select_movement_st;
        break;
    case left_st:
        currentState = select_movement_st;
        break;
    case right_st:
        currentState = select_movement_st;
        break;
    case backward_st:
        currentState = select_movement_st;
        break;
    case finished_st:
        currentState = finished_st;
        break;
    default:
        currentState = select_movement_st;
        break;
    }

    Navigation_debugStateMachine(); //debug the state machine to display current state

    //Actions for the Navigation State Machine
    switch (currentState) {
    case init_st:
        //keep empty, refer to init() function
        break;
    case select_movement_st:
        break;
    case forward_st:
        //Move both wheels forward at x speed
        break;
    case left_st:
        if(currentNavCase == 3) {
            // Move left wheel x speed
            // Move right wheel 2*x speed
        } else if(currentNavCase == 5) {
            // Move left wheel 0 speed
            // Move right wheel x speed
        } else {
            printf("Error in left state action current nav case, should be 3,5 is really %d\n", currentNavCase);
        }
        break;
    case right_st:
        if(currentNavCase == 2) {
            // Move right wheel x speed
            // Move left wheel 2*x speed
        } else if(currentNavCase == 4) {
            // Move right wheel 0 speed
            // Move left wheel x speed
        } else {
            printf("Error in left state action current nav case, should be 3,5 is really %d\n", currentNavCase);
        }
        break;
    case backward_st:
        //simply back up for x amount of time or y amount of wheel rotations
        break;
    case finished_st:
        navFinished = true;
        break;
    default:
        break;
    }
}

bool Navigation_finished() {
    return navFinished;
}
