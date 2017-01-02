#define _XTAL_FREQ 16000000 

#include <xc.h>

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = ON        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

#define STRLEN 256

unsigned char t;
int rcindex;
unsigned char rcbuf[STRLEN];

void usart_init(void)
{
    TXSTAbits.TXEN = 1;     // enable transmitter
    TXSTAbits.BRGH = 1;     // x4 multiplier
    RCSTAbits.CREN = 1;     // enable continous receiving

    // configure I/O pins
    APFCON0bits.RXDTSEL = 0;  // RX on RC5
    APFCON0bits.TXCKSEL = 0;  // TX on RC4
    TRISCbits.TRISC5 = 1;     // RX pin is input
    TRISCbits.TRISC5 = 1;     // TX pin is input (automatically configured)

    // 16MHz/9600/(103+1) = 9615 baud
    SPBRGL = 103;           // set baud rate to 9600 baud: (16MHz/9600/16) -1
    
    PIE1bits.RCIE = 1;      // enable USART receive interrupt
    RCSTAbits.SPEN = 1;     // enable USART
}

void putc(unsigned char c)
{
    while (!TXSTAbits.TRMT); // wait until transmit shift register is empty
    TXREG = c;               // write character to TXREG and start transmission
}

void puts(unsigned char *s)
{
    while (*s)
    {
        putc(*s);     // send character pointed to by s
        s++;          // increase pointer location to the next character
    }
}

int main(void)
{
    OSCCONbits.IRCF = 0b1111; // INTOSC frequency 16MHz

    usart_init();

    INTCONbits.PEIE = 1;    // enable peripheral interrupts
    INTCONbits.GIE = 1;     // enable interrupts

    TRISCbits.TRISC3 = 0;   // RC3 as output GPIO
    LATCbits.LATC3 = 1;     // HIGH on RC3

    puts((unsigned char*)("PIC16F1825 init completed"));
            
    while(1)
    {
        __delay_ms(500);
        LATCbits.LATC3 ^= 1;
        CLRWDT();
    }

    return 0;
}

void interrupt ISR(void)
{
    if (PIR1bits.RCIF)  // check if receive interrupt has fired
    {
        t = RCREG;      // read received character to buffer

        // check if received character is not new line character
        // and that maximum string length has not been reached
        if ( (t != '\n') && (rcindex < STRLEN) )
        {
            rcbuf[rcindex] = t; // append received character to string
            rcindex++;          // increment string index
        }
        else
        {
            rcbuf[rcindex++] = '\n';
            rcbuf[rcindex] = '\0';
            rcindex = 0;        // reset string index
            puts(rcbuf);  // echo received string
        }

        PIR1bits.RCIF = 0;      // reset receive interrupt flag
    }
}