# StatefulLoop
A library for building Arduino stateful loops

## Overview

This library provides an alternative to the **delay** function.

Instead of one function with a call to **delay** inside, make it two functions. With a StatefulLoop instance, the first function will schedule the second one to run after the needed delay... Allowing you to run other parts of code meanwhile.

### States

The main idea behind the StatefulLoop library is to deal withs *states*. States are short 'one-task' non blocking pieces of code, organized in functions. One function for each state.

Each state do what is needed for this state (e.g. checks if a button is pushed, or sets some leds in a particular way). And each state also defines what the next state will be, by calling the **setState** function on a StatefulLoop instance.

the **setState** function can take one or two parameters. The first one, mandatory, is the next function you want to execute. The second optional parameter, which defaults to 0 (zero), can be used to delay the call to this function.

```c++
#include <StatefulLoop.h>

// ...

StatefulLoop   trafficLights;
StatefulLoop   otherLoop;

void setup() {
    // ...
    trafficLights.setState(greenState);
    otherLoop.setState(otherState);
}

void loop() {
    trafficLights.loop();
    otherLoop.loop();
}

// -------------- states ------------------------- //

void greenState() {
    /*
       do things to setup leds with the green one HIGH
       ...
       then set the state to the orangeState function,
       after a 5000ms delay
    */
    trafficLights.setState(orangeState, 5000);
}

void orangeState() {
    // ...
}

// ...

void otherState() {
    if(something hapens) {
        if(trafficLights.getState() == greenState) {
          trafficLights.setState(orangeState);
        }
    }
    otherLoop.setState(otherState);
}

```

A full example is available in the [trafficLights.ino](https://github.com/dj3c1t/StatefulLoop/blob/master/example/trafficLights.ino) sketch.

## StatefulLoop functions

The **sl_state** type below is defined in **StatefulLoop.h** as a pointer to a function
that returns void and takes no parameter.

### setState

```c++
    void setState(sl_state stateFunction, unsigned long msDelay = 0)
```

Sets the next state to **stateFunction**.

|                  |                                            |
|------------------|--------------------------------------------|
|**stateFunction** | the function to be called                  |
|**msDelay**       | the delay (in ms) before the function call |

### getState

```c++
    sl_state getState();
```

returns the function defined as the current state.

### loop

```c++
    void loop()
```

This function must be called for each StatefulLoop instance in Arduino's main loop function.
