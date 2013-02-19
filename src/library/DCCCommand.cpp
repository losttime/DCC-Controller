#include <Arduino.h>
#include <DCCCommand.h>

// Defined in header:
//int _address;
//int _command;
//int _speed;
//bool _forward;




//<<constructor>>
DCCCommand::DCCCommand() {
}

//<<destructor>>
DCCCommand::~DCCCommand() {
}



void DCCCommand::address(int newAddress) {
    _address = newAddress;
}

void DCCCommand::setSpeed(int newSpeed) {
    _speed = newSpeed;
}

void DCCCommand::sendForward(bool isForward) {
    _forward = isForward;
}

void DCCCommand::assemble() {
    _convertToBitPattern();
}

void DCCCommand::send() {
    _convertToBitPattern();
}





void DCCCommand::_convertToBitPattern() {
    _bit = 0;
    _addPreamble();
    _addBit(0);
    _addAddress();
    _addBit(0);
    _addCommand();
    _addBit(0);
    _addChecksum();
    _addBit(1);
}

void DCCCommand::_addBit(byte bit) {
    // If adding a 1, set the next bit to a 1.
    // Otherwise, set the next bit to a 0.
    if (bit == 1) {
        bitSet(_bitPattern[_bit>>3], _bit & 7);
    } else {
        bitClear(_bitPattern[_bit>>3], _bit & 7);
    }
    _bit++;
}

void DCCCommand::_addPreamble() {
    // Add 14 1's to the bit pattern.
    for(byte i=0; i < 14; i++) {
        _addBit(1);
    }
}

void DCCCommand::_addAddress() {
    for (byte i = 0; i < 8; i++) {
        if (((_address << i) & 128) == 128) {
            _addBit(1);
        } else {
            _addBit(0);
        }
    }
}

void DCCCommand::_addCommand() {
    if (_speed > 0) {
        _commandFromSpeed();
    }

    for (byte i = 0; i < 8; i++) {
        if (((_command << i) & 128) == 128) {
            _addBit(1);
        } else {
            _addBit(0);
        }
    }
}

void DCCCommand::_commandFromSpeed() {
    // Take the least significant digit of speed
    // and tack it on before speed.
    _command = _speed | ((_speed & 1) << 4);

    // Add direction before speed (and duplicated speed bit).
    // Put a 1 in as bit 5 (shown as combining with int 32).
    // Otherwise, do nothing (leave bit 5 as 0);
    if (_forward) {
        _command = _command | 32;
    }

    // Add command header to represent a speed command.
    // Put a 0 as bit 7 and a 1 as bit 6 (01000000).
    // Shown as combinging with int 64.
    _command = _command | 64;
}

void DCCCommand::_addChecksum() {
    _checksum = _address ^ _command;

    for (byte i = 0; i < 8; i++) {
        if (((_checksum << i) & 128) == 128) {
            _addBit(1);
        } else {
            _addBit(0);
        }
    }
}













void DCCCommand::display() {
    Serial.print("Address: ");
    Serial.println(_address);
    Serial.print("Speed:   ");
    Serial.println(_speed);
    Serial.print("Forward: ");
    if (_forward) {
        Serial.println("forward");
    } else {
        Serial.println("backward");
    }
    Serial.println();
    Serial.print("Bits: ");
    for (byte i=0; i < 6; i++) {
        Serial.println(_bitPattern[i], BIN);
    }
}