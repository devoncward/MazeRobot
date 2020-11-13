#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


#define MAIN_TICK_RATE 1E5 //.2 seconds in usec

static bool robotFinished;

static enum MainState {
    init_st,
    configuring_sensors_st,
    finding_ball_st,
    verify_is_ball_st,
    trapping_ball_st,
    end_manuvering_st,
    finished_st
} currentState;

static void init() {
    currentState = init_st;
    printf("We are now initializing the main state machine\n");
    //initializing variables
    robotFinished = false;
}

// Displays changes of states in the state machine
static void debugStateMachine() {
    static bool firstPass = true;
    static enum MainState previousState;
    // on first pass, previousState is undefined, so could cause undefined
    // behavior. To prevent: firstPass is true upon first pass to guarantee
    // first execution here
    if (previousState != currentState || firstPass) {
        firstPass = false;
        previousState = currentState;
        switch (currentState) {
        case init_st:
            printf("Entering Main Init State\n");
            break;
        case configuring_sensors_st:
            printf("Entering Main Configuring Sensors State\n");
            break;
        case finding_ball_st:
            printf("Entering Main Finding Ball State\n");
            break;
        case verify_is_ball_st:
            printf("Entering Main Verify Is Ball State\n");
            break;
        case trapping_ball_st:
            printf("Entering Main Trapping Ball State\n");
            break;
        case end_manuvering_st:
            printf("Entering Main End Manuvering State\n");
            break;
        case finished_st:
            printf("Entering Main Finished State\n");
            break;
        }
    }
}

static void tickFunction() {
    //Transitions for the Main State machine
    switch (currentState) {
    case init_st:
        currentState = configuring_sensors_st;
        break;
    case configuring_sensors_st:
        currentState = finding_ball_st;
        break;
    case finding_ball_st:
        currentState = verify_is_ball_st;
        break;
    case verify_is_ball_st:
        currentState = trapping_ball_st;
        break;
    case trapping_ball_st:
        currentState = end_manuvering_st;
        break;
    case end_manuvering_st:
        currentState = finished_st;
        break;
    case finished_st:
        currentState = finished_st;
        break;
    }

    debugStateMachine(); //debug the state machine to display current state

    //Actions for the Main State Machine
    switch (currentState) {
    case init_st:
        //keep empty, refer to init() function
        break;
    case configuring_sensors_st:
        break;
    case finding_ball_st:
        break;
    case verify_is_ball_st:
        break;
    case trapping_ball_st:
        break;
    case end_manuvering_st:
        break;
    case finished_st:
        robotFinished = true;
        break;
    }
}

int main() {
    init();
    while(!robotFinished) {
        tickFunction();
        usleep(MAIN_TICK_RATE); // Accepts microseconds
    }
    return 0;
}