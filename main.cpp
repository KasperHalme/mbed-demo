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

AnalogIn Pot1(p19);
AnalogIn Pot2(p20);
 
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

char* BANG = " BANG! ";

int main()
{
    lcd.Reset();   
    
    // Nice header with bold first word
    header("MBED","Application Board"); 
        
    int pot = 0, old = 0;
    bool update = true;
    
    do {
        
        pot = Pot1 * 130;
        if((old/2) != (pot/2)) update = true; // +-1 to eliminate jitter
        old = pot;
        
        if (update) {
            
            lcd.Clear(1);
            lcd.Clear(2);
            lcd.Clear(3);
            
            lcd.XY(0,1);
            lcd.Bar(LCD_X, pot / 128.0);
                        
            if (fire) {
                
                lcd.Bold(true);
                lcd.Invert(true);
                lcd.XY(64-lcd.StringWidth(BANG)/2,3);
                lcd.String(BANG);
                lcd.Bold(false);
                lcd.Invert(false);
            
            } else {
            
                lcd.XY(0,2);
                lcd.String(lorem);
            
            }
            
            lcd.Update();
            update = false;
        }
        
        wait(0.1);        

        if (fire) { leds = 0xf; update = true; } else leds = joy;
                
    } while(1);    
}