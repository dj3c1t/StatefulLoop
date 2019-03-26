# StatefulLoop
A library for building Arduino stateful loops

## Overview

This library provides an alternative to the **delay** function.

Instead of one function with a call to **delay** inside, make it two functions. With a StatefulLoop instance, the first function will schedule the second one to run after the needed delay... Allowing you to run other parts of code meanwhile.

```c++
#include <StatefulLoop.h>

StatefulLoop   trafficLights;

// ...

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
```

A full example is available in the [trafficLights.ino](https://github.com/dj3c1t/StatefulLoop/blob/master/example/trafficLights.ino) sketch.

## Types and functions

### Types

#### sl_state

A pointer to a function that returns void and takes no parameter.

```c++
    typedef void (* sl_state)();
```

### Functions

#### setState

```c++
    void setState(sl_state stateFunction, unsigned long msDelay = 0)
```

Sets the next state for the StatefulLoop instance.

| Parameter name | type                      | description                                |
|----------------|---------------------------|--------------------------------------------|
| stateFunction  | sl_state      (mandatory) | the function to be called                  |
| msDelay        | unsigned long (default 0) | the delay (in ms) before the function call |

#### getState

```c++
    sl_state getState();
```

Returns the function defined as the current state in the StatefulLoop instance.

#### loop

```c++
    void loop()
```

This function must be called for each StatefulLoop instance in Arduino's main loop function.
