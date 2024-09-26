/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */



#include <xc.h>
#include "main.h"
#include <stdlib.h>

//extern unsigned char screen_flag;
//extern unsigned char menu_flag;
unsigned int temp_time[3] = {0};

extern unsigned char time[9];

void update_time()
{
    unsigned char second = (temp_time[0]%10) | (((temp_time[0]/10)%10) << 4);
    unsigned char minute = (temp_time[1]%10) | (((temp_time[1]/10)%10) << 4);
    unsigned char hour = (temp_time[2]%10) | (((temp_time[2]/10)%10) << 4);
    write_ds1307(SEC_ADDR,second);
    write_ds1307(MIN_ADDR,minute);
    write_ds1307(HOUR_ADDR,hour);
}


void set_time()
{
    //logic for set_time
    CLEAR_DISP_SCREEN;
    char key;
    char M_key;
    char temp;
    int delay = 0;
    int index = 0;
    int blink_delay = 0;
    
    //get the current time in temp_time
    get_time();
    char dummy_time[9];
    strncpy(dummy_time,time,9);
    temp_time[2] = atoi(strtok(dummy_time,":"));
    temp_time[1] = atoi(strtok(NULL,":"));
    temp_time[0] = atoi(strtok(NULL,":"));
    
    while(1)
    {
      //  key = read_switches(STATE_CHANGE);
        
        M_key = read_switches(LEVEL_CHANGE);
        if (M_key != ALL_RELEASED) 
        {
            temp = M_key;
        }

        if (M_key != ALL_RELEASED) 
        {
            delay++;
            if (delay > 500) 
            {
                if( M_key == MK_SW5 )
                {
                    key = MK_SW5_LONG;
                }
                else if( M_key == MK_SW6)
                {
                    key = MK_SW6_LONG;
                }

            }
        } 
        else if (delay < 500 && delay != 0) 
        {
            delay = 0;
            key = temp;    
        } 
        else 
        {
            delay = 0;
        }
        
        
        
        if( key == MK_SW5 )
        {
            temp_time[index]++;
            if( index == 2 && temp_time[index] == 24 )
            {
                temp_time[index] = 0;
            }
            else if( temp_time[index] == 60 )
            {
                temp_time[index] = 0;
            }
        }
        if( key == MK_SW6 )
        {
            index++;
            if(index == 3)
            {
                index = 0;
            }
        }
        clcd_print("HH:MM:SS",LINE1(8));
        //printing hours
        if( index != 2 )
        {
            clcd_putch((temp_time[2]/10)%10+'0',LINE2(8));
            clcd_putch(temp_time[2]%10+'0',LINE2(9));
        }
        clcd_putch(':',LINE2(10));
        
        //printing minutes
        if( index != 1 )
        {
            clcd_putch((temp_time[1]/10)%10+'0',LINE2(11));
            clcd_putch(temp_time[1]%10+'0',LINE2(12));
        }
        clcd_putch(':',LINE2(13));
        
        
        //printing seconds
        if( index != 0 )
        {
            clcd_putch((temp_time[0]/10)%10+'0',LINE2(14));
            clcd_putch(temp_time[0]%10+'0',LINE2(15));
        }
         
        
        //for blinking
        int i;
    //    i = 14 - (index*3);
        if( index == 0 )
        {
            i = 14;
        }
        else if( index == 1 )
        {
            i = 11;
        }
        else
        {
            i = 8;
        }
        
        if( blink_delay++ == 300 )
        {
            clcd_print("  ",LINE2(i));

        }
        else if( blink_delay == 600 )
        {
            blink_delay = 0;
            clcd_putch((temp_time[index]/10)%10+'0',LINE2(i));
            clcd_putch(temp_time[index]%10+'0',LINE2(i+1));
            
        }

        
        if( key == MK_SW5_LONG )
        {
            //set time and exit
            CLEAR_DISP_SCREEN;
            screen_flag = MENU_SCREEN;
            menu_flag = DISPLAY_MENU;
            clcd_print("Updated Success",LINE1(0));
            update_time();
            store_event("ST");
            strncpy(event,"ST",2);
            update_event_flag = 1;
            return;
        }
        
         if( key == MK_SW6_LONG )
        {
            screen_flag = DASHBOARD;
            menu_flag = DISPLAY_MENU;
            
            return;
        }
        key = ALL_RELEASED;
    }
}
