#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <stdbool.h>

bool ballFound;

// Init state function for control state machine
void Navigation_init();

// Debug function to display transitions for the state machine
void Navigation_debugStateMachine();

// Standard tick function for control state machine
void Navigation_tickFunction();

// Returns true if the Navigation state machine has finished
bool Navigation_finished();

// Init LED values from sensor
void Navigation_readSensorReadings();


#endif