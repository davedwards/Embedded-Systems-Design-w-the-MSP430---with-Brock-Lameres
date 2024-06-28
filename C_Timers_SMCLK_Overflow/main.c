#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- setup ports
	P1DIR |= BIT0;              // set P1.0 to output (LED1)
	P1OUT &= ~BIT0;             // clear P1.0 initally (LED1)
	PM5CTL0 &= ~LOCKLPM5;       // turn on digital IO

	//-- setup timer TB0
	TB0CTL |= TBCLR;            // reset TB0
	TB0CTL |= TBSSEL__SMCLK;    // SMCLK as source
	TB0CTL |= MC__CONTINUOUS;   // mode = continuous

	//-- setup overflow IRQ
	TB0CTL |= TBIE;             // local enable for overflow on TB0
	__enable_interrupt();        // global enable for maskable IRQs.
	TB0CTL &= ~TBIFG;           // clear flag

	//-- main loop
	while(1) {}                 // loop forever

	return 0;
}

// --- ISRs
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_Overflow(void)
{
    P1OUT ^= BIT0;              // toggle LED1
    TB0CTL &= ~TBIFG;           // clear flag
}

