#ifndef SPI_H_
#define SPI_H_

/* SPI input/output registers. */
#define SPI_TXBUF SPDR
#define SPI_RXBUF SPDR

#define BV(bitno) _BV(bitno)

#define SPI_WAITFOREOTx() do { while (!(SPSR & BV(SPIF))); } while (0)
#define SPI_WAITFOREORx() do { while (!(SPSR & BV(SPIF))); } while (0)


// ATmega256RFR2 SPI pin definitions
#define SCK            1  /* PB1: SPI Clock */
#define MOSI           2  /* PB2: Master Out, Slave In */
#define MISO           3  /* PB3: Master In, Slave Out */
#define CSN            0  /* PB0: SPI Slave Select */


//#define WIZNET_CS       3       /* PB.3 Output as CS for Wiznet ETHERNET*/
#define WIZNET_CS      4  /* PB4: CS for Wiznet */
#define SPI_WIZNET_ENABLE()  ( PORTB &= ~BV(WIZNET_CS) )
#define SPI_WIZNET_DISABLE() ( PORTB |=  BV(WIZNET_CS) )

//#define SD_CS       0       /* PB.0 Output as CS for SD-reader*/
#define SD_CS          5  /* PB5: CS for SD */
#define SPI_SD_ENABLE()  ( PORTB &= ~BV(SD_CS) )
#define SPI_SD_DISABLE() ( PORTB |=  BV(SD_CS) )





/* Define macros to use for checking SPI transmission status depending
   on if it is possible to wait for TX buffer ready. This is possible
   on for example MSP430 but not on AVR. */
#ifdef SPI_WAITFORTxREADY
#define SPI_WAITFORTx_BEFORE() SPI_WAITFORTxREADY()
#define SPI_WAITFORTx_AFTER()
#define SPI_WAITFORTx_ENDED() SPI_WAITFOREOTx()
#else /* SPI_WAITFORTxREADY */
#define SPI_WAITFORTx_BEFORE()
#define SPI_WAITFORTx_AFTER() SPI_WAITFOREOTx()
#define SPI_WAITFORTx_ENDED()
#endif /* SPI_WAITFORTxREADY */

void spi_init(void);

/* Write one character to SPI */
#define SPI_WRITE(data)                         \
  do {                                          \
    SPI_WAITFORTx_BEFORE();                     \
    SPI_TXBUF = data;                           \
    SPI_WAITFOREOTx();                          \
  } while(0)

/* Write one character to SPI - will not wait for end
   useful for multiple writes with wait after final */
#define SPI_WRITE_FAST(data)                    \
  do {                                          \
    SPI_WAITFORTx_BEFORE();                     \
    SPI_TXBUF = data;                           \
    SPI_WAITFORTx_AFTER();                      \
  } while(0)

/* Read one character from SPI */
#define SPI_READ(data)   \
  do {                   \
    SPI_TXBUF = 0;       \
    SPI_WAITFOREORx();   \
    data = SPI_RXBUF;    \
  } while(0)

/* Flush the SPI read register */
#ifndef SPI_FLUSH
#define SPI_FLUSH() \
  do {              \
    SPI_RXBUF;      \
  } while(0);
#endif

#endif /* SPI_H_ */
