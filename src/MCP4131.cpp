/*
 Library written for use with Common-Anode 7-Segment Display. For more information on how to use this library,
 please refer to the github README.
 Written by: Derek Duncan
 Data: 4/7/2018
*/

#include "Arduino.h"
#include "MCP4131.h"
#include <SPI.h>

int slaveSelectPin;

MCP4131::MCP4131(int slavePin) {
    SPI.begin();
    slaveSelectPin = slavePin;
	pinMode(slavePin, OUTPUT);
}

byte MCP4131::readWiper() {
    // Adjust SPI settings to fit MCP4131
    SPI.beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0));
    
    // take the SS pin low to select the chip:
    digitalWrite(slaveSelectPin, LOW);
    
    // Send the MSB of the 16bit read command to receive CMDR bit to check
    byte error = SPI.transfer(0x0F);

    //if(checkIfError(error))
    //    return;
        
    // Send LSB to retrieve the value of the Wiper
    byte result = SPI.transfer(0xFF);
    
    // take the SS pin high to de-select the chip:
    digitalWrite(slaveSelectPin, HIGH);
    SPI.endTransaction();
    
    Serial.println(error);
    Serial.println(result);
    
    return result;
}

void MCP4131::sendCommand() {
    // Adjust SPI settings to fit MCP4131
    SPI.beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0));
    
    // take the SS pin low to select the chip:
    digitalWrite(slaveSelectPin, LOW);
    
}

boolean MCP4131::checkIfError(byte errorByte) {
    boolean errorBoolean = (errorByte & 0x02) >> 1;
    return !errorBoolean;
}
