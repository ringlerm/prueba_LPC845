#ifndef AD9833_H_
#define AD9833_H_

#include "vars.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AD9833_MCLK_HZ             25000000UL /* 25 MHz. */
#define AD9833_DEFAULT_FREQUENCY   1000.0F // 1khz por default, se puede cambiar con AD9833_SetSineFrequency()

#define AD9833_MODE_SINE           0x2000U
#define AD9833_MODE_TRIANGLE       0x2002U
#define AD9833_MODE_SQUARE         0x2028U

void FSYNC_LOW(void);
void FSYNC_HIGH(void);
void SPI_SendByte(uint8_t data);

void AD9833_Write(uint16_t data);
void AD9833_SetSineFrequency(float frequency);
void AD9833_SetOutputMode(uint16_t mode);
void AD9833_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* AD9833_H_ */
