/*
 * File:   main.c
 * Author: Emertxe
 *
 * Created on March 28, 2024, 10:24 AM
 */


#include <xc.h>
#include "main.h"


extern unsigned char time[9];

void store_event(char event[]) {
    //update the time before storing
    char temp_log[15];
    get_time();
    strncpy(temp_log, time, 8);
    temp_log[8] = ' ';
    strncpy(&temp_log[9], event, 2);
    temp_log[11] = ' ';
    get_speed();
    temp_log[12] = (speed / 10) % 10 + '0';
    temp_log[13] = speed % 10 + '0';
    temp_log[14] = '\0';

    //read log_index from eeprom
    log_index = read_external_eeprom(200);

    if (log_index == 10) {
        //perform left shift operation
        int start_add = 0x10;
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 15; k++) {
                char data = read_external_eeprom(start_add + 15 + k);
                write_external_eeprom((start_add + k), data);
            }
            start_add = start_add + 15;
        }

        //store in last index
        for (int i = 0; i < 15; i++) {
            write_external_eeprom(start_add, temp_log[i]);
            start_add++;
        }
        log_index = 10;
        write_external_eeprom(200, log_index);
    } else {
        for (int i = 0; i < 15; i++) {
            write_external_eeprom(address, temp_log[i]);
            address++;
        }
        log_index++;
        write_external_eeprom(200, log_index);
    }
    

}

void init_config() {


    /*Initial configurations function call */
    init_i2c();
    init_ds1307();
    PEIE = 1;
    init_matrix_keypad();
    init_clcd();
    init_timer0();
    init_adc();
    init_uart();

    GIE = 1;
}

void main(void) {

    init_config();
    
    store_event("ON");

    while (1) {
        
        if( screen_flag == DASHBOARD )
        {
            display_dashboard();
        }
        else if( screen_flag == PASSWORD_SCREEN )
        {
            password_screen();
        }
        else if( screen_flag == MENU_SCREEN )
        {
            if( menu_flag == DISPLAY_MENU )
            {
                menu_screen();
            }
            else if( menu_flag == VIEW_LOG )
            {
                view_log();
            }
            else if( menu_flag == DOWNLOAD_LOG )
            {
                download_log();
                //clcd_print("Download Log    ", LINE1(0));
            }
            else if( menu_flag == CLEAR_LOG )
            {
                clear_log();
            }
            else if( menu_flag == SET_TIME )
            {
                set_time();
            }
            else if( menu_flag == CHANGE_PASSWORD )
            {
                change_password();
            }
        }

//        switch (screen_flag) {
//            case DASHBOARD:
//                /*call display_dashbord function */
//                display_dashboard();
//
//                break;
//            case PASSWORD_SCREEN:
//                /*call password_screen function */
//                password_screen();
//                break;
//            case MENU_SCREEN:
//            
//                switch (menu_flag) {
//                   
//
//                    case DISPLAY_MENU:
//                        /*call menu_screen function */
//                        CLEAR_DISP_SCREEN;
//                        menu_screen();
//                        break;
//                        
//                    case VIEW_LOG:
//                        /*call view_log function */
//                         view_log();
//
//                        break;
//                        
//                    case DOWNLOAD_LOG:
//                        /*call download log function */
//
//                        clcd_print("Download Log    ", LINE1(0));
//                        break;
//                        
//                    case CLEAR_LOG:
//                        /*call clear_log function */
//                        clear_log();
//                        break;
//                        
//                    case SET_TIME:
//                        /*call set_time function */
//                        set_time();
//                        // clcd_print("Set time        ",LINE1(0));
//                        break;
//                        
//                    case CHANGE_PASSWORD:
//                        /*call change_password function */
//                        change_password();
//                        break;    
//            }
//            break;
//                
//                /*call menu_screen function */
//
//        }

    }

}
