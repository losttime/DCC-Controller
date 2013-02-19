#ifndef DCCCOMMAND_H
#define DCCCOMMAND_H

#include <Arduino.h>

class DCCCommand {
    public:
        DCCCommand();
        ~DCCCommand();
        void address(int newAddress);
        void setSpeed(int newSpeed);
        void sendForward(bool isForward);
        void assemble();
        void send();
        void display();
    private:
        int _address;
        int _command;
        int _checksum;
        int _speed;
        bool _forward;

        uint8_t _bitPattern[6];
        byte _bit;
        uint8_t _dccBitPattern[18];
        byte _dccBit;

        void _convertToBitPattern();
        void _addBit(byte bit);
        void _addPreamble();
        void _addAddress();
        void _addCommand();
        void _addChecksum();

        void _commandFromSpeed();
};

#endif