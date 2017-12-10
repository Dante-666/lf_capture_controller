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

#define F_CPU       20000000UL
#define SPI_DELAY   2U
#define H_FUSE      0xD1
#define L_FUSE      0xE7

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <util/delay.h>

#define FORWARD     5
#define BACKWARD    7

#define START       13
#define LOAD        17
#define SUCCESS     19
#define FAILURE     23
#define STOP        29

#define X_F         0x01
#define Y_F         0x04
#define Z_F         0x10
#define X_B         0x02
#define Y_B         0x08
#define Z_B         0x20

// Writing these in reverse order ensures that
// the lowest frequency is stored in the lowest
// address
// TODO: gain finer control over frequency
// since most of the high bits are low,
// we can store 512 frequencies and use lookup
// to obtain the high freq. bit
uint32_t EEMEM F256 = 214748;
uint32_t EEMEM F255 = 213948;
uint32_t EEMEM F254 = 213148;
uint32_t EEMEM F253 = 212348;
uint32_t EEMEM F252 = 211548;
uint32_t EEMEM F251 = 210748;
uint32_t EEMEM F250 = 209948;
uint32_t EEMEM F249 = 209148;
uint32_t EEMEM F248 = 208348;
uint32_t EEMEM F247 = 207548;
uint32_t EEMEM F246 = 206748;
uint32_t EEMEM F245 = 205948;
uint32_t EEMEM F244 = 205148;
uint32_t EEMEM F243 = 204348;
uint32_t EEMEM F242 = 203548;
uint32_t EEMEM F241 = 202748;
uint32_t EEMEM F240 = 201948;
uint32_t EEMEM F239 = 201148;
uint32_t EEMEM F238 = 200348;
uint32_t EEMEM F237 = 199548;
uint32_t EEMEM F236 = 198748;
uint32_t EEMEM F235 = 197947;
uint32_t EEMEM F234 = 197147;
uint32_t EEMEM F233 = 196347;
uint32_t EEMEM F232 = 195547;
uint32_t EEMEM F231 = 194747;
uint32_t EEMEM F230 = 193947;
uint32_t EEMEM F229 = 193147;
uint32_t EEMEM F228 = 192347;
uint32_t EEMEM F227 = 191547;
uint32_t EEMEM F226 = 190747;
uint32_t EEMEM F225 = 189947;
uint32_t EEMEM F224 = 189147;
uint32_t EEMEM F223 = 188347;
uint32_t EEMEM F222 = 187547;
uint32_t EEMEM F221 = 186747;
uint32_t EEMEM F220 = 185947;
uint32_t EEMEM F219 = 185147;
uint32_t EEMEM F218 = 184347;
uint32_t EEMEM F217 = 183547;
uint32_t EEMEM F216 = 182747;
uint32_t EEMEM F215 = 181947;
uint32_t EEMEM F214 = 181147;
uint32_t EEMEM F213 = 180347;
uint32_t EEMEM F212 = 179546;
uint32_t EEMEM F211 = 178746;
uint32_t EEMEM F210 = 177946;
uint32_t EEMEM F209 = 177146;
uint32_t EEMEM F208 = 176346;
uint32_t EEMEM F207 = 175546;
uint32_t EEMEM F206 = 174746;
uint32_t EEMEM F205 = 173946;
uint32_t EEMEM F204 = 173146;
uint32_t EEMEM F203 = 172346;
uint32_t EEMEM F202 = 171546;
uint32_t EEMEM F201 = 170746;
uint32_t EEMEM F200 = 169946;
uint32_t EEMEM F199 = 169146;
uint32_t EEMEM F198 = 168346;
uint32_t EEMEM F197 = 167546;
uint32_t EEMEM F196 = 166746;
uint32_t EEMEM F195 = 165946;
uint32_t EEMEM F194 = 165146;
uint32_t EEMEM F193 = 164346;
uint32_t EEMEM F192 = 163546;
uint32_t EEMEM F191 = 162746;
uint32_t EEMEM F190 = 161946;
uint32_t EEMEM F189 = 161145;
uint32_t EEMEM F188 = 160345;
uint32_t EEMEM F187 = 159545;
uint32_t EEMEM F186 = 158745;
uint32_t EEMEM F185 = 157945;
uint32_t EEMEM F184 = 157145;
uint32_t EEMEM F183 = 156345;
uint32_t EEMEM F182 = 155545;
uint32_t EEMEM F181 = 154745;
uint32_t EEMEM F180 = 153945;
uint32_t EEMEM F179 = 153145;
uint32_t EEMEM F178 = 152345;
uint32_t EEMEM F177 = 151545;
uint32_t EEMEM F176 = 150745;
uint32_t EEMEM F175 = 149945;
uint32_t EEMEM F174 = 149145;
uint32_t EEMEM F173 = 148345;
uint32_t EEMEM F172 = 147545;
uint32_t EEMEM F171 = 146745;
uint32_t EEMEM F170 = 145945;
uint32_t EEMEM F169 = 145145;
uint32_t EEMEM F168 = 144345;
uint32_t EEMEM F167 = 143545;
uint32_t EEMEM F166 = 142745;
uint32_t EEMEM F165 = 141944;
uint32_t EEMEM F164 = 141144;
uint32_t EEMEM F163 = 140344;
uint32_t EEMEM F162 = 139544;
uint32_t EEMEM F161 = 138744;
uint32_t EEMEM F160 = 137944;
uint32_t EEMEM F159 = 137144;
uint32_t EEMEM F158 = 136344;
uint32_t EEMEM F157 = 135544;
uint32_t EEMEM F156 = 134744;
uint32_t EEMEM F155 = 133944;
uint32_t EEMEM F154 = 133144;
uint32_t EEMEM F153 = 132344;
uint32_t EEMEM F152 = 131544;
uint32_t EEMEM F151 = 130744;
uint32_t EEMEM F150 = 129944;
uint32_t EEMEM F149 = 129144;
uint32_t EEMEM F148 = 128344;
uint32_t EEMEM F147 = 127544;
uint32_t EEMEM F146 = 126744;
uint32_t EEMEM F145 = 125944;
uint32_t EEMEM F144 = 125144;
uint32_t EEMEM F143 = 124344;
uint32_t EEMEM F142 = 123543;
uint32_t EEMEM F141 = 122743;
uint32_t EEMEM F140 = 121943;
uint32_t EEMEM F139 = 121143;
uint32_t EEMEM F138 = 120343;
uint32_t EEMEM F137 = 119543;
uint32_t EEMEM F136 = 118743;
uint32_t EEMEM F135 = 117943;
uint32_t EEMEM F134 = 117143;
uint32_t EEMEM F133 = 116343;
uint32_t EEMEM F132 = 115543;
uint32_t EEMEM F131 = 114743;
uint32_t EEMEM F130 = 113943;
uint32_t EEMEM F129 = 113143;
uint32_t EEMEM F128 = 112343;
uint32_t EEMEM F127 = 111543;
uint32_t EEMEM F126 = 110743;
uint32_t EEMEM F125 = 109943;
uint32_t EEMEM F124 = 109143;
uint32_t EEMEM F123 = 108343;
uint32_t EEMEM F122 = 107543;
uint32_t EEMEM F121 = 106743;
uint32_t EEMEM F120 = 105943;
uint32_t EEMEM F119 = 105142;
uint32_t EEMEM F118 = 104342;
uint32_t EEMEM F117 = 103542;
uint32_t EEMEM F116 = 102742;
uint32_t EEMEM F115 = 101942;
uint32_t EEMEM F114 = 101142;
uint32_t EEMEM F113 = 100342;
uint32_t EEMEM F112 = 99542;
uint32_t EEMEM F111 = 98742;
uint32_t EEMEM F110 = 97942;
uint32_t EEMEM F109 = 97142;
uint32_t EEMEM F108 = 96342;
uint32_t EEMEM F107 = 95542;
uint32_t EEMEM F106 = 94742;
uint32_t EEMEM F105 = 93942;
uint32_t EEMEM F104 = 93142;
uint32_t EEMEM F103 = 92342;
uint32_t EEMEM F102 = 91542;
uint32_t EEMEM F101 = 90742;
uint32_t EEMEM F100 = 89942;
uint32_t EEMEM F99 = 89142;
uint32_t EEMEM F98 = 88342;
uint32_t EEMEM F97 = 87542;
uint32_t EEMEM F96 = 86741;
uint32_t EEMEM F95 = 85941;
uint32_t EEMEM F94 = 85141;
uint32_t EEMEM F93 = 84341;
uint32_t EEMEM F92 = 83541;
uint32_t EEMEM F91 = 82741;
uint32_t EEMEM F90 = 81941;
uint32_t EEMEM F89 = 81141;
uint32_t EEMEM F88 = 80341;
uint32_t EEMEM F87 = 79541;
uint32_t EEMEM F86 = 78741;
uint32_t EEMEM F85 = 77941;
uint32_t EEMEM F84 = 77141;
uint32_t EEMEM F83 = 76341;
uint32_t EEMEM F82 = 75541;
uint32_t EEMEM F81 = 74741;
uint32_t EEMEM F80 = 73941;
uint32_t EEMEM F79 = 73141;
uint32_t EEMEM F78 = 72341;
uint32_t EEMEM F77 = 71541;
uint32_t EEMEM F76 = 70741;
uint32_t EEMEM F75 = 69941;
uint32_t EEMEM F74 = 69141;
uint32_t EEMEM F73 = 68341;
uint32_t EEMEM F72 = 67540;
uint32_t EEMEM F71 = 66740;
uint32_t EEMEM F70 = 65940;
uint32_t EEMEM F69 = 65140;
uint32_t EEMEM F68 = 64340;
uint32_t EEMEM F67 = 63540;
uint32_t EEMEM F66 = 62740;
uint32_t EEMEM F65 = 61940;
uint32_t EEMEM F64 = 61140;
uint32_t EEMEM F63 = 60340;
uint32_t EEMEM F62 = 59540;
uint32_t EEMEM F61 = 58740;
uint32_t EEMEM F60 = 57940;
uint32_t EEMEM F59 = 57140;
uint32_t EEMEM F58 = 56340;
uint32_t EEMEM F57 = 55540;
uint32_t EEMEM F56 = 54740;
uint32_t EEMEM F55 = 53940;
uint32_t EEMEM F54 = 53140;
uint32_t EEMEM F53 = 52340;
uint32_t EEMEM F52 = 51540;
uint32_t EEMEM F51 = 50740;
uint32_t EEMEM F50 = 49940;
uint32_t EEMEM F49 = 49139;
uint32_t EEMEM F48 = 48339;
uint32_t EEMEM F47 = 47539;
uint32_t EEMEM F46 = 46739;
uint32_t EEMEM F45 = 45939;
uint32_t EEMEM F44 = 45139;
uint32_t EEMEM F43 = 44339;
uint32_t EEMEM F42 = 43539;
uint32_t EEMEM F41 = 42739;
uint32_t EEMEM F40 = 41939;
uint32_t EEMEM F39 = 41139;
uint32_t EEMEM F38 = 40339;
uint32_t EEMEM F37 = 39539;
uint32_t EEMEM F36 = 38739;
uint32_t EEMEM F35 = 37939;
uint32_t EEMEM F34 = 37139;
uint32_t EEMEM F33 = 36339;
uint32_t EEMEM F32 = 35539;
uint32_t EEMEM F31 = 34739;
uint32_t EEMEM F30 = 33939;
uint32_t EEMEM F29 = 33139;
uint32_t EEMEM F28 = 32339;
uint32_t EEMEM F27 = 31539;
uint32_t EEMEM F26 = 30738;
uint32_t EEMEM F25 = 29938;
uint32_t EEMEM F24 = 29138;
uint32_t EEMEM F23 = 28338;
uint32_t EEMEM F22 = 27538;
uint32_t EEMEM F21 = 26738;
uint32_t EEMEM F20 = 25938;
uint32_t EEMEM F19 = 25138;
uint32_t EEMEM F18 = 24338;
uint32_t EEMEM F17 = 23538;
uint32_t EEMEM F16 = 22738;
uint32_t EEMEM F15 = 21938;
uint32_t EEMEM F14 = 21138;
uint32_t EEMEM F13 = 20338;
uint32_t EEMEM F12 = 19538;
uint32_t EEMEM F11 = 18738;
uint32_t EEMEM F10 = 17938;
uint32_t EEMEM F9 = 17138;
uint32_t EEMEM F8 = 16338;
uint32_t EEMEM F7 = 15538;
uint32_t EEMEM F6 = 14738;
uint32_t EEMEM F5 = 13938;
uint32_t EEMEM F4 = 13138;
uint32_t EEMEM F3 = 12338;
uint32_t EEMEM F2 = 11537;
uint32_t EEMEM F1 = 10737;

register uint8_t flag asm("r2");
register uint8_t es_flag asm("r3");

register uint8_t countl0_x asm("r4");
register uint8_t countl0_y asm("r5");
register uint8_t countl0_z asm("r6");
register uint8_t buff_count asm("r7");

const uint16_t control_start = 0x2068;
const uint16_t control_stop = 0x2148;

uint8_t moveit = 0x00;
uint8_t freq_x = 0x0000;
uint8_t freq_y = 0x0000;
uint8_t freq_z = 0x0000;

uint16_t freql = 0x0000;
uint16_t freqh = 0x0000;

uint8_t countl1_x = 0x00;
uint8_t counth_x = 0x00;
uint8_t countl1_y = 0x00;
uint8_t counth_y = 0x00;
uint8_t countl1_z = 0x00;
uint8_t counth_z = 0x00;
uint8_t temp = 0x00;

// If something is wrong with the sync, check if the baud rates are
// same for the devices
void USART_init(void) {
    // Clock freq. is 20 Mhz
    // Baud rate is 20/16(1+520) Mbps = 2400 * 2 bps
    UBRR0 = 0x208;
    UCSR0A |= 1<<U2X0;
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
    DDRB = 1<<DDB5 | 1<<DDB3 | 1<<DDB2;
    // SCK is at 5MHz, TCK = 0.2us, and SPI_DELAY
    // can be easily set to 2 us considering it takes
    // 8 clock cycles to transmit 1 byte with extra 2 cycles
    SPCR = 1<<SPE | 1<<MSTR | 1<<CPOL;
}

void SPI_master_tx(uint8_t data) {
    SPDR = data;
}

void TIMER_init(void) {
    TCCR1B |= 1<<CS12 | 1<<CS10;
    OCR1A = 4882;
    TCCR1B |= 1<<WGM12;
}

void TIMER_enable(void) {
    TIMSK1 |= 1<<OCIE1A; 
}

void TIMER_disable(void) {
    TIMSK1 &= ~(1<<OCIE1A);
}

void ENDSTOP_enable(void) {
    EIMSK = 1<<INT1 | 1<<INT0;
}

void ENDSTOP_init(void) {
    EICRA = 0x00;
    ENDSTOP_enable();
}

void ENDSTOP_disable(void) {
    EIMSK &= ~(1<<INT1 | 1<<INT0);
}

void PCINT_init(void) {
    PCICR = 1<<PCIE2 | 1<< PCIE1 | 1<<PCIE0;
}

void PCINT_enable_x(void) {
    PCMSK0 = 1<<PCINT1;
}
void PCINT_enable_y(void) {
    PCMSK1 = 1<<PCINT10;
}
void PCINT_enable_z(void) {
    PCMSK2 = 1<<PCINT20;
}

void PCINT_enable_all(void) {
    if(moveit & (X_F | X_B))
        PCMSK0 = 1<<PCINT1;
    if(moveit & (Y_F | Y_B))
        PCMSK1 = 1<<PCINT10;
    if(moveit & (Z_F | Z_B))
        PCMSK2 = 1<<PCINT20;
}

void PCINT_disable_x(void) {
    PCMSK0 = 0x00;
}
void PCINT_disable_y(void) {
    PCMSK1 = 0x00;
}
void PCINT_disable_z(void) {
    PCMSK2 = 0x00;
}

void PCINT_disable_all(void) {
    PCMSK0 = 0x00;
    PCMSK1 = 0x00;
    PCMSK2 = 0x00;
}

// This updates the AD9833 in realtime
// It is user's responsibility to make sure that realtime
// update is intended, as in the case of speed control
// applications
void update_freq(uint8_t data) {
    
    uint16_t offset = data * 4;
    uint32_t freq = eeprom_read_dword((const uint32_t *) offset);

    freql = freq & 0x3FFF;
    freqh = freq >> 14;

    freql |= 0x4000;
    freqh |= 0x4000;
}

void update_freq_x(void) {
    update_freq(freq_x);
    uint8_t s_data;
    
    PORTB &= ~(1<<PORTB2);
    
    s_data = freql>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = freql & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = freqh>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = freqh & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);

    PORTB |= 1<<PORTB2;
}
void update_freq_y(void) {
    update_freq(freq_y);
    uint8_t s_data;

    PORTC &= ~(1<<PORTC0);

    s_data = freql>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = freql & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = freqh>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = freqh & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    
    PORTC |= 1<<PORTC0;
}
void update_freq_z(void) {
    update_freq(freq_z);    
    uint8_t s_data;

    PORTC &= ~(1<<PORTC1);

    s_data = freql>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = freql & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = freqh>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = freqh & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    
    PORTC |= 1<<PORTC1;
}

void load_freq(void) {

    if(moveit & (X_B | X_F))
        update_freq_x();
    if(moveit & (Y_B | Y_F))
        update_freq_y();
    if(moveit & (Z_B | Z_F))
        update_freq_z();
}

void set_direction(void) {
    
    if(moveit & X_B)
        PORTC |= 1<<PORTC3;
    else
        PORTC &= ~(1<<PORTC3);
    
    if(moveit & Y_B)
        PORTC |= 1<<PORTC4;
    else
        PORTC &= ~(1<<PORTC4);
    
    if(moveit & Z_B)
        PORTC |= 1<<PORTC5;
    else
        PORTC &= ~(1<<PORTC5);

}

void start_motor_x(void) {

    if(counth_x == 0 && countl1_x == 0 && countl0_x == 0)
        return;

    PCINT_enable_x();
    uint8_t s_data;
    
    PORTB &= ~(1<<PORTB2);
    
    s_data = control_start>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = control_start & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);

    PORTB |= 1<<PORTB2;
}

void start_motor_y(void) {

    if(counth_y == 0 && countl1_y == 0 && countl0_y == 0)
        return;

    PCINT_enable_y();
    uint8_t s_data;
    
    PORTC &= ~(1<<PORTC0);
    
    s_data = control_start>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = control_start & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);

    PORTC |= 1<<PORTC0;
}

void start_motor_z(void) {

    if(counth_z == 0 && countl1_z == 0 && countl0_z == 0)
        return;

    PCINT_enable_z();
    uint8_t s_data;
    
    PORTC &= ~(1<<PORTC1);
    
    s_data = control_start>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = control_start & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);

    PORTC |= 1<<PORTC1;
}

void start_motors(void) {
    
    if(moveit & (X_F | X_B)) {
        start_motor_x();
    }
    if(moveit & (Y_F | Y_B)) {
        start_motor_y();
    }
    if(moveit & (Z_F | Z_B)) {
        start_motor_z();
    }

}

void stop_motor_x(void) {
    
    PCINT_disable_x();
    uint8_t s_data;
    
    PORTB &= ~(1<<PORTB2);
    
    s_data = control_stop>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = control_stop & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);

    PORTB |= 1<<PORTB2;

}

void stop_motor_y(void) {
    
    PCINT_disable_y();
    uint8_t s_data;
    
    PORTC &= ~(1<<PORTC0);
    
    s_data = control_stop>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = control_stop & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);

    PORTC |= 1<<PORTC0;

}

void stop_motor_z(void) {
   
    PCINT_disable_z();
    uint8_t s_data;
    
    PORTC &= ~(1<<PORTC1);
    
    s_data = control_stop>>8 & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);
    s_data = control_stop & 0xFF;
    SPI_master_tx(s_data);
    _delay_us(SPI_DELAY);

    PORTC |= 1<<PORTC1;
}

void stop_motors(void) {
    stop_motor_x();
    stop_motor_y();
    stop_motor_z();
}

int main(void) {

    cli();
    USART_init();
    SPI_master_init();
    PCINT_init();
    TIMER_init();
    ENDSTOP_init();

    // Disable modules that are not being used
    wdt_disable();
    power_timer0_disable();
    power_timer2_disable();
    power_twi_disable();
    power_adc_disable();
   
    // PORTB :
    // 0 -> STATUS_LED
    // 1 <- PCINT0 INT FG_X OUT
    // 2 -> FG_X FSYNC
    // 3 -> FG_SDATA
    // 4 <- Z_AXIS ENDSTOP
    // 5 -> FG_SCK
    // 6 // XTAL1
    // 7 // XTAL2
    DDRB |= 1<<DDB0;
    PORTB |= 1<<PORTB4 | 1<<PORTB1 | 1<<PORTB0;
    
    
    // PORTC : 
    // 0 -> FG_Y FSYNC
    // 1 -> FG_Z FSYNC
    // 2 <- PCINT1 INT FG_Y OUT
    // 3 -> CH_X DIR
    // 4 -> CH_Y DIR
    // 5 -> CH_Z DIR
    DDRC |= 1<<DDC5 | 1<<DDC4 | 1<<DDC3 | 1<<DDC1 | 1<<DDC0;
    PORTC |= 1<<PORTC2 | 1<<PORTC1 | 1<<PORTC0;

    // PORTD :
    // 0 <- UART RXD
    // 1 -> UART TXD
    // 2 <- ENDSTOP INT0
    // 3 <- ENDSTOP INT1
    // 4 <- PCINT2 INT FG_Z OUT
    // 5 -> MUX SELECT
    // 6 <- Y_AXIS ENDSTOP
    // 7 <- X_AXIS ENDSTOP
    DDRD |= 1<<DDD5;
    PORTD |= 1<<PORTD7 | 1<<PORTD6 | 1<<PORTD4 |
             1<<PORTD3 | 1<<PORTD2;

    // Put device in reset mode with square wave output and full clock
    // Also disables the DAC to save power.
    stop_motors();
    
    sei();

    // To allocate a named location for counth_z
    temp = moveit;

    while(1) {}
}

ISR(INT0_vect, ISR_NAKED) {
    __asm__(
    "   push r24\n\t"
    "   in r24, 0x3f\n\t"
    "   push r24\n\t"
    "   cli\n\t"
    "   call 0x12e\n\t"
    "   call 0x42e\n\t"
    "   ldi r24, 0x40\n\t"
    "   mov r2, r24\n\t"
    "   cbi 0x0b, 5\n\t"
    "   sbic 0x09, 7\n\t"
    "   rjmp .+20\n\t"
    "   ldi r24, 0x01\n\t"
    "   sts 0x00C6, r24\n\t"
    "   call 0x106\n\t"
    "   sei\n\t"
    "   pop r24\n\t"
    "   out 0x3f, r24\n\t"
    "   pop r24\n\t"
    "   reti\n\t"
    "   sbic 0x09, 6\n\t"
    "   rjmp .+4\n\t"
    "   ldi r24, 0x04\n\t"
    "   rjmp .-26\n\t"
    "   ldi r24, 0x10\n\t"
    "   rjmp .-30\n\t");
}

ISR(INT1_vect, ISR_NAKED) {
    __asm__(
    "   sbi 0x0b, 5\n\t"
    "   push r24\n\t"
    "   in r24, 0x3f\n\t"
    "   push r24\n\t"
    "   cli\n\t"
    "   call 0x12e\n\t"
    "   call 0x42e\n\t"
    "   ldi r24, 0x40\n\t"
    "   mov r2, r24\n\t"
    "   sbic 0x09, 7\n\t"
    "   rjmp .+22\n\t"
    "   ldi r24, 0x02\n\t"
    "   sts 0x00C6, r24\n\t"
    "   call 0x106\n\t"
    "   cbi 0x0b, 5\n\t"
    "   sei\n\t"
    "   pop r24\n\t"
    "   out 0x3f, r24\n\t"
    "   pop r24\n\t"
    "   reti\n\t"
    "   sbic 0x09, 6\n\t"
    "   rjmp .+4\n\t"
    "   ldi r24, 0x08\n\t"
    "   rjmp .-28\n\t"
    "   ldi r24, 0x20\n\t"
    "   rjmp .-32\n\t");
}

// This routine will not work if the counter
// is initialized with 0, please make sure that the counter
// is at least one before enabling the routine
//
// Also check the calls to stop_motor_*, that may change
// as the code changes
ISR(PCINT0_vect, ISR_NAKED) {
    __asm__(
    "   sbis 0x03, 1\n\t"
    "   rjmp .+14\n\t"
    "   in r7, 0x3f\n\t"
    "   push r7\n\t"
    "   and r4, r4\n\t"
    "   breq .+8\n\t"
    "   dec r4\n\t"
    "   pop r7\n\t"
    "   out 0x3f, r7\n\t"
    "   reti\n\t"
    "   lds r7, 0x010a\n\t"
    "   and r7, r7\n\t"
    "   breq .+10\n\t"
    "   dec r7\n\t"
    "   sts 0x010a, r7\n\t"
    "   dec r4\n\t"
    "   rjmp .-24\n\t"
    "   lds r7, 0x0109\n\t"
    "   and r7, r7\n\t"
    "   breq .+16\n\t"
    "   dec r7\n\t"
    "   sts 0x0109, r7\n\t"
    "   eor r7, r7\n\t"
    "   dec r7\n\t"
    "   sts 0x010a, r7\n\t"
    "   rjmp .-48\n\t"
    "   call 0x3c8\n\t"
    "   rjmp .-54\n\t");
}

ISR(PCINT1_vect, ISR_NAKED) {
    __asm__(
    "   sbis 0x06, 2\n\t"
    "   rjmp .+14\n\t"
    "   in r7, 0x3f\n\t"
    "   push r7\n\t"
    "   and r5, r5\n\t"
    "   breq .+8\n\t"
    "   dec r5\n\t"
    "   pop r7\n\t"
    "   out 0x3f, r7\n\t"
    "   reti\n\t"
    "   lds r7, 0x0108\n\t"
    "   and r7, r7\n\t"
    "   breq .+10\n\t"
    "   dec r7\n\t"
    "   sts 0x0108, r7\n\t"
    "   dec r5\n\t"
    "   rjmp .-24\n\t"
    "   lds r7, 0x0107\n\t"
    "   and r7, r7\n\t"
    "   breq .+16\n\t"
    "   dec r7\n\t"
    "   sts 0x0107, r7\n\t"
    "   eor r7, r7\n\t"
    "   dec r7\n\t"
    "   sts 0x0108, r7\n\t"
    "   rjmp .-48\n\t"
    "   call 0x3ea\n\t"
    "   rjmp .-54\n\t");
}

ISR(PCINT2_vect, ISR_NAKED) {
    __asm__(
    "   sbis 0x09, 4\n\t"
    "   rjmp .+14\n\t"
    "   in r7, 0x3f\n\t"
    "   push r7\n\t"
    "   and r6, r6\n\t"
    "   breq .+8\n\t"
    "   dec r6\n\t"
    "   pop r7\n\t"
    "   out 0x3f, r7\n\t"
    "   reti\n\t"
    "   lds r7, 0x0106\n\t"
    "   and r7, r7\n\t"
    "   breq .+10\n\t"
    "   dec r7\n\t"
    "   sts 0x0106, r7\n\t"
    "   dec r6\n\t"
    "   rjmp .-24\n\t"
    "   lds r7, 0x0105\n\t"
    "   and r7, r7\n\t"
    "   breq .+16\n\t"
    "   dec r7\n\t"
    "   sts 0x0105, r7\n\t"
    "   eor r7, r7\n\t"
    "   dec r7\n\t"
    "   sts 0x0106, r7\n\t"
    "   rjmp .-48\n\t"
    "   call 0x40c\n\t"
    "   rjmp .-54\n\t");
}

ISR(TIMER1_COMPA_vect, ISR_NAKED) {
    __asm__(
    "   push r24\n\t"
    "   in r24, 0x3f\n\t"
    "   push r24\n\t"
    "   in r24, 0x05\n\t"
    "   sbrs r24, 0\n\t"
    "   rjmp .+4\n\t"
    "   andi r24, 0xFE\n\t"
    "   rjmp .+2\n\t"
    "   ori r24, 0x01\n\t"
    "   out 0x05, r24\n\t"
    "   pop r24\n\t"
    "   out 0x3f, r24\n\t"
    "   pop r24\n\t"
    "   reti \n\t");

}

ISR(USART_RX_vect) {
    
    uint8_t data;
    USART_rx(&data);

    if(flag & 0x40) {
        if(data == STOP) {
            ENDSTOP_enable();
            TIMER_disable();
            es_flag = 0x00;
            flag = 0x00;
            USART_tx(SUCCESS);
            PORTB |= 1<<PORTB0;
        }
    }
    else if(flag & 0x80) {
        if((flag & 0x0F) == 13) {
            moveit = data;
            flag--;
        }
        else if((flag & 0x0F) == 12) {
            freq_x = data;
            flag--;
        }
        else if((flag & 0x0F) == 11) {
            freq_y = data;
            flag--;
        }
        else if((flag & 0x0F) == 10) {
            freq_z = data;
            flag--;
        }
        else if((flag & 0x0F) == 9) {
            countl0_x = data;
            flag--;
        }
        else if((flag & 0x0F) == 8) {
            countl1_x = data;
            flag--;
        }
        else if((flag & 0x0F) == 7) {
            counth_x = data;
            flag--;
        }
        else if((flag & 0x0F) == 6) {
            countl0_y = data;
            flag--;
        }
        else if((flag & 0x0F) == 5) {
            countl1_y = data;
            flag--;
        }
        else if((flag & 0x0F) == 4) {
            counth_y = data;
            flag--;
        }
        else if((flag & 0x0F) == 3) {
            countl0_z = data;
            flag--;
        }
        else if((flag & 0x0F) == 2) {
            countl1_z = data;
            flag--;
        }
        else if((flag & 0x0F) == 1) {
            counth_z = data;
            USART_tx(SUCCESS);
            flag = 0x00;
            set_direction();
            load_freq();
        }
    }
    else if (data == STOP) {
        stop_motors();
        USART_tx(SUCCESS);
    }
    else if (data == START) {
        start_motors();
        USART_tx(SUCCESS);
    }
    else if(data == LOAD) {
        flag = 0x8D;
    }
}
