#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- setup ports
	P1DIR |= BIT0;              // set P1.0 (LED1) to output
	P1OUT &= ~BIT0;             // clear P1.0 initially
	PM5CTL0 &= ~LOCKLPM5;       // turn on digital I/O

	//-- Setup Timer
	TB0CTL |= TBCLR;            // reset TB0
	TB0CTL |= MC__UP;           // put in UP mode for CCR0
	TB0CTL |= TBSSEL__ACLK;     // chose ACLK (32 KHz)
	TB0CCR0 = 16384;            // Set CCR0 = 16384

	//-- Setup Timer Compare IRQ
	TB0CCTL0 |= CCIE;           // local enable for CCR0
	__enable_interrupt();       // enable maskables
	TB0CCTL0 &= ~CCIFG;         // clear flag

	//-- main loop
	while(1) {}                 // loop forever

	return 0;
}


//------ ISRs ---- //
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P1OUT ^= BIT0;              // toggle LED1
    TB0CCTL0 &= ~CCIFG;         // clear flag
}


