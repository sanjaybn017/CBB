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

void clear_log()
{
    //logic for clear_log
    int delay = 500;
    write_external_eeprom(200,0);
    CLEAR_DISP_SCREEN;
    
    screen_flag = MENU_SCREEN;
    menu_flag = DISPLAY_MENU;
    
    while( delay-- )
    {
        clcd_print("   Clear log    ",LINE1(0));
        clcd_print("  Successfully  ",LINE2(0));
    }
    store_event("CL");
    strncpy(event,"CL",2);
    update_event_flag = 1;
    
    
}