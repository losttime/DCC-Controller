#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <DCC.h>
#include <DCCCommand.h>

DCCCommand *priorityQueue;
DCCCommand *standardQueue;
volatile byte readPos;

//<<constructor>>
DCC::DCC() {
    _prepareQueues();
    _initializeTimer();
}

//<<constructor>>
DCC::DCC(int pin_a, int pin_b) {
    if (pin_a != NULL) {
        _pinA = pin_a;
    }
    
    if (pin_b != NULL) {
        _pinB = pin_b;
    }

    _prepareQueues();
    _initializeTimer();
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
    readPos = 0;
}

void DCC::_initializeTimer() {
    // set the short count and long count
    _short_count = 115;
    _long_count = 199;

    // Set the relevant pins to output mode
    // Set pin 1 and 2 on port B to output mode
    DDRB |= (1<<DDB1) | (1<<DDB2);

    // Change the timer registers
    // Setting COM1A1/COM1B1 = 0 and COM1A0/COM1B0 = 1
    //   means toggle OC1A/OC1B on Compare Match
    // Setting WGM12 = 1 and WGM10, WGM11, WGM13 = 0
    //   means set CTC mode (Clear timer when the interupt fires.
    // Setting CS11 = 1 and CS10, CS12 = 0
    //   mean set an 8 bit prescaler
    // Setting ICNC1 = 0
    //   means leave "Input Capture Noise Canceler" off
    //   otherwise any input change must be given at least 4x
    //   on the Input Capture Pin (not used here)
    // Setting ICES1 = 0
    //   means the interrupt is triggered on the falling edge
    //   of the Input Capture Pin (not used here)
    TCCR1A = (0<<COM1A1) | (1<<COM1A0) | (0<<COM1B1) | (1<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B = (0<<ICNC1)  | (0<<ICES1)  | (0<<WGM13)  | (1<<WGM12)  | (0<<CS12)  | (1<<CS11) | (0<<CS10);

    // set the timer length 58us
    OCR1A = OCR1B = _short_count;
    
    // force a toggle on OC1B so OC1B and OC1A will always
    // compliment each other
    TCCR1C |= (1<<FOC1B);

    // Enable the compare match interrupt
    TIMSK1 |= (1<<OCIE1A);
}





ISR(TIMER1_COMPA_vect) {
    // if the pin is in high mode, the low has already been sent
    // and now we're on the second pass.
    // It's time to change.
/*
    if (PINB & (1<<PINB1)) {
        // get the current packet
        DCCCommand command;
        memcpy(&command,&standardQueue[readPos],sizeof(DCCCommand));
        readPos = (readPos + 1) % STANDARD_QUEUE_SIZE;
    }
*/
    digitalWrite(13, !digitalRead(13));
}