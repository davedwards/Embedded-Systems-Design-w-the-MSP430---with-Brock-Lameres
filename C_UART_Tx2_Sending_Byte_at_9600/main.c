#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	//-- setup UART
	UCA1CTLW0 |= UCSWRST;        // put UART A1 to SW reset

	UCA1CTLW0 |= UCSSEL__ACLK;  // Choose ACLK for UART A1
	UCA1BRW = 3;                // setprescalar to 3
	UCA1MCTLW = 0x9200;         // setup modulation

	//--setup pins
	P4SEL1 &= ~BIT3;            // Want p4.3 to use UART A1 Tx
	P4SEL1 |= BIT3;             // P4SEL1.3:P4SEL0.3 = 01
	PM5CTL0 &= ~LOCKLPM5;       // turn on I/O

	UCA1CTLW0 &= ~UCSWRST;        // take UART A1 our of SW reset

	//-- main loop
	int i;

	while(1)
	{
	    UCA1TXBUF = 0x55;       // transmit 0x55 over UART A1 Tx
	    for(i=0; i<10000;i=i+1) {}
	}
	
	return 0;
}
