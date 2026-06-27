#ifndef AD9833_PORT_H_
#define AD9833_PORT_H_

#include "../GPIO/GPIO.h"
#include "../SPI/SPI.h"

/*
 * Guarda los objetos que apuntan al driver SPI y al pin FSYNC del AD9833, para que puedan ser usados por el driver AD9833.
 */
void AD9833_AttachHardware(SPI& spi, Gpio& fsync);

#endif /* AD9833_PORT_H_ */
