#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	//-- setup ports
	P1DIR |= BIT0;              // set P1.0 to output (LED1)
	P1OUT &= ~BIT0;             // set P1.0 LOW initially (LED1)
	PM5CTL0 &= ~LOCKLPM5;       // turn on digital IO
	
	//-- setup timer TB0
	TB0CTL |= TBCLR;            // reset timer
	TB0CTL |= MC__CONTINUOUS;   // choose continuous mode
	TB0CTL |= TBSSEL__SMCLK;    // choose SMCLK (1MHz)
	TB0CTL |= ID__4;            // divide by 4 to get 250KHz

	//-- setup IRQs
	TB0CTL |= TBIE;             // local enable for TB0 overflow
	__enable_interrupt();       // enable maskables
	TB0CTL &= ~TBIFG;           // clear flag

	//-- main loop
	while(1) {}                 // loop forever

	return 0;
}

//--- ISRs -------//
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_Overflow(void)
{
    P1OUT ^= BIT0;              // toggle LED1
    TB0CTL &= ~TBIFG;           // clear flag
}
