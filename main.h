#ifndef MAIN_H
#define MAIN_H

#define DASHBOARD               0
#define PASSWORD_SCREEN                1
#define MENU_SCREEN                   2
#define DISPLAY_MENU               3
#define VIEW_LOG                 4
#define DOWNLOAD_LOG             5
#define CLEAR_LOG                6
#define SET_TIME                 7
#define CHANGE_PASSWORD             8

#include "string.h"

void display_dashboard();
void store_event();
void password_screen();
void menu_screen();
void view_log();
void download_log();
void clear_log();
void set_time();
void change_password();
void read_log();
void store_event(char []);
void get_speed();
void update_time();

/* Functions declarations and global variable declarations */
unsigned short int speed = 0;
char log[10][15];
char log_index = 0;
unsigned int address = 0x10;
char event[3];

unsigned char key, screen_flag = DASHBOARD, menu_flag = DISPLAY_MENU;
unsigned char update_event_flag = 0;

#endif


// for clcd 
#ifndef LCD_H
#define LCD_H



#define CLCD_PORT			PORTD
#define CLCD_EN				RC2
#define CLCD_RS				RC1
#define CLCD_RW				RC0
#define CLCD_BUSY			RD7
#define PORT_DIR			TRISD7


#define HI												1
#define LO												0

#define INPUT											0xFF
#define OUTPUT											0x00

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0
#define _XTAL_FREQ                  20000000
#define LINE1(x)									(0x80 + (x))
#define LINE2(x)										(0xC0 + (x))

#define TWO_LINE_5x8_MATRIX_8_BIT					clcd_write(0x38, INSTRUCTION_COMMAND)
#define CLEAR_DISP_SCREEN				                clcd_write(0x01, INSTRUCTION_COMMAND)
#define CURSOR_HOME							clcd_write(0x02, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_OFF						clcd_write(0x0C, INSTRUCTION_COMMAND)
#define EIGHT_BIT_MODE   0x33
void init_clcd(void);
void clcd_print(const unsigned char *data, unsigned char addr);
void clcd_putch(const unsigned char data, unsigned char addr);
void clcd_write(unsigned char bit_values, unsigned char control_bit);

#endif

//for matrix keypad

#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H


	
#define MAX_ROW				4
#define MAX_COL				3

#define STATE_CHANGE				1
#define LEVEL_CHANGE				0
#define MATRIX_KEYPAD_PORT			PORTB
#define ROW3					PORTBbits.RB7
#define ROW2					PORTBbits.RB6
#define ROW1					PORTBbits.RB5
#define COL4					PORTBbits.RB4
#define COL3					PORTBbits.RB3
#define COL2					PORTBbits.RB2
#define COL1					PORTBbits.RB1


#define MK_SW1					1
#define MK_SW2					2
#define MK_SW3					3
#define MK_SW4					4
#define MK_SW5					5
#define MK_SW6					6
#define MK_SW7					7
#define MK_SW8					8
#define MK_SW9					9
#define MK_SW10				10
#define MK_SW11				11
#define MK_SW12				12

#define MK_SW5_LONG          13
#define MK_SW6_LONG         14

#define ALL_RELEASED	0xFF

#define HI				1
#define LO				0

void init_matrix_keypad(void);
unsigned char scan_key(void);
unsigned char read_switches(unsigned char detection_type);

#endif

//timer 0

#ifndef TIMER0_H
#define TIMER0_H

void init_timer0(void);

#endif

//adc
#ifndef ADC_H
#define ADC_H

#define CHANNEL0		0x00
#define CHANNEL1		0x01
#define CHANNEL2		0x02
#define CHANNEL3		0x03
#define CHANNEL4		0x04
#define CHANNEL5		0x05
#define CHANNEL6		0x06
#define CHANNEL7		0x07
#define CHANNEL8		0x08
#define CHANNEL9		0x09
#define CHANNEL10		0x0A

void init_adc(void);
unsigned short read_adc(unsigned char channel);

#endif

//eeprom
//#ifndef EEPROM_H
//#define EEPROM_H
//
//void write_internal_eeprom(unsigned char address, unsigned char data); 
//unsigned char read_internal_eeprom(unsigned char address);
//
//#endif

//rtc
#ifndef Ds1307_H
#define Ds1307_H

#define SLAVE_READ		0xD1
#define SLAVE_WRITE		0xD0


#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07


void write_ds1307(unsigned char address1,  unsigned char data);
unsigned char read_ds1307(unsigned char address1);
void init_ds1307(void);


void get_time(void);

//global variable for time


#endif

//i2c
#ifndef I2C_H
#define I2C_H


void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);

#endif

//uart
#ifndef SCI_H
#define SCI_H

#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

void init_uart(void);
void putch(unsigned char byte);
int puts(const char *s);
unsigned char getch(void);
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);

#endif

//ext eeprom
#ifndef EXTERNAL_EEPROM_H
#define EXTERNAL_EEPRO_H

#define SLAVE_READ_EXEEP		0xA1
#define SLAVE_WRITE_EXEEP		0xA0


void write_external_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);

#endif

