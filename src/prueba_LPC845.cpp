/*
 * Minimal AD9833 test for LPC845.
 */

#include "Defines.h"
#include "Hardware.h"
#include "drivers/SPI/SPI.h"
#include "drivers/AD9833/ad9833.h"
#include "drivers/AD9833/ad9833_port.h"

int main()
{
    /*
     * PIN_AD9833_SCLK  -> AD9833 CLK (clock serie generado por el micro)
     * PIN_AD9833_SDATA -> AD9833 DATA (entrada de datos serie desde el micro)
     * PIN_AD9833_FSYNC -> AD9833 FNC/FSYNC (chip select. Cuando esta en LOW, el AD9833 interpreta los 16 bits que llegan por SDATA)
     * LPC845 GND       -> AD9833 GND
     */
    Gpio ad9833Sclk(PIN_AD9833_SCLK, OUTPUT);
    Gpio ad9833Sdata(PIN_AD9833_SDATA, OUTPUT);
    Gpio ad9833Fsync(PIN_AD9833_FSYNC, OUTPUT);

    /*
     * SPI0 master, MSB primero, SPI_MODE: 2.
     * el AD9833 interpreta los datos en el flanco de bajada de SCLK; por eso se usa MODE2 que mantiene SCLK en alto cuando esta inactivo
     * y hace que MOSI sea estable antes de ese flanco de bajada.
     * FSYNC es controlado manualmente por el driver AD9833, no por el driver SPI. Por eso no se pasa como argumento al constructor de SPI.
     */
    SPI ad9833Spi(
        ad9833Sclk,
        ad9833Sdata,
        SyncCommSPI::DEFAULT_FREQUENCY,
        SPI::SPI_CHANNEL0,
        true,
        SyncCommSPI::MSB_FIRST,
        SyncCommSPI::MODE2
    );

    AD9833_AttachHardware(ad9833Spi, ad9833Fsync);
    AD9833_Init();

    while (1) {
        
    }
}
