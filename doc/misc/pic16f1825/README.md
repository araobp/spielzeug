# PIC16F1825 LED blinking

2016/12/27

I have just tested LED blinking with PIC16F1825-I/P.

I use PICkit3 to upload code to PIC:

![code_writing](./code_writing.png)

## LED blinking

I have tried out LED blinking powered by AA x 3:

![blinking](./blinking.png)

The test code is as follows:

```
#define _XTAL_FREQ 500000  // 500kHz

#include <xc.h>

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

int main()
{
  OSCCONbits.IRCF = 0b0111;  // 500kHz
  TRISCbits.TRISC3 = 0;  // RC3 as output GPIO
  LATCbits.LATC3 = 1;
  while(1) {
    __delay_ms(1000);
    LATCbits.LATC3 ^= 1;
  }
  return 0;
}
```

## Testing USART

I use  [this module (FT234X)](http://akizukidenshi.com/catalog/g/gM-08461/) to get access to PIC16F1825 from my PC via USB.

Set up:
```
         +---------------------------------+
         |                PIC16F1825       |
         |                 +-----+         |
         |  +-------- VDD 1|     |14 VSS --+
         |  |             2|     |
         |  |             3|     |
       +------+           4|     |
USB ---|FTDI  |--- RX/RC5 5|     |
       |FT234X|--- TX/RC4 6|     |
       +------+           7|     |
                           +-----+
```

## Goal

```
  [ESP8266]--- UART ---[PIC16F1825]
```
