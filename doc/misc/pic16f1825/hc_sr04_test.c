#define _XTAL_FREQ 16000000 

#include <xc.h>
#include <stdio.h>

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

void init(void)
{
    TXSTAbits.TXEN = 1;     // enable transmitter
    TXSTAbits.BRGH = 1;     // x4 multiplier
    RCSTAbits.CREN = 1;     // enable continous receiving

    // configure I/O pins
    APFCON0bits.RXDTSEL = 0;  // RX on RC5
    APFCON0bits.TXCKSEL = 0;  // TX on RC4
    ANSELAbits.ANSA2 = 0;     // RA2 as digital input
    ANSELCbits.ANSC2 = 0;     // RC2 as digital input
    TRISCbits.TRISC5 = 1;     // RX pin is input
    TRISCbits.TRISC5 = 1;     // TX pin is input (automatically configured)
    TRISCbits.TRISC2 = 0;     // output to HC-SR04 Trig pin
    TRISAbits.TRISA2 = 1;     // input from HC-SR04 Echo pin

    // 16MHz/9600/(103+1) = 9615 baud
    SPBRGL = 103;           // set baud rate to 9600 baud: (16MHz/9600/16) -1
    
    PIE1bits.RCIE = 1;      // enable USART receive interrupt
    RCSTAbits.SPEN = 1;     // enable USART
}

void usart_putc(unsigned char c)
{
    while (!TXSTAbits.TRMT); // wait until transmit shift register is empty
    TXREG = c;               // write character to TXREG and start transmission
}

void usart_puts(unsigned char *s)
{
    while (*s)
    {
        usart_putc(*s);     // send character pointed to by s
        s++;          // increase pointer location to the next character
    }
}

int main(void)
{
    OSCCONbits.IRCF = 0b1111; // INTOSC frequency 16MHz

    init();

    INTCONbits.PEIE = 1;    // enable peripheral interrupts
    INTCONbits.GIE = 1;     // enable interrupts

    TRISCbits.TRISC3 = 0;   // RC3 as output GPIO
    LATCbits.LATC3 = 1;     // HIGH on RC3

    usart_puts((unsigned char*)("PIC16F1825 init completed\n"));
    
    // Timer1 at 1MHz
    T1CONbits.TMR1CS = 0;     // FOSC/4 internal clock
    T1CONbits.T1CKPS = 0b10;  // 1:4 prescaler
    
    unsigned int count;
    unsigned int d;
    
    while(1)
    {
        __delay_ms(500);
        LATCbits.LATC3 ^= 1;
        
        TMR1H = 0;
        TMR1L = 0;

        // HC-SR04 Trigger pin
        LATCbits.LATC2 = 1;
        __delay_us(10);
        LATCbits.LATC2 = 0;
        
        // HC-SR04 Echo pin
        while(!PORTAbits.RA2);
        TMR1ON = 1;
        while(PORTAbits.RA2);
        TMR1ON = 0;
        
        count = (TMR1L | (TMR1H<<8)); //Reads Timer Value
        d = (unsigned int)(count/58.82);
        if (d >= 2 || d <= 400) {
            sprintf(rcbuf, "%u\n", d);
            usart_puts(rcbuf);
        } else {
            usart_puts((unsigned char*)("distance out of range\n"));
        }
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
            usart_puts(rcbuf);  // echo received string
        }

        PIR1bits.RCIF = 0;      // reset receive interrupt flag
    }
}