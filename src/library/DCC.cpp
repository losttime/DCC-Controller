#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <DCC.h>
#include <DCCCommand.h>



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
    free(priorityQueue);
    free(standardQueue);
}



void DCC::queueCommand(DCCCommand command) {
    // Queue commands to be sent.
    command.assemble();

    memcpy(&standardQueue[writePos],&command,sizeof(DCCCommand));
    writePos = (writePos + 1) % STANDARD_QUEUE_SIZE;
}





void DCC::_prepareQueues() {
    priorityQueue = (DCCCommand *)malloc(sizeof(DCCCommand) *PRIORITY_QUEUE_SIZE);
    standardQueue = (DCCCommand *)malloc(sizeof(DCCCommand) *STANDARD_QUEUE_SIZE);

    writePos = 0;
}