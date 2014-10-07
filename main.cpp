//
// MBED Application Board
// Lightweight C12832 LCD library
// 2014, Alexander Medvedev, @medvdv
//

// 
// Usage Sample
// 

#include "mbed.h"

#include "lcd128lib.h" 

#include "lcd128menu.h"
 
lcd128 lcd;

bool    menuCheckVariable = false;
int     menuRadioVariable = 1;
float   menuProgressBar   = 0.5;

lcd128entry menuMain[] = {

    { APPMENU_COMMENT,  0, "Main Menu",        true,  false, 0, 0, 0, NULL }, 
    { APPMENU_ACTION,   1, "Action Item",      false, false, 0, 0, 0, NULL },
    { APPMENU_ACTION,   2, "Other Action",     false, false, 0, 0, 0, NULL },
    { APPMENU_BREAK,    0, NULL,               false, false, 0, 0, 0, NULL },
    { APPMENU_CHECK,    0, "Check Button",     false, false, 0, 0, 0, & menuCheckVariable },
    { APPMENU_BREAK,    0, NULL,               false, false, 0, 0, 0, NULL },
    { APPMENU_COMMENT,  0, "Select one:",      false, false, 0, 0, 0, NULL }, 
    { APPMENU_RADIO,    1, "Radio Button 1",   false, false, 0, 0, 0, & menuRadioVariable },
    { APPMENU_RADIO,    2, "Radio Button 2",   false, false, 0, 0, 0, & menuRadioVariable },
    { APPMENU_RADIO,    3, "Radio Button 3",   false, false, 0, 0, 0, & menuRadioVariable },
    { APPMENU_BAR,      0, NULL,               false, false, 0, 0, 0, & menuProgressBar },

};
    
int main()
{
    BusIn joy(p15, p12, p13, p16);
    DigitalIn fire(p14);

    lcd.Reset();  

    lcd.XY(0, 0); 
    lcd.Bold(true); lcd.String("LCD LIBRARY"); lcd.Bold(false);
    lcd.Row(1, "Simple interface library with nice proportional font.");
    lcd.Row(3, "Push joystick!", true, LCD_ALIGN_CENTER);
    lcd.InverseRow(2, 0x80); // Add one inverted pixel line upper than last row
    
    lcd.Update();
    
    wait_ms(500); while(! fire) wait_ms(100);
        
    lcd.Row(0, "Left aligned text");
    lcd.Row(1, "Center aligned text", false, LCD_ALIGN_CENTER);
    lcd.Row(2, "Right aligned text", false, LCD_ALIGN_RIGHT);
    lcd.InverseRow(2, 0x80); // Add one inverted pixel line upper than last row
    
    lcd.Update();

    wait_ms(500); while(! fire) wait_ms(100);
    
    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2);
    
    lcd.XY(0, 1); 
    lcd.Bold(true); lcd.String("Bold"); lcd.Bold(false);
    lcd.String(" and ");
    lcd.Underline(true); lcd.String("underlined"); lcd.Underline(false);
    lcd.String(" text");
     
    lcd.InverseRow(2, 0x80); // Add one inverted pixel line upper than last row

    lcd.Update();

    wait_ms(500); while(! fire) wait_ms(100);
        
    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2); lcd.InverseRow(2, 0x80);

    lcd.Row(0, "Arbitary X position:");

    wait_ms(500);
    
    int x = 0;    
    
    do { 
        lcd.Clear(1); 
        lcd.XY(5 + x/8, 1); 
        lcd.Character(LCD_CLOCK0 + (x % 8));
        lcd.Update();
        x += 1;
        x %= 113*8;
        wait_ms(100);
    } while(! fire);
    
    wait_ms(500);
    
    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2); lcd.InverseRow(2, 0x80);
    
    lcd.XY(0,1); lcd.String("Bar");

    x = 0;
    
    do { 
        lcd.Clear(2); 
        lcd.XY(22, 1); 
        lcd.Bar(98, x/96.0);
        lcd.Update();
        x += 1;
        x %= 97;
        wait_ms(50);
    } while(! fire);

    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2); lcd.InverseRow(2, 0x80);

    lcd.Row(1, "Hardware Inverse All");
    lcd.Update();
    
    wait_ms(500); while(! fire) wait_ms(100);

    lcd.InverseMode(true);

    wait_ms(500); while(! fire) wait_ms(100);
    
    lcd.InverseMode(false);

    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2); lcd.InverseRow(2, 0x80);

    lcd.Row(1, "Hardware Power Off / On");
    lcd.Update();

    wait_ms(500); while(! fire) wait_ms(100);

    lcd.Power(false);
    
    wait_ms(500); while(! fire) wait_ms(100);
    
    lcd.Power(true);

    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2);
    
    lcd.Row(0, "Menu interface:");
    lcd.Row(1, "Values and sub-menu");
    lcd.Row(2, "Checkbox, radiobutton");
    
    lcd.InverseRow(2, 0x80);
    
    lcd.Update();
    
    wait_ms(500); while(! fire) wait_ms(100);    
           
    lcd128menu(&lcd, menuMain, sizeof(menuMain) / sizeof(lcd128entry)); 

}