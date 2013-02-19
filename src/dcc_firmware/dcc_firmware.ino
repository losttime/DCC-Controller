#include <DCC.h>
#include <DCCCommand.h>

#define PINA 9
#define PINB 10

DCC dcc;
//DCC dcc(PINA, PINB);

void setup() {
    Serial.begin(9600);
    DCCCommand command;
    command.address(79);
    command.setSpeed(10);
    command.sendForward(true);
    
    dcc.queueCommand(command);
//    dcc.showPinAssignments();
}

void loop() {
    // Here is where we listen for commands and send them to the processor
}

