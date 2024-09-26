/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */



#include <xc.h>
#include "main.h"

//extern unsigned char screen_flag;
//extern unsigned char menu_flag;
void menu_screen()
{
    //logic menu_screen
    char *menu[5] = {"View_log        ","Download_log    ","clear_log       ","Set_time        ","Change_password "};
    char menu_arr[5] = {VIEW_LOG, DOWNLOAD_LOG , CLEAR_LOG, SET_TIME, CHANGE_PASSWORD};
    char key;
    char M_key = ALL_RELEASED;
    char prev_flag = -1;
    int index = 0;
    char temp;
    int delay = 0;
    int block = 800;
    
    CLEAR_DISP_SCREEN;
    int sub_block = 800;
    while(sub_block--)
    {
        clcd_print("  Entering",LINE1(3));
        clcd_print("MENU SCREEN",LINE2(0));
    }

    //clear screen first
    CLEAR_DISP_SCREEN;
    clcd_print("->",LINE1(0));
    while(1)
    {
      //  key = read_switches(STATE_CHANGE);
        key = ALL_RELEASED;
        
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
        
        
        
        if( key == MK_SW5 && prev_flag == 1 && index > 0 )
        {
            index--;
        }
        if( key == MK_SW6 && prev_flag == 0 && index < 3 )
        {
            index++;
        }
        clcd_print(menu[index],LINE1(3));
        clcd_print(menu[index+1],LINE2(3));
        
        if( key == MK_SW5 )
        {
            prev_flag = 1;
            clcd_print("->",LINE1(0));
            clcd_print("  ",LINE2(0));
            
        }
        if( key == MK_SW6 )
        {
            prev_flag =  0;
            clcd_print("  ",LINE1(0));
            clcd_print("->",LINE2(0));
        }
        
        
        //if long press mkp5 enter into choice
        if( key == MK_SW5_LONG )
        {
        
            index = index + !prev_flag;
            screen_flag = MENU_SCREEN;
            menu_flag = menu_arr[index];
            CLEAR_DISP_SCREEN;
            while(block--)
            {
                clcd_print("Entering",LINE1(0));
                clcd_print(menu[index],LINE2(0));
            }
         
            return;
        }
        
        //if long press mkp6 update flag and exit
        if( key == MK_SW6_LONG )
        {
            screen_flag = DASHBOARD;
            menu_flag = DISPLAY_MENU;
            CLEAR_DISP_SCREEN;
            while(block--)
            {
                clcd_print("Entering",LINE1(0));
                clcd_print("DASHBOARD",LINE2(0));
            }
            return;
            
        }
        
        
    }
    
    
}