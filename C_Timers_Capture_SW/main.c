#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//--setup ports
	P1DIR |= BIT0;              // set P1.0 to output (LED1)
	P1OUT &= ~BIT0;             // clear P1.0 initially (LED1)

	P4DIR &= ~BIT1;             // set P4.1 to input (SW1)
	P4REN |= BIT1;              // enable resistor on P4.1
	P4OUT |= BIT1;              // makes resistor a pull-up
	P4IES |= BIT1;              // set IRQ sensitivity to H-to-L
	PM5CTL0 &= ~PM5CTL0;        // turn on digital I/O

	// setup port IRQ
	P4IE  |= BIT1;              // local enable for P4.1
	__enable_interrupt();       // enable maskable IRQs
	P4IFG &= ~BIT1;             // clear flag

	//-- setup timer
	TB0CTL |= TBCLR;            // reset timer
	TB0CTL |= MC__CONTINUOUS;   // put into continuous mode
	TB0CTL |= TBSSEL__ACLK;     // choose ACLK
	TB0CTL |= ID__8;            // div-by-8 in prescalar

	//-- setup capture
	TB0CCTL0 |= CAP;            // put CCR0 into capture mode
	TB0CCTL0 |= CM__BOTH;       // sensitive to both edges
	TB0CCTL0 |= CCIS__GND;      // put capture input level at GND




	return 0;
}
