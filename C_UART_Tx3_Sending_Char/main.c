#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	//-- setup UART A1
	UCA1CTLW0 |= UCSWRST;       // put into SW reset

	UCA1CTLW0 |= UCSSEL__SMCLK; // choose SMCLK=BRCLK
	UCA1BRW = 8;                // prescalar = 8
	UCA1MCTLW = 0xD600;         // OS16=low freq, set modulation

	P4SEL1 &= ~BIT3;            // changes P4.3 function to A1 UART Tx
	P4SEL0 |= BIT3;

	PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

	UCA1CTLW0 &= ~UCSWRST;      // takes UART A1 out of SW reset

	int i;

	while(1)
	{
	    UCA1TXBUF = 'A';        // transmits ASCII code for 'A' over UART A1
	    for(i=0;i<10000;i++) {} // delay
	}
	
	return 0;
}
