#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- Setup UART
	UCA1CTLW0 |= UCSWRST;       // put UART A! into SW reset

	UCA1CTLW0 |= UCSSEL__SMCLK; // Choose SMCLK for UART A1
	UCA1BRW = 8;                // Set Prescalar to 8
	UCA1MCTLW |= 0xD600;        // Configure modulation settings + low freq

	//-- setup ports
	P4SEL1 &= ~BIT3;            // P4SEL1.3 : P4SEL0.3 = 01
	P4SEL0 | BIT3;              // puts UART A1 Tx on P4.3

	PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

	UCA1CTLW0 &= ~UCSWRST;       // put UART A1 into SW reset

	// main loop

	int i;

	while(1)
	{
	    UCA1TXBUF = 0x4D;           // send x4D out over UART A1
	    for(i=0; i<1000; i=i+1){}   // delay between frames
	}



	return 0;
}
