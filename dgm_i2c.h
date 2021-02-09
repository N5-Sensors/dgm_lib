#ifndef DGM_I2C_H
#define DGM_I2C_H
#include <Arduino.h>
#include <Wire.h>

//#define dgm_i2c_address ((uint8_t)0x55)
#define PACKET_CONFIG_POS           (0u)
#define PACKET_I2CADDR_POS          (PACKET_CONFIG_POS+1u)
#define PACKET_PWM_POS              (PACKET_I2CADDR_POS+1u)
#define PACKET_B1_POS               (PACKET_PWM_POS+1u)
#define PACKET_B2_POS               (PACKET_B1_POS+4u)
#define PACKET_TEMPERATURE_POS      (PACKET_B2_POS+4u)
#define PACKET_HUMIDITY_POS         (PACKET_TEMPERATURE_POS+4u)
#define PACKET_UID_POS              (PACKET_HUMIDITY_POS+4u)
#define PACKET_CALIBRATED_VALUE     (PACKET_UID_POS+8u)

#define DGM_ADC_BUFFER_SIZE_1 0x00
#define DGM_ADC_BUFFER_SIZE_10 0x01
#define DGM_ADC_BUFFER_SIZE_50 0x02
#define DGM_ADC_BUFFER_SIZE_100 0x03


/*CONFIG MASKS*/
#define CONFIG_PULLUP_MASK (1u) //if 1 pull up active if 0 open drain strong low
#define CONFIG_B1GAINMUXCH_MASK ((3u)<<1)
#define CONFIG_B2GAINMUXCH_MASK ((3u)<<3)
#define CONFIG_ADCAVRGBUFFSIZE_MASK ((3u)<<5)
#define CONFIG_CMD_MASK ((1u)<<7)

class DGM
{
  public:
    DGM();
    DGM(uint8_t addr);
    DGM(uint8_t addr,uint8_t config);
    void init(uint8_t addr);
    float getTemp();
    float getHumidity();
    float getVoltege1();
    float getVoltege2();
    uint8_t getConfig();
    void setPwm(uint8_t value);
    void setI2cAddr(uint8_t value);
    void setConfig(uint8_t value);
    void setCh1GainMuxCh(uint8_t value);
    void setCh2GainMuxCh(uint8_t value);
    void setAdcBufferSize(uint8_t value);
    void calibrateBridge1();
    void calibrateBridge2();
    float getCalibratedValue();
    uint8_t _addr = 0x55;
};

#endif
