#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <DCC.h>
#include <DCCCommand.h>

//vector<DCCCommand> piorityCommandQueue
//vector<DCCCommand> standardCommandQueue



//<<constructor>>
DCC::DCC() {
}

//<<constructor>>
DCC::DCC(int pin_a, int pin_b) {
    if (pin_a != NULL) {
        _pinA = pin_a;
    }
    
    if (pin_b != NULL) {
        _pinB = pin_b;
    }
}

//<<destructor>>
DCC::~DCC() {
}



void DCC::queueCommand(DCCCommand command) {
    // Queue commands to be sent.
}