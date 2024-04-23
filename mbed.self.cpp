//
// PWM LED
//
#include "mbed.h" 
PwmOut LED(PC_8s); 
 
int main() { 
  LED.Period_ms(10); 
  LED=0.00f; 
  while(true){ 
    for(float val=0.0f; val<1.0f; val+=0.1f){ 
      LED=val; 
      wait(0.5f); 
    } 
    for(float val=1.0f; val>0.0f; val-=0.1f){ 
      LED=val; 
      wait(0.5f); 
    } 
  } 
}
//
// PWM Buzzer
//
#include "mbed.h" 
PwmOut speaker(PC_8); 
 
int main(){ 
    speaker.period(1.0/240.0); 
    speaker=0.5; 
    wait(0.5); 
    speaker.period(1.0/270.0); 
    speaker=0.5; 
    wait(0.5); 
    speaker.period(1.0/300.0); 
    speaker=0.5; 
    wait(0.5); 
    speaker.period(1.0/337.0); 
    speaker=0.5; 
    wait(0.5); 
    speaker.period(1.0/360.0); 
    speaker=0.5; 
    wait(0.5); 
    speaker.period(1.0/400.0); 
    speaker=0.5; 
    wait(0.5); 
    speaker.period(1.0/450.0); 
    speaker=0.5; 
    wait(0.5); 
    speaker=0.0; 
}
//
// Tera Term, Pot
//
#include "mbed.h" 
 
Serial pc(USBTX, USBRX); 
AnalogIn ain(PC_3); 
PwmOut PWM1(PC_8); 
 
int main() { 
    while (1) { 
        float value = ain * 5; 
        pc.printf("The reading of pot: %f", value); 
        wait(0.25); 
        PWM1.period(0.01); 
        PWM1 = ain; 
    } 
} 
//
// LCD Pot
//
#include "mbed.h" 
#include "TextLCD.h"  
AnalogIn ain(PC_5); 
TextLCD lcd(PC_0,PC_1,PB_0,PA_4,PA_1,PA_0); 
int main() {  
    lcd.cls();  
    while(1) {  
        float value = ain*5; 
        lcd.locate(5,0); 
        lcd.printf("v = %0.3f",value);  
        wait(2); 
        lcd.cls();  
        wait(1); 
    } 
} 
//
// Servo
//
#include "mbed.h" 
PwmOut PWM1(PC_8); 
int main() { 
    while(1){ 
        PWM1.period_ms(20); 
        PWM1.pulsewidth_us(500); 
        wait(1); 
        PWM1.pulsewidth_us(1000); 
        wait(1); 
        PWM1.pulsewidth_us(1500); 
        wait(1); 
        PWM1.pulsewidth_us(2000); 
        wait(1); 
        PWM1.pulsewidth_us(2500); 
        wait(1); 
    } 
} 
//
// Ultrasonic
//
#include "mbed.h" 
#include "TextLCD.h" 
TextLCD lcd(PC_0,PC_1,PB_0,PA_4,PA_1,PA_0); 
DigitalOut trigger(PC_8); 
DigitalIn echo(PC_6); 
DigitalOut buzzer(PC_10); 
int distance = 0; 
Timer sonar; 
 
int main() { 
  lcd.cls();     
  while(1) { 
    trigger = 1; 
    sonar.reset(); 
    wait_us(10.0); 
    trigger = 0; 
    while(echo == 0); 
    sonar.start(); 
    while(echo == 1); 
    sonar.stop(); 
    distance = (sonar.read_us())/58.0; 
    lcd.locate(1,0); 
    lcd.printf("Distance %d cm\n\r",distance); 
    wait(0.2); 
    if(distance<=15){ 
        buzzer = 1; 
        lcd.locate(2,1); 
       lcd.printf("Obstacle!!!",distance); 
    } 
    else{ 
        buzzer = 0; 
        lcd.cls(); 
    } 
  } 
}
//
// SPI 
//
// Master
#include "mbed.h" 
SPI spi(PB_15,PB_14,PB_13); 
DigitalOut cs(PB_12); 
Serial pc(USBTX,USBRX); 
int main(){ 
    char send_val; 
    pc.printf("Press any key to start..\n"); 
    while(1){ 
        send_val=pc.getc(); 
        pc.printf("%c",send_val); 
        cs=0; 
        spi.write(send_val); 
        cs=1; 
        wait(0.01); 
    } 
}
// Slave
#include "mbed.h" 
SPISlave spi(PB_15,PB_14,PB_13, 
PB_12); 
Serial pc(USBTX, USBRX); 
char recd_val; 
int main(){ 
    pc.printf("Received word is...\n"); 
    while(1){ 
        if(spi.receive()){ 
            recd_val=spi.read(); 
            
pc.printf("%c",recd_val); 
        } 
    } 
}
//
// Bluetooth
//
#include "mbed.h" 
Serial pc(USBTX,USBRX); 
Serial bt(PC_10,PC_11); 
int main(){ 
    char ch; 
    pc.baud(9600); 
    bt.baud(9600); 
    pc.printf("Hello World\n\r"); 
    while(1){ 
        if (bt.readable()){ 
            ch=bt.getc(); 
            pc.printf("%c",ch); 
        }else if(pc.readable()){ 
            ch=pc.getc(); 
            bt.printf("%c",ch); 
        } 
    } 
} 
//
// I2C
//
// Master
#include "mbed.h" 
Serial pc (USBTX,USBRX); 
I2C i2c(PB_11,PB_10); 
int main(){ 
    int address = 0xA0; 
    char data[20]; 
    pc.printf("Enter data to be sent"); 
    pc.scanf("%s",&data); 
    pc.printf("%s",data); 
    int len=strlen(data); 
    i2c.write(address, data,len); 
    i2c.write(data,len); 
    wait(2); 
} 
// Slave
#include "mbed.h" 
Serial pc(USBTX, USBRX); 
I2CSlave slave(PB_11, PB_10); 
int main() { 
    char buf[20]; 
    char msg[] = "Slave!"; 
    slave.address(0xA0); 
    while (1) { 
        int i = slave.receive(); 
        switch (i) { 
            case I2CSlave::ReadAddressed: 
            slave.write(msg, strlen(msg) + 1); 
            break; 
            case I2CSlave::WriteGeneral: 
            slave.read(buf, 20); 
            pc.printf("Read1 : %s\r\n", buf); 
            //wait(1); 
            break; 
            case I2CSlave::WriteAddressed: 
            slave.read(buf, 20); 
            pc.printf("Read2 : %s\r\n", buf); 
            wait(5); 
            break; 
        } 
    } 
}
//
// ADXL
//
#include "mbed.h" 
#include "ADXL345_I2C.h" 
ADXL345_I2C accelerometer(PB_11,PB_10); 
Serial pc(USBTX,USBRX); 
int X_out_raw,Y_out_raw,Z_out_raw; 
int X_out,Y_out,Z_out; 
int main(){ 
    int readings[3]={0,0,0}; 
    pc.printf("Starting ADXL345 test...\n"); 
    wait(.001); 
    pc.printf("Device ID is: 0x%02x\n",accelerometer.getDeviceID()); 
    wait(.001); 
    if(accelerometer.setPowerControl(0x00)){ 
        pc.printf("didn't initialize power control\n"); 
        return 0; 
    } 
    wait(.001); 
    if(accelerometer.setDataFormatControl(0x0B)){ 
        pc.printf("didn't set data format\n"); 
        return 0; 
    } 
    wait(.001); 
    if (accelerometer.setDataRate(ADXL345_3200HZ)) { 
        pc.printf("didn't set data rate\n");        
        return 0; 
    }         
    wait(.001);        
    if(accelerometer.setPowerControl (MeasurementMode)) { 
        pc.printf("didn't set the power control to measurement\n"); 
        return 0; 
    }         
    while (1){        
        wait(0.1);        
        accelerometer.getOutput(readings);         
        wait(0.1); 
        X_out_raw = (int16_t)readings[0]; 
        Y_out_raw =(int16_t)readings[1]; 
        Z_out_raw =(int16_t)readings[2]; 
        X_out = 0.94 *X_out + 0.06* X_out_raw; 
        Y_out = 0.94 *Y_out + 0.06 * Y_out_raw; 
        Z_out = 0.94 *Z_out + 0.06 * Z_out_raw; 
        pc.printf("X:%i,Y:%i,Z:%i\r\n",X_out, Y_out, Z_out); 
    } 
}
//
// Keypad
//
#include "mbed.h" 
#include "keypad.h" 
#include "TextLCD.h" 
 
TextLCD lcd(PC_0,PC_1,PB_0,PA_4,PA_1,PA_0); 
Keypad keypad(PA_1,PB_3,PB_5,PB_4,PB_10,PA_8,PA_9,PC_7); 
DigitalOut buzzer(PC_6); 
PwmOut servo(PC_8); 
const char passkey[4] = {'1','2','3','4'}; 
char pass[4]; 
int count; 
 
int main(){ 
    keypad.enablePullUp(); 
    while(1){ 
        lcd.cls(); 
        lcs.locate(0,0); 
        lcd.printf(" Enter Password : "); 
        servo.period_ms(20); 
        servo.pulsewidth_us(500); 
        buzzer=0; 
        for(count=0; count<4; count++){ 
            while(keypad.getKey() == '\0'); 
            pass[count] = keypad.getKey(); 
            { 
                lcd.locate(count,1); 
                lcd.printf("*"); 
                wait(1); 
            } 
        } 
        if((passkey[0] == pass[0]) && (passkey[1] == pass[1]) && (passkey[2] == pass[2]) 
&& (passkey[3] == pass[3])){ 
            lcd.cls(); 
            lcd.locate(0,0); 
            lcd.printf("Correct Password"); 
            lcd.locate("Door Opening"); 
            servo.period_ms(20); 
            servo,pulsewidth_us(1500);
            wait(3); 
        } else { 
            lcd.cls(); 
            lcd.locate(0,0); 
            lcd.printf("Incorrect Password"); 
            lcd.locate(0,1); 
            lcd.printf("Door Can't Openn"); 
            buzzer=1; 
            wait(3); 
        } 
    } 
}
//
// 7-Segment
//
#include "mbed.h" 
BusOut display (PA_10,PB_3,PB_5,PB_4,PB_10, 
PA_8,PA_9,PC_7);  
int main(){ 
    while(1){ 
        for(int i=0; i<=9; i++){ 
            switch (i){ 
                case 0: display=0xC0; break; 
                case 1: display=0xF9; break; 
                case 2: display=0xA4; break; 
                case 3: display=0xB0; break; 
                case 4: display=0x99; break; 
                case 5: display=0x92; break; 
                case 6: display=0x82; break; 
                case 7: display=0xF8; break; 
                case 8: display=0x80; break; 
                case 9: display=0x90; break; 
                case 10: display=0x88; break; 
                case 11: display=0x83; break; 
                case 12: display=0xC6; break; 
                case 13: display=0xA1; break; 
                case 14: display=0x86; break; 
                case 15: display=0x8E; break; 
            } 
            wait(2); 
        } 
    } 
} 
//
// RTOS
//
#include "mbed.h" 
#include "rtos.h" 
Serial PC(USBTX, USBRX); 
Thread Thread1, Thread2; 
Semaphore sem_count(1); 
Mutex mutex1; 
int i = 10; 
void count(int i) { 
    mutex1.lock(); 
    sem_count.wait(); 
    PC.printf("Count values before delay: %d\n\r", i); 
    Thread::wait(1000); 
    PC.printf("Count value after delay : %d\n\r", i); 
    mutex1.unlock(); 
    sem_count.release(); 
} 
void increment() { 
    i += 1; 
    count(i); 
} 
void decrement() { 
    i -=1 ; 
    count(i); 
} 
int main() { 
    Thread1.start(increment); 
    Thread2.start(decrement); 
    Thread1.join(); 
    Thread2.join(); 
} 