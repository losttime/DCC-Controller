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
    command.display();
    command.convertToBitPattern();
    command.display();
//    dcc.queueCommand();
//    dcc.showPinAssignments();
}

void loop() {
    // Here is where we listen for commands and send them to the processor
}
