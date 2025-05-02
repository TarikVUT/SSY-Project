#include <avr/io.h>
#include "spi.h"
#include "globals.h"

/*
 * Initialize SPI bus.
 */

//~ // From working SPI ENC28J60 driver
//~ #define ENC28J60_CONTROL_PORT   PORTB
//~ #define ENC28J60_CONTROL_DDR    DDRB
//~ 
//~ #define ENC28J60_CONTROL_CS PORTB6
//~ #define ENC28J60_CONTROL_SO PORTB3
//~ #define ENC28J60_CONTROL_SI PORTB2
//~ #define ENC28J60_CONTROL_SCK PORTB1
//~ #define ENC28J60_CONTROL_SS PORTB0
//~ 
//~ // set CS to 0 = active
//~ #define CSACTIVE ENC28J60_CONTROL_PORT&=~(1<<ENC28J60_CONTROL_CS)
//~ // set CS to 1 = passive
//~ #define CSPASSIVE ENC28J60_CONTROL_PORT|=(1<<ENC28J60_CONTROL_CS)
//
//~ #define waitspi() while(!(SPSR&(1<<SPIF)))
 

void
spi_init(void)
{
  // CS PIN for FLASH
  DDRB	|= _BV(WIZNET_CS); // CS to OUT && Disable
  SPI_WIZNET_DISABLE();
  

  
  // === Set MOSI, SCK, SS (CSN) as Output ===
  DDRB |= _BV(MOSI) | _BV(SCK) | _BV(CSN);

  // === Set MISO as Input ===
  DDRB &= ~_BV(MISO);

  // === Optional: Enable pull-up on MISO to avoid floating input ===
  PORTB |= _BV(MISO);

  // === Optional: Pull high unused outputs initially ===
  PORTB |= _BV(MOSI) | _BV(SCK) | _BV(CSN);

  // === Enable SPI in Master Mode, SPI Mode 0 ===
  SPCR = _BV(SPE) | _BV(MSTR);

  // === Set SPI Clock Speed ===
#if defined(SPI_8_MHZ)
  SPSR = _BV(SPI2X);  // F_CPU / 2
#elif defined(SPI_4_MHZ)
  SPSR = 0x00;        // F_CPU / 4
#else
  SPSR = 0x00;        // Default to F_CPU / 4
#endif
//   /* Initalize ports for communication with SPI units. */
//   /* CSN=SS and must be output when master! */
//   DDRB  |= _BV(MOSI) | _BV(SCK) | _BV(CSN);
//   PORTB |= _BV(MOSI) | _BV(SCK);
 
//   /* Enables SPI, selects "master", clock rate FCK / 4 - 4Mhz, and SPI mode 0 */
//   SPCR = _BV(SPE) | _BV(MSTR);
// #if defined(SPI_8_MHZ)
//   SPSR = _BV(SPI2X); //FCK / 2 - 8Mhz
// #elif defined (SPI_4_MHZ)
//   SPSR = 0x0; //FCK / 4 - 4Mhz
// #else
//   SPSR = 0x0; //FCK / 4 - 4Mhz
//#endif


}
