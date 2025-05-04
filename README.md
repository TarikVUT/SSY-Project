# SSY-Project
The project for MPC-SSY

---


# ATmega256RFR2 SPI & UART Configuration Web Interface

This project is built for the **ATmega256RFR2** microcontroller and enables bidirectional communication between the device and a web-based interface. It allows you to **view current configuration values** (such as channel, address, etc.) and **edit them via a web form** that sends updates back to the microcontroller.

---

## ✨ Features

- ✅ SPI configuration updated for ATmega256RFR2
- ✅ UART communication updated and extended
- ✅ Web interface to:
  - Display internal variable values (e.g. current channel, address)
  - Submit new configuration values from a form
- ✅ Support for Wiznet Ethernet and SD card SPI interfaces

---

## 📁 Project Structure

```
project-root/
├── spi.h         # SPI configuration header (customized for ATmega256RFR2)
├── spi.c         # SPI initialization and control logic
├── uart\_extd.h   # UART communication interface with updated compatibility
├── uart.c        # UART logic (must be updated to match header & MCU)
├── main.c        # Application logic: read/write via SPI/UART, update from web
├── web/          # Web UI files (HTML/JS/CSS)
└── README.md     # This file

````

---

## 🔧 Changes Made

### SPI (`spi.h`, `spi.c`)
- Pin configuration adjusted to match **ATmega256RFR2 SPI hardware (PORTB)**.
- `spi_init()` function updated to initialize correct DDR/PORT bits and SPI control registers.
- Support for SPI devices: Wiznet (Ethernet), SD card.

### UART (`uart_extd.h`)
- Baud rate macros verified for compatibility with ATmega256RFR2.
- Extended to support USART1 (and optionally USART2/3).
- Buffer size and error code handling retained from original, portable AVR library.

---

## 🌐 Web Interface Functionality

The microcontroller hosts or interacts with a web interface that:
- Displays internal config variables (e.g. current RF channel, network address)
- Allows user to submit new config values via form fields
- Sends updated values back over UART or SPI to the MCU

---

## 🚀 Getting Started

### Requirements
- AVR toolchain (e.g. `avr-gcc`, `avrdude`)
- ATmega256RFR2 development board
- Web browser for interface
- Ethernet/SD/Wiznet modules (depending on setup)

### Build & Flash
```bash
make
avrdude -p atmega256rfr2 -c your_programmer -U flash:w:your_project.hex
````

### Example Usage

1. Connect the board to Ethernet.
2. Open the web UI in your browser.
3. View current config settings.
4. Change a value (e.g. RF channel) and click "Save".
5. The value is sent to the microcontroller and applied.

---

## 📌 Notes

* Ensure proper pinout and voltage compatibility when connecting SPI devices.
* Make sure the `F_CPU` macro is correctly set in your project for accurate baudrate calculations.
* Web server functionality can be provided by Wiznet Ethernet module or externally.

---

## 📄 License

This project is open-source. You are free to use, modify, and distribute it under the terms of the MIT License.

---

## 🙋‍♂️ Questions / Issues

Feel free to [open an issue](https://github.com/your-username/your-repo/issues) or contact me for support or suggestions.

```



