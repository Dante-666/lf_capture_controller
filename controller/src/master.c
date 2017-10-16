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

#define F_CPU 20000000UL

#include <avr/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/power.h>

#define FORWARD     5
#define BACKWARD    7
#define MOTORFREE   11

#define START       13
#define LOAD        17
#define SUCCESS     19
#define FAILURE     23
#define STOP        29

#define X_F         0x01
#define Y_F         0x04
#define Z_F         0x10
#define X_B         0x03
#define Y_B         0x0C
#define Z_B         0x30

register uint8_t flag asm("r2");
register uint8_t slave_flag asm("r3");

uint8_t moveit = 0x00;
uint8_t direction = 0x00;
uint8_t frequency = 0x00;
uint8_t motorl0 = 0x00;
uint8_t motorl1 = 0x00;
uint8_t motorh = 0x00;

void USART_init(void) {
    // Clock freq. is 20 Mhz
    // Baud rate is 20/16(1+4) Mbps = 250 kbps * 2 for double speed
    // UBRR = 0x004;
    UBRR0L = 0x04;
    UCSR0A = 1<<U2X0;
    // Enable both the transmitter and reciever interrupts and set 8 bits
    UCSR0B = 1<<RXCIE0 | 1<<RXEN0 | 1<<TXEN0;
    // Set parity bit on with even parity, put 2 stop bits for tx.
    UCSR0C =  1<<UPM01 | 1<<USBS0 | 1<<UCSZ01 | 1<<UCSZ00;
}

void USART_tx(uint8_t data) {
    UDR0 = data;
}

void USART_rx(uint8_t* data) {
    *data = UDR0;
}

void SPI_master_init(void) {
    DDRB = 1<<DDB5 | 1<<DDB3 | 1 << DDB2; 
    SPCR = 1<<SPIE | 1<<SPE | 1<<MSTR | 1<<SPR0;
}

void SPI_master_tx(uint8_t data) {
    SPDR = data;
}

void SPI_master_rx(uint8_t* data) {
    *data = SPDR;
}

void blink_led() {
    PORTD |= 1<<PORTD2;
    _delay_ms(1);
    PORTD &= ~(1<<PORTD2);
}

void pass_motion(void) {

    slave_flag = 0xC0;
    slave_flag += 5;

    SPI_master_tx(0x00);
}

void start_all(void) {
    
    slave_flag = 0x40;

    SPI_master_tx(0x00);
}

void stop_all(void) {

    SPI_master_tx(0x00);
}

int main(void) {
    cli();
    USART_init();
    SPI_master_init();

    flag = 0x00;
    slave_flag = 0x00;
    
    //TODO: Set output status LEDs that light up showing the status

    // Set all unused pins to input which are pulled-up
    // Set this to be a slave selector port
    // At most 3 slaves will be used for 3DOF camera mover.
    DDRC |= 1<<DDC1 | 1<<DDC0;
    PORTC |= 1<<PORTC6 | 1<<PORTC5 | 1<<PORTC4 |
             1<<PORTC3 | 1<<PORTC2 | 1<<PORTC1 | 1<<PORTC0;

    // This is for the Slave_X port, this is required to be
    // present at all times and DDC0 and DDC1 correspond to
    // Slave_Y and Slave_Z respectively
    // Data direction has already been set in SPI_master_init()
    PORTB |= 1<<PORTB7 | 1<<PORTB6 | 1<<PORTB4 |
             1<<PORTB2 | 1<<PORTB1 | 1 <<PORTB0;

    // Data direction presumable set duing USART initialization
    // TODO: Remove after debugging
    DDRD |= 1<<DDD2;
    PORTD |= 1<<PORTD7 | 1<<PORTD6 | 1<<PORTD5 | 1<<PORTD4 | 
             1<<PORTD3;// | 1<<PORTD2;
    PORTD &= ~(1<<PORTD2);
  
    // TODO: Temperature control can be done
    // by speed controlling a fan using any
    // of the unused timers

    // Disable modules that are not being used
    wdt_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();
    power_twi_disable();
    power_adc_disable();

    sei();
    
    while(1) {}
}

ISR(USART_RX_vect) {
    uint8_t data;
    USART_rx(&data);

    if(flag & 0x80) {
        if((flag & 0x0F) == 5) {
            moveit = data;
            flag--;
        } else if((flag & 0x0F) == 4) {
            frequency = data;
            flag--;
        } else if((flag & 0x0F) == 3) {
            motorl0 = data;
            flag--;
        } else if((flag & 0x0F) == 2) {
            motorl1 = data;
            flag--;
        } else if((flag & 0x0F) == 1) {
            motorh = data;
            flag = 0x00;
            pass_motion();
        }
    }
    else if(data == STOP) stop_all();
    else if(data == START) start_all();
    else if(data == LOAD) {
        blink_led();
        flag = 0x80;
        flag += 0x05;
    }
}

ISR(SPI_STC_vect) {

    uint8_t s_retval;

    blink_led();
    
    if(slave_flag & 0x80) {

        if(slave_flag & 0x40) {
            if(moveit == X_F) {
                PORTB &= ~(1<<PORTB2);
                if(moveit & (X_F ^ X_B)) direction = BACKWARD;
                else direction = FORWARD;
            
            } else if(moveit == Y_F) {
                PORTB &= ~(1<<PORTC0);
                if(moveit & (Y_F ^ Y_B)) direction = BACKWARD;
                else direction = FORWARD;
            
            } else if(moveit == Z_F) {
                PORTB &= ~(1<<PORTC1);
                if(moveit & (Z_F ^ Z_B)) direction = BACKWARD;
                else direction = FORWARD;
            }

            SPI_master_tx(LOAD);
            slave_flag &= 0xBF;
            reti();
        }

        if((slave_flag & 0x0F) == 5) {
            SPI_master_tx(direction);
            slave_flag--;
        } else if((slave_flag & 0x0F) == 4) {
            SPI_master_tx(frequency);
            slave_flag--;
        } else if((slave_flag & 0x0F) == 3) {
            SPI_master_tx(motorl0);
            slave_flag--;
        } else if((slave_flag & 0x0F) == 2) {
            SPI_master_tx(motorl1);
            slave_flag--;
        } else if((slave_flag & 0x0F) == 1) {
            SPI_master_tx(motorh);
            slave_flag = 0x00;
            
            SPI_master_rx(&s_retval);
            if(s_retval == SUCCESS)
                USART_tx(SUCCESS);
            else
                USART_tx(FAILURE);
        
        }
    } else if(slave_flag & 0x40) {
        SPI_master_tx(START);
        flag = 0x00;
        
    } else if(slave_flag & 0x20) {
        SPI_master_tx(STOP);
        flag = 0x00;

    }

}
