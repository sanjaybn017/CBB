/*
 * File:   
 * Author: <NAME>
 *
 */



#include <xc.h>
#include "main.h"

//extern unsigned char screen_flag;
//extern unsigned char menu_flag;
int index = 0;


unsigned char clock_reg[3];
unsigned char time[9];

void get_time(void)
        {
        	clock_reg[0] = read_ds1307(HOUR_ADDR);
        	clock_reg[1] = read_ds1307(MIN_ADDR);
        	clock_reg[2] = read_ds1307(SEC_ADDR);

        	if (clock_reg[0] & 0x40)
        	{
        		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
            	time[1] = '0' + (clock_reg[0] & 0x0F);
            }
            else
            {
                time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
                time[1] = '0' + (clock_reg[0] & 0x0F);
            }
            time[2] = ':';
            time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
            time[4] = '0' + (clock_reg[1] & 0x0F);
            time[5] = ':';
            time[6] = '0' + ((clock_reg[2] >> 4) & 0x07);
            time[7] = '0' + (clock_reg[2] & 0x0F);
            time[8] = '\0';
            
        }

unsigned short adc_reg_val;

void get_speed()
{
    adc_reg_val = read_adc(CHANNEL4)/10.33;
        
        if( index == 0 || index == 1 )
        {
            speed = 0;
        }
        else if( index != 7 )
        {
            speed = adc_reg_val / ((float)5/(index-1));
        }
}

void display_dashboard()
{
    //logic for display_dashboard
    
    unsigned short vtg;
    
    char key;
    char temp;
    
    char *gear[8] = {"ON","GN","GR","G1","G2","G3","G4","C "};
    
    
    
    CLEAR_DISP_SCREEN;

    while (1)
    {
        menu_flag = DISPLAY_MENU;
        //get time from rtc
        get_time();
         
        get_speed();
        
        key = read_switches(STATE_CHANGE);
        clcd_print(" Time    EV   SP",LINE1(0));
        
        if( key == MK_SW2  && index > 1 )
        {
            update_event_flag = 0;
            index--;
            store_event(gear[index]);
        }
        else if( key == MK_SW3 && index < 6 )
        {
            update_event_flag = 0;
            index++;
            store_event(gear[index]);
        }
        else if( key == MK_SW1)
        {
            update_event_flag = 0;
            //collision detected
            index = 7;
            store_event(gear[index]);
        }
        else if( key == MK_SW5 )
        {
            screen_flag = PASSWORD_SCREEN;
            return;
        }
        
        clcd_print(time,LINE2(0));
        
        if( update_event_flag == 0 )
        {
            clcd_print(gear[index],LINE2(9));
        }
        else
        {
            clcd_print(event,LINE2(9));
        }
        
        clcd_putch((speed/10)%10+'0',LINE2(14));
        clcd_putch(speed%10+'0',LINE2(15));
   
    }
}