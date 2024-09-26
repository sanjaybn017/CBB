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

void change_password()
{
    //change change_password logic
    unsigned short i = 0;
    unsigned short flag = 1;
    unsigned int delay = 0;
  //  unsigned int address = 0x00;
    char new_paswd[5];
    char confrm_paswd[5];
    char confrm_flag = 0;
    int block = 1000;
    //   write_internal_eeprom(address,'0');
    //   address++;
    CLEAR_DISP_SCREEN;
    while(1)
    {
        if( confrm_flag == 0 )
        {
            clcd_print("Enter New Passwd",LINE1(0));
        }
        else
        {
            clcd_print("cnfrm New Passwd",LINE1(0));
        }
        
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
        
        // for printing * and writing 1 or 0 to new password string
        if( key == MK_SW1 && !confrm_flag )
        {
            clcd_putch('*',LINE2(i));
            new_paswd[i++] = '0';           
        }
        if( key == MK_SW2 && !confrm_flag )
        {
            clcd_putch('*',LINE2(i));
            new_paswd[i++] = '1';
        }
        
        
        // for printing * and writing 1 or 0 to confirm password string
        if( key == MK_SW1 && confrm_flag )
        {
            clcd_putch('*',LINE2(i));
            confrm_paswd[i++] = '0';           
        }
        if( key == MK_SW2 && confrm_flag )
        {
            clcd_putch('*',LINE2(i));
            confrm_paswd[i++] = '1';
        }
        
        if( i == 4  && !confrm_flag )
        {
            confrm_flag = 1;
            new_paswd[i] = '\0';
            i = 0;
            flag = 1;
            CLEAR_DISP_SCREEN;
        } 
        
        if( i == 4  && confrm_flag )
        {
            confrm_paswd[i] = '\0';
            
            //compare two password
            if( strcmp(new_paswd,confrm_paswd)== 0)
            {
                
                //store new password in eeprom
                write_external_eeprom(0x00,new_paswd[0]);
                write_external_eeprom(0x01,new_paswd[1]);
                write_external_eeprom(0x02,new_paswd[2]);
                write_external_eeprom(0x03,new_paswd[3]);
                
                //go back to menu screen
                screen_flag = MENU_SCREEN;
                menu_flag = DISPLAY_MENU;
                
                //print error message for some seconds
                while( block-- )
                {
                    clcd_print("Password Changed",LINE1(0));
                    clcd_print("  Successfully  ",LINE2(0));
                }
                store_event("CP");
                strncpy(event,"CP",2);
                update_event_flag = 1;
                
                return;
            }
            else
            {
                //go back to menu screen
                screen_flag = MENU_SCREEN;
                menu_flag = DISPLAY_MENU;
                
                
               //print error message
                while( block-- )
                {
                    clcd_print("Passwd not match",LINE1(0));
                    clcd_print("not changing org",LINE2(0));
                }
                
                return;
            }
        }
        
    }
}