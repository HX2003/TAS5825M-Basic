#include <Wire.h>
#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#include "TAS5825M.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

static inline void wiresend(uint8_t x) {
#if ARDUINO >= 100
	Wire.write((uint8_t) x);
#else
	Wire.send(x);
#endif
}

static inline uint8_t wirerecv(void) {
#if ARDUINO >= 100
	return Wire.read();
#else
	return Wire.receive();
#endif
}

/**
 * Reads a given register
 */
uint8_t TAS5825M::readRegister(uint8_t addr){
	Wire.beginTransmission(i2caddr);
	wiresend(addr);
	Wire.endTransmission();
	Wire.requestFrom(i2caddr, 1);
	return wirerecv();
}

/**
 * Writes a given register
 */
void TAS5825M::writeRegister(uint8_t regAddr, uint8_t regValue){
	// Write the register
	Wire.beginTransmission(i2caddr);
	wiresend(regAddr);
	wiresend(regValue);
	Wire.endTransmission();
}


/**
 * Initializes the TAS5825M given its HW selected address
 */
void TAS5825M::begin(uint8_t addr) {
	i2caddr = addr;

	//Reset
	writeRegister(0x00, 0x00);
	//Book
	writeRegister(0x7f, 0x00);
	//Digital volume
	writeRegister(0x4c, 0x30);
	//Play mode
	writeRegister(0x03, 0x03);
	//Set analog gain
	writeRegister(0x54, 0x1E);
	delay(5);
	//Fault clear
	writeRegister(0x78, 0x80);
}

/**
 * Initializes the default TAS5825M address
 */
void TAS5825M::begin(void) {
	begin(TAS5825M_ADDRESS);
}
 
/**
 * Shutdown sequence
 */
void TAS5825M::end(void) {
	//TODO
}
 
