/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */

char org_pswd[5];
char cur_pswd[5];
unsigned int seconds;
//extern unsigned char screen_flag;
//extern unsigned char menu_flag;
unsigned char second_flag = 0;

#include <xc.h>
#include "main.h"

void password_screen()
{
    //read original password from eeprom
    org_pswd[0] = read_external_eeprom(0x00);
	org_pswd[1] = read_external_eeprom(0x01);
	org_pswd[2] = read_external_eeprom(0x02);
	org_pswd[3] = read_external_eeprom(0x03);
    org_pswd[4] = '\0';
    
    //logic for password screen
    
    unsigned short i = 0;
    unsigned short attempt = 0;
    unsigned int delay =0;
    unsigned char flag = 0;
    unsigned int wait = 1000;
    unsigned int time = 1000;
    unsigned int block = 800;
    
    CLEAR_DISP_SCREEN;
    
	while(1)
	{
        //blink led
        if( !wait-- )
        {
            wait = time;
            RB0 = !RB0;
        }
        
        clcd_print("Enter Password  ",LINE1(0));
        if( i == 0  && flag )
        {
            flag = 0;
            clcd_print("                ",LINE2(0));
        }
        
        char key = read_switches(STATE_CHANGE);
        
        //for underscore
        if( delay++ == 500 )
        {
            clcd_putch(' ',LINE2(i));
        }
        else if( delay == 1000 )
        {
            delay = 0;
            clcd_putch('_',LINE2(i));
        }
        
        // frr printing * and reading 1 or 0 to string
        if( key == MK_SW1 )
        {
            clcd_putch('*',LINE2(i));
            cur_pswd[i++] = '0';
            
        }
        if( key == MK_SW2 )
        {
            clcd_putch('*',LINE2(i));
            cur_pswd[i++] = '1';
            
        }
        if( i == 4)
        {
            // start compare
            cur_pswd[i] = '\0';
            i = 0;
            flag = 1;
            if( strncmp(org_pswd,cur_pswd,4) == 0)
            {
                //password matched
                
                while(block--)
                {
                
                    clcd_print("Password is    ",LINE1(0));
                    clcd_print("Matched        ",LINE2(0));
                }
                screen_flag = MENU_SCREEN;
                menu_flag = DISPLAY_MENU;
                return;
            }
            else
            {
                if( attempt != 2 )
                {
                    while(block--)
                    {
                        clcd_print("Wrong Password ",LINE1(0));  // if not printing try adding delay
                        clcd_print("Attempt left",LINE2(0));
                        clcd_putch('0'+(2-attempt),LINE2(13));
                    }
                    block = 800;
                    
                    attempt++;
                    time = time - 150;
                }
                else
                {
                    seconds = 59;
                    while( seconds )
                    {
                        if( second_flag == 1 )
                        {
                            seconds -= 1;
                            second_flag = 0;
                            
                        }
                        //wait for 1 min and again give 3 attempt
                        clcd_print("Device Locked  ",LINE1(0));
                        clcd_print("Time remain  ",LINE2(0));
                        clcd_putch('0'+seconds/10,LINE2(13));
                        clcd_putch('0'+seconds%10,LINE2(14));
                    }
                    attempt = 0;
                }
            }
        }
	}
}