#include <msp430.h>

void changeRGBLED(char Red, char Green, char Blue);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

    P6DIR |= BIT0 | BIT1 | BIT2;                     // P1.6 and P1.7 output
    P6SEL0 |= BIT0 | BIT1 | BIT2;                    // P1.6 and P1.7 options select
    
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    TB3CCR0 = 1000-1;                         // PWM Period
    TB3CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB3CCR1 = 750;                            // CCR1 PWM duty cycle
    TB3CCTL2 = OUTMOD_7;                      // CCR2 reset/set
    TB3CCR2 = 250;                            // CCR2 PWM duty cycle
    TB3CCTL3 = OUTMOD_7;                      // CCR2 reset/set
    TB3CCR3 = 100;                             // CCR2 PWM duty cycle
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR

    while(1){
        //Change Red
        changeRGBLED(255, 0, 0);    //R, B, G given as 0-255
        __delay_cycles(1000000);
        
        //Change Green
        changeRGBLED(0, 255, 0);
        __delay_cycles(1000000);
        
        //Change Blue
         changeRGBLED(0, 0, 255);
         __delay_cycles(1000000);
    }
}
//ChangeRGBLED takes in 0-255 and produces the correct duty cycle
void changeRGBLED(char Red, char Green, char Blue){
    TB3CCR1 = Blue << 2; //Set Blue
    TB3CCR1 = Green << 2; //Set Green   
    TB3CCR1 = Red << 2; //Set Red
}

  
  
  
  
  
  

