#include "ad9833.h"
#include "ad9833_port.h"

static SPI* s_spi = nullptr;
static Gpio* s_fsync = nullptr;

void AD9833_AttachHardware(SPI& spi, Gpio& fsync)
{
    s_spi = &spi;
    s_fsync = &fsync;
}

extern "C" void FSYNC_LOW(void)
{
    if (s_fsync != nullptr) {
        s_fsync->Set(0U);
    }
}

extern "C" void FSYNC_HIGH(void)
{
    if (s_fsync != nullptr) {
        s_fsync->Set(1U);
    }
}

extern "C" void SPI_SendByte(uint8_t data)
{
    if (s_spi != nullptr) {
        // usando bloqueante para evitar solapamiento de bytes en el buffer de envio del SPI, ya que el AD9833 no tiene buffer y necesita recibir los 16 bits completos para interpretar la palabra.
        s_spi->transmitByteBlocking(data);
    }
}
