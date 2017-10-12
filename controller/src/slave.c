/**
 * File              : src/slave.c
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
#include <avr/eeprom.h>
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

// Writing these in reverse order ensures that
// the lowest frequency is stored in the lowest
// address
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

void SPI_slave_init(void) {
    cli();
    DDRB = 1<<DDB4;
    SPCR = 1<<SPIE | 1 <<SPE | 1<<SPR0;
    sei();
}

void SPI_slave_tx(uint8_t data) {
    SPDR = data;
}

void SPI_slave_rx(uint8_t* data) {
    *data = SPDR;
}

void set_frequency(uint8_t data) {
    
    uint16_t offset = data * 4;
    uint32_t freq =  eeprom_read_dword((const uint32_t *)0);
    //uint32_t freq =  eeprom_read_dword((const uint32_t *)offset);
    //freq = 0;
    PORTD |= 0x01;
    PORTD &= 0xFE;
}

int main(void) {

    USARTSPI_init();
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
    uint8_t data;
    SPI_slave_rx(&data);

    if(flag == 0x80) {
        if(data == BACKWARD)
            PORTD |= 0x04;
        else if(data == FORWARD)
            PORTD &= 0xFB;
        flag = 0x10;
        flag += 5;
        SPI_slave_tx(SUCCESS);
    }
    else if (flag & 0x10) {
        // Discard this byte since this
        // was used to tranfer values from
        // the slave to master
        if ((flag & 0x0F) == 0x05) flag--;
        else if((flag & 0x0F) == 0x04) {
            set_frequency(data);
            flag--;
        }
        else if((flag & 0x0F) == 0x03) {
            flag--;
        }
        else if((flag & 0x0F) == 0x02) {
            flag--;
        }
        else if((flag & 0x0F) == 0x01) {
            flag--;
            SPI_slave_tx(STOP);
        }
        // Reset the state back
        else if((flag & 0x0F) == 0x00) {
            flag = 0x00;
        }
    }
    else if(data == START) {
        flag = 0x80;
    }
}

