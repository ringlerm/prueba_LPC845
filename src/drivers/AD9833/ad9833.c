#include "ad9833.h"

static uint16_t s_outputMode = AD9833_MODE_SINE;

void AD9833_Write(uint16_t data)
{
    const uint8_t highByte = (uint8_t)((data >> 8) & 0xFFU);
    const uint8_t lowByte = (uint8_t)(data & 0xFFU);

    /*
     * pongo FSYNC en bajo para indicar al AD9833 que se va a enviar una palabra de 16 bits.
     * primero se envía el byte mas significativo, luego el menos significativo, y finalmente se pone FSYNC en alto para indicar que termino la palabra de 16 bits.
     */
    FSYNC_LOW();
    SPI_SendByte(highByte);
    SPI_SendByte(lowByte);
    FSYNC_HIGH();
}

void AD9833_SetSineFrequency(float frequency)
{
    uint32_t frequencyWord;
    uint16_t lsb;
    uint16_t msb;

    if (frequency < 0.0F) {
        frequency = 0.0F;
    }

    /*
        la frecuencia se envia en una palabra de 28 bits, que se divide en dos palabras de 16 bits (14 bits "importantes" cada una).
        primero se envía la parte baja, luego la parte alta.
        la parabra de 28 bits se calcula con la formula:
        frequencyWord = (frequency * 2^28) / MCLK
        basicamente la la frecuencia deseada multiplicada por 2^28 y dividida por la frecuencia del reloj maestro del AD9833 (MCLK).
    */
    frequencyWord = (uint32_t)(
        (frequency * 268435456.0F) / (float)AD9833_MCLK_HZ
    );

    frequencyWord &= 0x0FFFFFFFUL; // 0x0FFFFFFFUL = 0000 1111 1111 1111 1111 1111 1111 1111, mascara para quedarme con los 28 bits menos significativos.

    // divido la palabra de 28 bits en dos palabras de 16 bits, primero la parte baja(lsb), luego la parte alta(msb).
    lsb = (uint16_t)(frequencyWord & 0x3FFFU); // 0x3FFFU = 0011 1111 1111 1111, mascara para quedarme con los 14 bits menos significativos.
    msb = (uint16_t)((frequencyWord >> 14) & 0x3FFFU); // Desplazo y aplico misma mascara.
    /*
     *  RESET=1, 
     *  B28=1: se prepara para escuchar palabra de 28 bits(2 palabras de 16 bits, primero parte baja, luego parte alta),
     */
    AD9833_Write(0x2100U);

    /* FREQ0 lsb 14 bits. */
    AD9833_Write((uint16_t)(0x4000U | lsb));

    /* FREQ0 msb 14 bits. */
    AD9833_Write((uint16_t)(0x4000U | msb));

    /* fase = 0. */
    AD9833_Write(0xC000U);

    /* envio tipo señal deseada */
    s_outputMode = AD9833_MODE_SINE;
    AD9833_Write(s_outputMode);
}


/*
    setea el tipo de señal que se desea generar: senoidal, triangular o cuadrada.
    recibe como argumento la constante correspondiente al tipo de señal deseada: AD9833_MODE_SINE, AD9833_MODE_TRIANGLE o AD9833_MODE_SQUARE.
*/
void AD9833_SetOutputMode(uint16_t mode)
{
    if ((mode == AD9833_MODE_SINE) ||
        (mode == AD9833_MODE_TRIANGLE) ||
        (mode == AD9833_MODE_SQUARE)) {
        s_outputMode = mode;
        AD9833_Write(s_outputMode);
    }
}

void AD9833_Init(void)
{
    /* FSYNC inactivo alto cuando no se está enviando ninguna palabra de 16 bits. */
    FSYNC_HIGH();
    AD9833_SetSineFrequency(AD9833_DEFAULT_FREQUENCY);
}
