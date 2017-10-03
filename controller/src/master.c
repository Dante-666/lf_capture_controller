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

#define START       17
#define SUCCESS     19
#define STOP        23

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
    UCSR0B = 1<<RXCIE0 | 1<<RXEN0 | 1<<TXEN0 | 1<<TXCIE0 ;
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
    DDRB = 1<<DDRB4 | 1<<DDRB5 | 1 << DDRB7; 
    SPCR = 1<<SPE | 1<<MSTR | 1<<SPR0;
    sei();
}

void SPI_master_tx(uint8_t data) {
    SPDR = data;
}

void SPI_master_rx(uint8_t* data) {
    *data = SPDR;
}

int main(void) {

    //TIMER_init();
    USART_init();
    SPI_master_init();

    flag = 0x00;
    
    // Set this to be a slave selector port
    // At most 3 slaves will be used for 3DOF camera mover.
   
    // Disable functions which are not being used

    // Set all unused pins as inputs
    while(1) {}
}

ISR(TIMER1_COMPA_vect) {
}

ISR(USART_RXC_vect) {
    uint8_t data;
    USART_rx(&data);

    if(flag = 0x80) {
        // Data flow commences here
        // Set the motor directions here
        if(data & X_B) {
            PORTA = 0x00;
            SPI_master_tx(data);
            PORTA = 0x01;        
        }
        if(data & Y_B) {
        
        }
        if(data & Z_B) {
        
        }
        // Send the SUCCESS flag
        USART_tx(SUCCESS);        
    }
    else if(flag & 0x04) {
        SPI_master_tx(data);
        flag &= 0xFB;
    }
    else if(flag & 0x08) {
        SPI_master_tx(data);
        flag &= 0xF7; 
    }
    else if(flag & 0x80) {

    }
    else if(data == START) {
        flag = 0x80;
    }
}

// May not be used at all
ISR(USART_TXC_vect) {

}

// May be used to randomize the
// key_x register when all the
// data is successfully transferred
ISR(SPI_STC_vect) {
}
