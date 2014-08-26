/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"
#include "system.h"

volatile uint16_t interval_s;
volatile uint8_t interval;
volatile uint16_t wdtwakeups;
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* Take a picture */
void takepicture() {
    SHUTTER = 1;
    __delay_ms(SHUTTER_LENGTH_MS);
    SHUTTER = 0;
}

/* Function to increment interval to the next available interval */
void increment_interval() {
    interval += 1;
    if(interval > 7) {
        interval = 0;
    }
    set_interval_s();
}

/* Set the global interval_s value in seconds using the global interval value */
void set_interval_s() {
     switch(interval) {
        case 0:
            interval_s = 10; //2 second WDT 5 times
            WDTCON = 0b10111;
            wdtwakeups = 5;
            break;
        case 1:
            interval_s = 30;//2 second WDT 15 times
            WDTCON = 0b10111;
            wdtwakeups = 15;
            break;
        case 2:
            interval_s = 60;//2 second WDT 30 times
            WDTCON = 0b10111;
            wdtwakeups = 30;
            break;
        case 3:
            interval_s = 300;
            //2 second WDT 150 times
            WDTCON = 0b10111;
            wdtwakeups = 150;//5 min
            break;
        case 4:
            interval_s = 600;
            //2 second WDT 300 times
            WDTCON = 0b10111;
            wdtwakeups = 300;//10 min
            break;
        case 5:
            interval_s = 1800;//2 second WDT 900 times
            WDTCON = 0b10111;
            wdtwakeups = 900;  //30 min
            break;
        case 6:
            interval_s = 3600;//2 second WDT 1800 times
            WDTCON = 0b10111;
            wdtwakeups = 1800;  // 1hr
            break;
        case 7:
            interval_s = 86400; //2 second WDT 43200 times
            WDTCON = 0b10111;
            wdtwakeups = 43200;// 24hr
            break;
        default:
            break;
    }
}

/* Display the current interval on the LEDs */
void display_interval() {
    /* Interval is a 3 bit number */
    LED1 = (interval & 0x01) >> 0;
    LED2 = (interval & 0x02) >> 1;
    LED3 = (interval & 0x04) >> 2;
}

/* Store the interval in memory in case of power outage */
void store_interval() {
    eeprom_write(0x00,interval);
}

void prepare_for_sleep() {
    /* Turn off all LEDS */
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    /* */
}

void InitApp(void)
{
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    ANSEL = 0b00000000;
    TRISA = 0b00000000;
    TRISB = 0b00000001; /* Only RB0 is input (external interrupt button) */
    OPTION_REG = 0b11010111; // pullups disabled, interrupt on rising RB0, Timer 0 clock is internal, prescalar is for TMR0, 1:256 rate

    /* WDT setup */
    PSA = 1;
    PS0 = 0;
    PS1 = 0;
    PS2 = 0;

    interval = eeprom_read(0x00);
    set_interval_s();
    display_interval();
    __delay_ms(DISPLAY_TIME_MS);
    
 

    /* RB0 interrupt enable */
    INT0IF = 0;
    INT0IE = 1;
    PEIE = 0; /* Not needed for RB0 */
    GIE = 1;


    //TRISIO = 0b001001; /* TRISIO3 is always read as 1, opendrain. TRISIO0 set for adc input*/
    //GPIO = 0x00;
    //ADCON0 = 0x00; /* left  justified, VDD reference, channel 0, converter off*/
    //ANSEL = 0b1010001; /* FOSC/16 (since using 4MHz internal clock) and select AN0 for adc */
    //ADCON0bits.ADON = 1; /* Turn converter on */
    //#asm
    //clrwdt;
    //bsf STATUS, RP0;
    //movlw   b"xxxx0xxx";
    //movwf   OPTION_REG;
    //bcf STATUS, RPO;
    //#endasm
    //PSA = 0;
    /* Change prescalar to TIMER0, see datasheet */
    //T0CS = 0; /*timer mode*/
    //PS0 = 0; /* Timer0 is clkout/2, therefore FOSC/16
      //        * (4MHz clock means 250ns clocks, therefore 4us TIMER0 clock*/
    //TMR1ON = 1;
}
