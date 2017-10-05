/**
 * File              : src/master.c
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

#define FORWARD     5
#define BACKWARD    7
#define MOTORFREE   11

#define START       17
#define SUCCESS     19
#define FAILURE     23
#define STOP        29

#define FETCH       31

#define X_F         0x01
#define Y_F         0x04
#define Z_F         0x10
#define X_B         0x03
#define Y_B         0x0C
#define Z_B         0x30

register uint8_t flag asm("r2");

void USART_init(void) {
    cli();
    // Clock freq. is 1 Mhz
    // TODO: Change this for 20 MHz
    // Baud rate is 1/16(1+12) Mbps = 4800 bps
    // UBRR = 0x00C;
    UBRR0L = 0x0C;
    // Enable both the transmitter and reciever interrupts and set 8 bits
    UCSR0B = 1<<RXCIE0 | 1<<RXEN0 | 1<<TXEN0 | 1<<TXCIE0;
    // Set parity bit on with even parity, put 2 stop bits for tx.
    UCSR0C =  1<<UPM01 | 1<<USBS0 | 1<<UCSZ01 | 1<<UCSZ00;
    sei();
}

void USART_tx(uint8_t data) {
    UDR0 = data;
}

void USART_rx(uint8_t* data) {
    *data = UDR0;
}

void SPI_master_init(void) {
    cli();
    DDRB = 1<<DDB5 | 1<<DDB3 | 1 << DDB2; 
    SPCR = 1<<SPIE | 1<<SPE | 1<<MSTR | 1<<SPR0;
    sei();
}

void SPI_master_tx(uint8_t data) {
    SPDR = data;
}

void SPI_master_rx(uint8_t* data) {
    *data = SPDR;
}

int main(void) {

    USART_init();
    SPI_master_init();

    flag = 0x00;
    
    // Set this to be a slave selector port
    // At most 3 slaves will be used for 3DOF camera mover.
    DDRC |= 1<<DDC0 | 1<<DDC1;
    PORTC |= 1<<PORTC0 | 1<<PORTC1;

    DDRB |= 1<<DDB2;
    PORTB |= 1<<PORTB2;
   
    // Disable modules that are not being used
    wdt_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();
    power_twi_disable();
    power_adc_disable();

    // Set all unused pins as pulled-up inputs
    DDRD &= 0x03;
    PORTD |= 0xFC;

    // TODO: Check for reset situation once
    // and verify if the reset pin has no effect
    DDRC &= 0x03;
    PORTC |= 0xFC;

    // Data direction has already been set in
    // SPI_master_init()
    PORTB |= 0x13;
    
    while(1) {}
}

ISR(USART_RX_vect) {
    uint8_t data;
    USART_rx(&data);

    if(flag == 0x80) {

        uint8_t s_retval;
        uint8_t motors = 0x00;
        // Data flow commences here
        // Set the motor directions here
        if(data & X_F) {
            PORTB &= 0xFB;
            SPI_master_tx(START);
            if(data & (X_B ^ X_F))
                SPI_master_tx(BACKWARD);
            else
                SPI_master_tx(FORWARD);
            SPI_master_tx(FETCH);
            PORTB |= 0x04;
        
            SPI_master_rx(&s_retval);
            if(s_retval != SUCCESS)
                motors |= 0x20;
            else {
                flag |= 0x10;
                flag += 4;
            }
        }

        if(data & Y_F) {
            PORTC &= 0xFE;
            SPI_master_tx(START);
            if(data & (Y_B ^ Y_F))
                SPI_master_tx(BACKWARD);
            else
                SPI_master_tx(FORWARD);
            SPI_master_tx(FETCH);
            PORTC |= 0x01;

            SPI_master_rx(&s_retval);
            if(s_retval != SUCCESS)
                motors |= 0x40;
            else {
                flag |= 0x20;
                flag += 4;
            }
        }

        if(data & Z_F) {
            PORTC &= 0xFD;
            SPI_master_tx(START);
            if(data & (Z_B ^ Z_F))
                SPI_master_tx(BACKWARD);
            else
                SPI_master_tx(FORWARD);
            SPI_master_tx(FETCH);
            PORTC |= 0x02;
        
            SPI_master_rx(&s_retval);
            if(s_retval != SUCCESS)
                motors |= 0x80;
            else {
                flag |= 0x40;
                flag += 4;
            }
        }
        
        if(motors) {
            // Reset the state to scanning start word
            flag = 0x00;
            USART_tx(FAILURE | motors);
        }
        else {
            USART_tx(SUCCESS);
        }
    }
    else if(flag & 0x10) {
        PORTB &= 0xFB;
        SPI_master_tx(data);
        PORTB |= 0x04;
        flag--;
        if((flag & 0x03) == 0x00){
            flag &= 0xEF;
            USART_tx(SUCCESS);
        }
        if(flag == 0x80) {
            flag = 0x00;
            USART_tx(STOP);
        }
    }
    else if(flag & 0x20) {
        PORTC &= 0xFE;
        SPI_master_tx(data);
        PORTC |= 0x01;
        flag--;
        if((flag & 0x03) == 0x00) {
            flag &= 0xDF;
            USART_tx(SUCCESS);
        }
        if(flag == 0x80) {
            flag = 0x00;
            USART_tx(STOP);
        }

    }
    else if(flag & 0x40) {
        PORTC &= 0xFD;
        SPI_master_tx(data);
        PORTC |= 0x02;
        flag--;
        if((flag & 0x03) == 0x00) {
            flag &= 0xBF;
            USART_tx(SUCCESS);
        }
        if(flag == 0x80) {
            flag = 0x00;
            USART_tx(STOP);
        }
    }
    else if(data == START) {
        flag = 0x80;
    }
}

// May not be used at all
ISR(USART_TX_vect) {
}
ISR(SPI_STC_vect) {
}
