#ifndef DCC_H
#define DCC_H

#include <Arduino.h>
#include <DCCCommand.h>

class DCC {
    public:
        DCC();
        DCC(int pin_a, int pin_b);
        ~DCC();
        void queueCommand(DCCCommand command);
    private:
        int _pinA;
        int _pinB;

        void initializeTimer();
};

#endif
