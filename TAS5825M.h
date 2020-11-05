#ifndef _TAS5825M_H_
#define _TAS5825M_H_

class TAS5825M {
public:
  void begin(uint8_t addr);
  void begin(void);
  void end(void);
  
 private:
  uint8_t i2caddr;

  uint8_t readRegister(uint8_t addr);
  void writeRegister(uint8_t addr, uint8_t value);
};

#define TAS5825M_ADDRESS 0x4c

#endif
