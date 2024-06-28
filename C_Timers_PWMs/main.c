#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	//-- setup ports
	P1DIR |= BIT0;              // set P1.0 to output (LED1)
	P1OUT |= BIT0;              // set LED1=1 initially
	PM5CTL0 &= ~LOCKLPM5;       // turn on digital I/O
	
	//-- setup timer TB0
	TB0CTL |= TBCLR;            // reset TB0
	TB0CTL |= MC__UP;           // put into UP mode for CCR0
	TB0CTL |= TBSSEL__ACLK;     // choose ACLK (32 KHz)
	TB0CCR0 = 32768;            // set PWM period
	TB0CCR1 = 1638;             // set PWM duty cycle

	//--- setup compare IRQs
	TB0CCTL0 |= CCIE;           // local enable for CCR0
	TB0CCTL1 |= CCIE;           // local enable for CCR1
	__enable_interrupt();       // enable maskable interrupts
	TB0CCTL0 &= ~CCIFG;          // clear flag for CCR0
	TB0CCTL1 &= ~CCIFG;          // clear flag for CCR1

	while(1) {}                 // main loop

	return 0;
}

//--- Interrupt Service Routines ---//
#pragma vector = TIMER0_B0_VECTOR   // ISR for period
__interrupt void ISR_TB0_CCR0(void)
{
    P1OUT |= BIT0;              // turn LED1 ON
    TB0CCTL0 &= ~CCIFG;          // clear flag for CCR0
}

#pragma vector = TIMER0_B1_VECTOR    // ISR for duty cycle
__interrupt void ISR_TB0_CCR1(void)
{
    P1OUT &= ~BIT0;             // turn LED1 OFF
    TB0CCTL1 &= ~CCIFG;          // clear flag for CCR1
}






