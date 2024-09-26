/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */



#include <xc.h>
#include "main.h"

void download_log()
{
    //logic for clear
    read_log();
    log_index = read_external_eeprom(200);
    puts("\n\r-----Downloading log-----");
    for( int i = 0; i< log_index; i++ )
    {
        puts("\n\r");
        puts(log[i]);
      //  puts("\n\r");
    }
    int block = 1000;
    while(block--)
    {
        clcd_print("Download log    ",LINE1(0));
        clcd_print("Successfully... ",LINE2(0));
    }
    
    store_event("DL");
    strncpy(event,"DL",2);
    update_event_flag = 1;
    screen_flag = MENU_SCREEN;
    menu_flag = DISPLAY_MENU;
}