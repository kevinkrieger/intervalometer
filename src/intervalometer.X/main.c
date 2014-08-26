/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <math.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/


uint16_t i = 0;
extern uint16_t interval_s;
extern uint8_t interval;
extern int button_pressed;
extern uint16_t wdtwakeups;
uint16_t wakeups = 0;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/


void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    while(1)
    {
#ifdef DEBUG
        if(button_pressed) {
            SHUTTER = 1;
            __delay_ms(SHUTTER_LENGTH_MS);
            SHUTTER = 0;
            INT0IF = 0;
            INT0IE = 1;
            button_pressed = 0;
        }
        RB2 ^= 1;
        __delay_ms(50);
        SLEEP();
#else
        
        if(button_pressed) {
            INT0IE = 0;
            increment_interval();
            display_interval();
            INT0IF = 0;
            
            __delay_ms(DISPLAY_TIME_MS);
            store_interval();
            button_pressed = 0;
            INT0IE = 1;
        } else {
            LED1 ^= 1;

            wakeups++;
            RA0 = 0;
            if(wakeups == wdtwakeups) {
                takepicture();
                wakeups = 0;
            }
        }
        prepare_for_sleep();
        SLEEP();
#endif

     /*   pot_pos_average = 0;
        for(i = 0; i<NUM_AVERAGES;i++) {
            ADCON0bits.GO_DONE = 1; // Start conversion, should take about 20us
            while(ADCON0bits.GO_DONE); // wait
          //  pot_position = ((ADRESH << 8) | (ADRESL));
           // pot_position = pot_position >> 6;
            pot_position = ADRESH;
            pot_pos_average += pot_position;
        }
        */
        /*pot_pos_average /= NUM_AVERAGES;
        pot_position = pot_pos_average;*/
       // if (fabs(pot_position - prev_position) < 100) {
       //     prev_position = pot_position;
       //     continue;
       // }

     //   prev_position = pot_position;
       // servo_position = (pot_position >> 2);
        /*pulse_length_us = 8*pot_position + 500; // y=8x+500 us approximately
                                                //(really y=2000x/255 + 500
        if(pulse_length_us < 500) pulse_length_us = 500;
        if(pulse_length_us > 2500) pulse_length_us = 2500;*/
        /*
         * Servo timing :   1ms pulse is minimum position
         *                   2ms pusle is maximum
         *                   20ms period
         */
        //for( i = 0; i < pulse_length_us / 4; i++) {
        //   __delay_us(4);
        //}
        /* Set timer0 to appropriate value and wait for it to overflow*/
       // TMR0IF = 0;
 //       TMR0 = 256 - (pulse_length_us - 1000)/4;
        //TMR0 = 250;
        //while(!TMR0IF);
        //__delay_us(1000);
     //   for (i = 0; i< 10; i++){
        /*GPIObits.GP4 = 1;
        TMR1IF = 0;
        TMR1 = 0xFFFF - pulse_length_us;
        while(!TMR1IF);

        GPIObits.GP4 = 0;
        __delay_ms(18);
        __delay_us(480);*/
     //   }
    }

}

