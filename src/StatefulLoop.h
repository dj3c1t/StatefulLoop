/*
  StatefulLoop.h - Library for building stateful loops for Arduino
  Created by dj3c1t, Mars 17, 2019.
  Released in GPL v.3 or later <https://www.gnu.org/licenses/>
*/

#ifndef StatefulLoop_h
#define StatefulLoop_h

#include "Arduino.h"

typedef void (* sl_state)();

struct sl_transition {
    unsigned long started;
    unsigned long msDelay;
    unsigned long lastRun;
    sl_state      nextState;
    bool          active;
};

class StatefulLoop {

  public:
                  StatefulLoop();
    void          setState(sl_state stateFunction, unsigned long msDelay = 0);
    sl_state      getState();
    void          loop();
    bool          transitionEnded();

  private:

    unsigned long runTime;
    sl_state      currentState;
    bool          stateChanged;
    sl_transition transition;

};

#endif
