#include "dgm_i2c.h"

#define WRITE_WAIT_TIME 60
DGM::DGM(){
  _addr = 0x55;
}
DGM::DGM(uint8_t addr){
  _addr = addr;
}

DGM::DGM(uint8_t addr,uint8_t config){
  _addr = addr;
  setConfig(config);
}

void DGM::init(uint8_t addr) {
  _addr = addr;
}


void DGM::setPwm(uint8_t value) {
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_PWM_POS);
  Wire.write(value);
  Wire.endTransmission();
}

void DGM::setI2cAddr(uint8_t value) {
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_I2CADDR_POS);
  Wire.write(value);
  Wire.endTransmission();
  delay(WRITE_WAIT_TIME);
}

void DGM::setConfig(uint8_t value) {
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_CONFIG_POS);
  Wire.write(value);
  Wire.endTransmission();
  delay(WRITE_WAIT_TIME);
}



uint8_t DGM::getConfig() {
  uint8_t received;
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_CONFIG_POS);
  Wire.endTransmission();
  Wire.requestFrom(_addr, (uint8_t)1);
  unsigned int aux = 0;
  while ( aux < sizeof(received) && Wire.available() > 0 )
  {
    received = Wire.read();
    //Serial.print(received[aux], HEX);
    aux++;
  }
  return received;

}

void DGM::calibrateBridge1() {
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_CONFIG_POS);
  Wire.write((byte)0x81);
  Wire.endTransmission();
  uint8_t value = getConfig();
  while( (value & CONFIG_CMD_MASK) ){
    value = getConfig();
    delay(10);
  }
}

void DGM::calibrateBridge2() {
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_CONFIG_POS);
  Wire.write((byte)0x82);
  Wire.endTransmission();
  uint8_t value = getConfig();
  while( (value & CONFIG_CMD_MASK) ){
    value = getConfig();
    delay(10);
  }
}

void DGM::setCh1GainMuxCh(uint8_t value) {
  if( value >= 0 && value <= 3){
    uint8_t config = getConfig();
    value = value << 1;
    config = config | value;
    setConfig(config);
  }
}

void DGM::setCh2GainMuxCh(uint8_t value) {
  if( value >= 0 && value <= 3){
    uint8_t config = getConfig();
    value = value << 3;
    config = config | value;
    setConfig(config);
  }
}

void DGM::setAdcBufferSize(uint8_t value) {
  if( value >= 0 && value <= 3){
    uint8_t config = getConfig();
    value = value << 5;
    config = config | value;
    setConfig(config);
  }
}

float DGM::getTemp() {
  unsigned char received[4];
  float value;
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_TEMPERATURE_POS);
  Wire.endTransmission();
  Wire.requestFrom(_addr, (uint8_t)4);
  unsigned int aux = 0;
  while ( aux < sizeof(received) && Wire.available() > 0 )
  {
    received[aux] = Wire.read();
    //Serial.print(received[aux], HEX);
    aux++;
  }
  memcpy(&value, received, 4);

  return value;

}

float DGM::getHumidity() {
  unsigned char received[4];
  float value;
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_HUMIDITY_POS);
  Wire.endTransmission();
  Wire.requestFrom(_addr, (uint8_t)4);
  unsigned int aux = 0;
  while ( aux < sizeof(received) && Wire.available() > 0 )
  {
    received[aux] = Wire.read();
    //Serial.print(received[aux], HEX);
    aux++;
  }
  memcpy(&value, received, 4);

  return value;

}


float DGM::getVoltege1() {
  unsigned char received[4];
  float value;
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_B1_POS);
  Wire.endTransmission();
  Wire.requestFrom(_addr, (uint8_t)4);
  unsigned int aux = 0;
  while ( aux < sizeof(received) && Wire.available() > 0 )
  {
    received[aux] = Wire.read();
    //Serial.print(received[aux], HEX);
    aux++;
  }
  memcpy(&value, received, 4);

  return value;

}

float DGM::getVoltege2() {
  unsigned char received[4];
  float value;
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_B2_POS);
  Wire.endTransmission();
  Wire.requestFrom(_addr, (uint8_t)4);
  unsigned int aux = 0;
  while ( aux < sizeof(received) && Wire.available() > 0 )
  {
    received[aux] = Wire.read();
    //Serial.print(received[aux], HEX);
    aux++;
  }
  memcpy(&value, received, 4);

  return value;

}

void DGM::getUid(uint8_t *uid) {

  Wire.beginTransmission(_addr);
  Wire.write(PACKET_UID_POS);
  Wire.endTransmission();
  Wire.requestFrom(_addr, (uint8_t)8);
  unsigned int aux = 0;
  while ( aux < 8 && Wire.available() > 0 )
  {
    uid[aux] = Wire.read();
    //Serial.print(received[aux], HEX);
    aux++;
  }

}

float DGM::getCalibratedValue() {
  unsigned char received[4];
  float value;
  Wire.beginTransmission(_addr);
  Wire.write(PACKET_CALIBRATED_VALUE);
  Wire.endTransmission();
  Wire.requestFrom(_addr, (uint8_t)4);
  unsigned int aux = 0;
  while ( aux < sizeof(received) && Wire.available() > 0 )
  {
    received[aux] = Wire.read();
    //Serial.print(received[aux], HEX);
    aux++;
  }
  memcpy(&value, received, 4);

  return value;

}
