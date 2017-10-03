/**
 * File              : src/base.c
 * Author            : Siddharth J. Singh <j.singh.logan@gmail.com>
 * Date              : 11.09.2017
 * Last Modified Date: 15.09.2017
 * Last Modified By  : Siddharth J. Singh <j.singh.logan@gmail.com>
 */
#ifndef __TWEAK__
#define __AVR_ATmega328P__ 
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

register uint8_t link asm("r2");
register uint8_t buff asm("r3");

void TIMER_init(void) {
    cli();
    TCCR1B |= 1<<CS11 | 1<<CS10; // Prescaler by 1024 
    ICR1 = 15624; // 16000000/1024 -1, clock starts with 0 in uC, count till 1 second
    TCCR1B |= 1<<WGM12; // Set CTC mode
    TIMSK1 |= 1<<ICIE1; // Enable interrupt on match
    sei();
}

void SPI_slave_init(void) {
    cli();
    DDRB = 1<<DDB6;
    PORTB = 1<<PORTB4 | 1<<PORTB5 | 1<<PORTB7;
    SPCR = 1<<SPIE | 1 <<SPE | 1<<SPR0;
    sei();
}

void SPI_slave_tx(uint8_t data) {
    UDR0 = data;
}

void SPI_slave_rx(uint8_t* data) {
    *data = UDR0;
}

int main(void) {

    SPI_slave_init();

    while(1) {}
}

//TODO: count the input pulses as they arrive.
/*ISR(TIMER1_COMPA_vect) {
    glow_led(link);
    link += 1;    
}*/

ISR(SPI_STC_vect) {
}

