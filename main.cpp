#include "mbed.h"
#include "lcd128lib.h" 
#include "LM75B.h"
#include "MMA7660.h"


lcd128 lcd;
DigitalOut Up(p15);
DigitalIn fire(p14);
LM75B sensor(p28, p27);
PwmOut spkr(p26);
AnalogOut Aout(p18);
AnalogIn pot1(p19), pot2(p20);
PwmOut led1(LED1), led2(LED2), led3(LED3), led4(LED4);
MMA7660 MMA(p28, p27);


void LEDGraph(float value) {
    led1 = (value >= 0.2) ? 1 : 0;
    led2 = (value >= 0.4) ? 1 : 0;
    led3 = (value >= 0.6) ? 1 : 0;
    led4 = (value >= 0.8) ? 1 : 0;
}

int main() {
    lcd.Reset();  
    lcd.XY(0, 0);
    lcd.Bold(true); lcd.String(" EMBED DEMO "); lcd.Bold(false);
    lcd.Row(1, "Simple interface to show      different mbed services. ");
    lcd.Row(3, "Push joystick!", true, LCD_ALIGN_CENTER);
    
    lcd.Update();
    wait_ms(500); 
    while(! fire) wait_ms(100);



    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2); 
    lcd.XY(0,0);
    lcd.Bold(true); lcd.String("Speaker test"); lcd.Bold(false);
    lcd.Clear(3);
    lcd.Update();
    wait_ms(2000);

    for (float i=2000.0; i<10000.0; i+=100) {
        spkr.period(1.0/i);
        spkr=0.5;
        wait(0.1);
    }
    lcd.Row(3, "Push joystick!", true, LCD_ALIGN_CENTER);
    lcd.Update();
    spkr=0.0;
    while(!fire) {}
    
    
    
    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2);  
    lcd.XY(0,0);
    lcd.Bold(true); lcd.String("Audio out test"); lcd.Bold(false);
    lcd.Update(); 
    wait_ms(2000);

    for(float i=0.0; i<1.0; i+=0.1) {
        Aout = i;
        wait(0.00001+(0.0001*pot1.read()));
    }
    while(!fire) {}



    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2);
    lcd.XY(0,0);
    lcd.Bold(true); lcd.String("Potentiometer"); lcd.Bold(false);
    lcd.Update();
    wait_ms(2000);
    float sample;
    
    do {
        sample = pot1;
        LEDGraph(sample);
        wait(0.01);
        
    } while(!fire);
        wait_ms(500);



    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2);
    lcd.XY(0,0);
    lcd.Bold(true); lcd.String("Animation"); lcd.Bold(false);
    lcd.Update();
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
  
  
  
    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2);
    lcd.XY(0,0);
    lcd.Bold(true); lcd.String("Temperature"); lcd.Bold(false);
    lcd.XY(0,1); lcd.String("Cel");
    do { 
        lcd.Clear(2); 
        lcd.XY(22, 1); 
        lcd.Bar(98, (float)sensor.read()/100.0);
        lcd.Update();
        wait_ms(50);
    } while(! fire);    
        wait_ms(500);
 
    

    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2);
    lcd.XY(0,0); lcd.String("R");
    lcd.XY(0,1); lcd.String("G");
    lcd.XY(0,2); lcd.String("B");
    lcd.Clear(3);
    
    PwmOut r (p23);
    PwmOut g (p24);
    PwmOut b (p25);

    for(float i = 0.0; i < 1.0 ; i += 0.001) {
        float p = 3 * i;
        r = 1.0 - ((p < 1.0) ? 1.0 - p : (p > 2.0) ? p - 2.0 : 0.0);
        g = 1.0 - ((p < 1.0) ? p : (p > 2.0) ? 0.0 : 2.0 - p);
        b = 1.0 - ((p < 1.0) ? 0.0 : (p > 2.0) ? 3.0 - p : p - 1.0);  ;  

        lcd.XY(22, 0); 
        lcd.Bar(98, (1.0 - (float)r.read()));
    
        lcd.XY(22, 1); 
        lcd.Bar(98, (1.0 - (float)g.read()));
        
        lcd.XY(22, 2); 
        lcd.Bar(98, (1.0 - (float)b.read()));
        
        lcd.Update();
        wait_ms(50);
    } 
    lcd.Row(3, "Push joystick!", true, LCD_ALIGN_CENTER);
    lcd.Update();
    while(! fire);    
        r = 1.0;
        g = 1.0;
        b = 1.0;
        wait_ms(500);  



    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2);
    lcd.XY(0,0);
    lcd.Bold(true); lcd.String("Accelerometer"); lcd.Bold(false);
    lcd.Row(1, "led2=x     led3=y                  led4=z");
    lcd.Update();

    if (MMA.testConnection())
        led1 = 1;
        
    do {
        led2 = MMA.x();
        led3 = MMA.y();
        led4 = MMA.z();
        
        
    } while(! fire);    
        wait_ms(500);



    lcd.Clear(0); lcd.Clear(1); lcd.Clear(2);
    lcd.Update();
    lcd.Reset();  
    lcd.XY(0, 0); 
    lcd.Bold(true); lcd.String("   THE END"); lcd.Bold(false);
    lcd.Row(1, "Simple interface to show      different mbed services.");
    lcd.Row(3, "PRESS THE RESET BUTTON");
    
    lcd.Update();

}