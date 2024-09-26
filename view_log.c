/*
 * File:   
 * Author: <NAME>
 *
 * 
 */



#include <xc.h>
#include "main.h"

//extern unsigned char screen_flag;
//extern unsigned char menu_flag;
void read_log()
{
    int address = 0x10;
    log_index = read_external_eeprom(200);
    for(int i = 0; i <= log_index ; i++ )
    {    
        for(int j = 0; j < 15; j++)
        {
            log[i][j] = read_external_eeprom(address++);
        }
    }
}

void view_log()
{
    //logic for view_log
    char key= ALL_RELEASED;
    char M_key=ALL_RELEASED;
    char prev_flag = -1;
    int index = 0;
    char temp;
    int delay = 0;
    read_log();
    
    
    //clear screen first
    CLEAR_DISP_SCREEN;
    clcd_print("->",LINE1(0));
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
        

        if( key == MK_SW5 && index > 0 )
        {
            index--;
        }
        if( key == MK_SW6 && index < log_index-1 )
        {
            index++;
        }
        clcd_print("    VIEW LOG    ",LINE1(0));
        clcd_putch(index+48,LINE2(0));
        if( log_index == -1 )
        {
            clcd_print("LOG_CLEARED     ",LINE2(2));
        }
        clcd_print(log[index],LINE2(2));
        
//        if( key == MK_SW5 )
//        {
//            prev_flag = 1;
//            clcd_print("->",LINE1(0));
//            clcd_print("  ",LINE2(0));
//            
//        }
//        if( key == MK_SW6 )
//        {
//            prev_flag =  0;
//            clcd_print("  ",LINE1(0));
//            clcd_print("->",LINE2(0));
//        }
        
        //if long press mkp6 update flag and exit
        if( key == MK_SW6_LONG )
        {
            screen_flag = MENU_SCREEN;
            menu_flag = DISPLAY_MENU;
            
            return;
        }
        key = ALL_RELEASED;
    }
}