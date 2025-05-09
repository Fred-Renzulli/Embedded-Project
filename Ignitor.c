#include <msp430.h>

void thermostat_init(int Callforheat) {
    // Set P2.0 as output
    P2DIR |= BIT0;

    // Turn on LED if Callforheat is 1, otherwise turn it off
    if (Callforheat == 1) {
        P2OUT |= BIT0;   // Set P2.0 high
    } else {
        P2OUT &= ~BIT0;  // Set P2.0 low
    }
}

Ignitor_Spark(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    int Callforheat = 1;        // Simulate your condition

    thermostat_init(Callforheat);     // Call your function

//while (1);                  // Infinite loop
}



