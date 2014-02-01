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

BusIn joy(p15,p12,p13,p16);
DigitalIn fire(p14);
 
BusOut leds(LED1,LED2,LED3,LED4);
 
lcd128 lcd;

char lorem[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";

void header(char* name, char* page)
{
    lcd.Clear();
    lcd.Bold();
    lcd.String(name);
    lcd.Bold(false);
    lcd.String(page);
    lcd.XY(0,1); 
}

int main()
{
    lcd.Reset();   
    
    // Nice header with bold first word
    header("MBED","Application Board"); 
    
    // Horizontal line
    lcd.Write((char)0x02, LCD_X);
    
    // Sample text
    lcd.XY(0,2);
    lcd.String(lorem);
    lcd.Update();

    while(1);     
}