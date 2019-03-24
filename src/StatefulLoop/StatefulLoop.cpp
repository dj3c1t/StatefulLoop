/*
  StatefulLoop.cpp - Library for building stateful loops for Arduino
  Created by dj3c1t, Mars 17, 2019.
  Released in GPL v.3 or later <https://www.gnu.org/licenses/>
*/

#include "Arduino.h"
#include "StatefulLoop.h"
#include "limits.h"

StatefulLoop::StatefulLoop() {
    transition.started   = 0;
    transition.msDelay   = 0;
    transition.lastRun   = 0;
    transition.nextState = NULL;
    transition.active    = false;
    stateChanged         = false;
}

void StatefulLoop::setState(sl_state stateFunction, unsigned long msdelay) {
    transition.started   = millis();
    transition.msDelay   = msdelay;
    transition.lastRun   = transition.started;
    transition.nextState = stateFunction;
    transition.active    = true;
}

sl_state StatefulLoop::getState() {
    return currentState;
}

void StatefulLoop::loop() {
    runTime = millis();
    if(stateChanged) {
        if(currentState != NULL) {
            (* currentState)();
        }
        stateChanged = false;
    }
    if(transitionEnded()) {
        transition.active = false;
        currentState      = transition.nextState;
        stateChanged      = true;
    }
}

bool StatefulLoop::transitionEnded() {
    if(!transition.active) {
        return false;
    }
    if(runTime < transition.lastRun) {
        if((ULONG_MAX - transition.started) < transition.msDelay) {
            transition.msDelay -= (ULONG_MAX - transition.started);
            transition.started = 0;
        }
        else {
            transition.lastRun = runTime;
            return true;
        }
    }
    transition.lastRun = runTime;
    if((runTime - transition.started) > transition.msDelay) {
        return true;
    }
    return false;
}
