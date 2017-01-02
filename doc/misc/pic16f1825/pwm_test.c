#include <xc.h>
#include <math.h>

#define _XTAL_FREQ 500000

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
#pragma config PLLEN = ON       // PLL Enadble (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

#define DUTY 0.2  // duty 20%

int main(void)
{
    OSCCONbits.IRCF = 0b0111;   // 500kHz
    // P1A is output
    TRISCbits.TRISC5 = 0; 
    // configure CCP1
    CCP1CONbits.CCP1M = 0b1100; // PWA mode
    // configure Timer 2
    T2CONbits.T2CKPS = 0b10;    // Timer 2 prescaler 1:16
    PR2 = 155;                  // 500kHz / 4 / 16 / 50Hz - 1 = 155
    T2CONbits.TMR2ON = 1;       // Timer 2 on
    CCPR1 = PR2 * DUTY;
   while (1)
    {
        CLRWDT();
    }
    return 0;
}