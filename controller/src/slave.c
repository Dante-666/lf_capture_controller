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
#include <avr/wdt.h>
#include <avr/power.h>

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

void USARTSPI_init(void) {
    cli();
    // Clock freq. is 1 Mhz
    // TODO: Change this for 20 MHz
    // Baud rate is 1/16(1+12) Mbps = 4800 bps
    // UBRR = 0x00C;
    UBRR0L = 0x0C;
    // Enable transmitter only
    UCSR0B = 1<<TXEN0 | 1<<TXCIE0 ;
    UCSR0C = 1<<UMSEL01 | 1<<UMSEL00;
    sei();
}

void USARTSPI_tx(uint8_t data) {
    UDR0 = data;
}

void USARTSPI_rx(uint8_t* data) {
    *data = UDR0;
}

void SPI_slave_init(void) {
    cli();
    DDRB = 1<<DDB4;
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

    // Disable modules that are not being used
    wdt_disable();
    power_timer0_disable();
    // TODO: enable this to implement the
    // counting operation
    power_timer1_disable();
    power_timer2_disable();
    power_twi_disable();
    power_adc_disable();
    
    // Set all unused pins as pulled-up inputs
    DDRD &= 0x1F;
    PORTD |= 0xE1;

    // TODO: Check for reset situation once
    // and verify if the reset pin has no effect
    DDRC &= 0x00;
    PORTC |= 0xFF;

    // Data direction has already been set in
    // SPI_master_init()
    PORTB |= 0x2F;
    
    while(1) {}
}

//TODO: count the input pulses as they arrive.
/*ISR(TIMER1_COMPA_vect) {
    glow_led(link);
    link += 1;    
}*/

ISR(SPI_STC_vect) {
}

