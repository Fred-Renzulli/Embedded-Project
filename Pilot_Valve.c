#include <msp430.h>

#define PILOT_PIN BIT5       // Using P2.5 for pilot signal
#define MAX_ATTEMPTS 5
#define DISPERSION_DELAY_MINUTES 2

static int signalCount = 0;

void Pilot_init() {
    P2DIR |= PILOT_PIN;     // Set P2.5 as output
    P2OUT &= ~PILOT_PIN;    // Make sure it's off initially
}

void Pilot_StartSignal_Shutoff() {
    // Shut off pilot signal
    P2OUT &= ~PILOT_PIN;

    // Wait for gas to disperse (2 minutes, assuming 1 MHz clock)
    // 1 minute = 60 seconds = 60,000,000 cycles at 1 MHz
    for (int i = 0; i < DISPERSION_DELAY_MINUTES; i++) {
        __delay_cycles(60000000); // 1 minute delay
    }

    signalCount = 0;  // Reset signal count
    Pilot_StartSignal();  // Retry ignition sequence
}

int Ignition_Occurred() {
    // Placeholder: return 1 if flame sensor detects ignition, 0 otherwise
    // Replace with your actual detection method
    return 0;
}

void Pilot_StartSignal() {
    if (signalCount >= MAX_ATTEMPTS) {
        Pilot_StartSignal_Shutoff();
        return;
    }

    // Send ignition signal
    P2OUT |= PILOT_PIN;
    signalCount++;

    // Hold signal briefly
    __delay_cycles(500000); // 0.5 second pulse
    P2OUT &= ~PILOT_PIN;

    // Wait 5 seconds for ignition
    __delay_cycles(5000000); // 5 second delay

    if (Ignition_Occurred()) {
        // Success: move on
        signalCount = 0;
        // Proceed to next state
    } else {
        // Try again
        Pilot_StartSignal();
    }
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog

    Pilot_init();               // Setup pilot valve
    Pilot_StartSignal();        // Begin ignition attempts

    //while (1);                  // Idle
}
