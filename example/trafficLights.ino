/*

    trafficLights - sketch for arduino

    This sketch runs a set of traffic lights, with three leds
    (green, orange and red) for vehicles, two leds (green and red)
    for pedestrians and a push button that can be used to change se
    state of the traffic lights to "walkState" (green
    for pedestrians and red for vehicles).

    This is an example of a sketch using the StatefulLoop library
    <https://github.com/dj3c1t/StatefulLoop>

    pin  4: green led for vehicles (OUTPUT)
    pin  5: orange led for vehicles (OUTPUT)
    pin  6: red led for vehicles (OUTPUT)
    pin  7: green led for pedestrians (OUTPUT)
    pin  8: red led for pedestrians (OUTPUT)
    pin 10: push button (INPUT_PULLUP)

    trafficLights.ino
    Created by dj3c1t, Mars 24, 2019.
    Released in GPL v.3 or later <https://www.gnu.org/licenses/>

*/

#include <StatefulLoop.h>

int pin_vehiculesGreenLed   = 4;
int pin_vehiculesOrangeLed  = 5;
int pin_vehiculesRedLed     = 6;
int pin_pedestriansGreenLed = 7;
int pin_pedestriansRedLed   = 8;
int pin_pushBouton          = 10;

// lightsLoop handles the traffic lights cycle
StatefulLoop   lightsLoop;
// buttonLoop checks if the button is pushed
StatefulLoop   buttonLoop;

void setup() {
    // init pins
    pinMode(pin_vehiculesGreenLed, OUTPUT);
    pinMode(pin_vehiculesOrangeLed, OUTPUT);    
    pinMode(pin_vehiculesRedLed, OUTPUT);
    pinMode(pin_pedestriansGreenLed, OUTPUT);
    pinMode(pin_pedestriansRedLed, OUTPUT);
    pinMode(pin_pushBouton, INPUT_PULLUP);
    /*
        set the first state in the StatefulLoop instances, using the setState
        function, e.g. :

        lightsLoop.setState(greenState);

        this sets the lightsLoop instance to be in the "greenState" state

        setState is called with a function as a parameter, which means we
        have a greenState function defined in our code (see below)
    */
    lightsLoop.setState(greenState);
    buttonLoop.setState(buttonState);
}

/*
    call the loop() function on each instances of StatefulLoop
*/
void loop() {
    lightsLoop.loop();
    buttonLoop.loop();
}

/* -------------------------------------------- */
/*              lightsLoop states               */
/* -------------------------------------------- */

void greenState() {
    // green for vehicles, red for pedestrians
    digitalWrite(pin_vehiculesGreenLed, HIGH);
    digitalWrite(pin_vehiculesOrangeLed, LOW);
    digitalWrite(pin_vehiculesRedLed, LOW);
    digitalWrite(pin_pedestriansGreenLed, LOW);
    digitalWrite(pin_pedestriansRedLed, HIGH);
    // set lightsLoop's next state to be "orangeState", after a 5000ms delay
    lightsLoop.setState(orangeState, 5000);
}

void orangeState() {
    // orange for vehicles, red for pedestrians
    digitalWrite(pin_vehiculesGreenLed, LOW);   
    digitalWrite(pin_vehiculesOrangeLed, HIGH);
    digitalWrite(pin_vehiculesRedLed, LOW);
    digitalWrite(pin_pedestriansGreenLed, LOW);
    digitalWrite(pin_pedestriansRedLed, HIGH);
    // set lightsLoop's next state to be "redState", after a 1000ms delay
    lightsLoop.setState(redState, 1000);
}

void redState() {
    // red for vehicles, red for pedestrians
    digitalWrite(pin_vehiculesRedLed, HIGH);
    digitalWrite(pin_vehiculesOrangeLed, LOW);
    digitalWrite(pin_vehiculesGreenLed, LOW);
    digitalWrite(pin_pedestriansGreenLed, LOW);
    digitalWrite(pin_pedestriansRedLed, HIGH);
    // set lightsLoop's next state to be "walkState", after a 1000ms delay
    lightsLoop.setState(walkState, 1000);
}

void walkState() {
    // red for vehicles, green for pedestrians
    digitalWrite(pin_vehiculesRedLed, HIGH);
    digitalWrite(pin_vehiculesOrangeLed, LOW);
    digitalWrite(pin_vehiculesGreenLed, LOW);  
    digitalWrite(pin_pedestriansGreenLed, HIGH);
    digitalWrite(pin_pedestriansRedLed, LOW);
    // set lightsLoop's next state to be "walkEndingState", after a 5000ms delay
    lightsLoop.setState(walkEndingState, 5000);
}

void walkEndingState() {
    // red for vehicles, red for pedestrians
    digitalWrite(pin_vehiculesRedLed, HIGH);
    digitalWrite(pin_vehiculesOrangeLed, LOW);
    digitalWrite(pin_vehiculesGreenLed, LOW);  
    digitalWrite(pin_pedestriansGreenLed, LOW);
    digitalWrite(pin_pedestriansRedLed, HIGH);
    // set lightsLoop's next state to be "greenState", after a 1000ms delay
    lightsLoop.setState(greenState, 1000);
}

/* -------------------------------------------- */
/*              buttonLoop states               */
/* -------------------------------------------- */

/*
    the buttonLoop instance has only one state, the "buttonState" function,
    which checks if the button is pushed
*/
void buttonState() {
    if(digitalRead(pin_pushBouton) == LOW) {
        // if lightsLoop is in "greenState"
        if(lightsLoop.getState() == greenState) {
            // set lightsLoop to "orangeState", without delay
            lightsLoop.setState(orangeState);
        }
        // if lightsLoop is in "walkState" or in "walkEndingState"
        else if(
                (lightsLoop.getState() == walkState)
            ||  (lightsLoop.getState() == walkEndingState)
        ) {
            // set lightsLoop to "walkState", without delay
            lightsLoop.setState(walkState);
        }
    }
    // set buttonLoop's next state to be "buttonState", without delay
    buttonLoop.setState(buttonState);
}
