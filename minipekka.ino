#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeOrion.h>

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
MeDCMotor motor_9(9);//motore di destra
MeDCMotor motor_10(10);//motore di sinistra
MeDCMotor motor_1(1);//motore stringimento
MeDCMotor motor_2(2);//motore alzata
MeUltrasonicSensor ultrasonic_8(8); //sensore ultrasuoni

void setup(){
    motor_1.run(100);
    motor_2.run(100);
    _delay(0.75);
    
    if((ultrasonic_8.distanceCm()) > (0)){
        motor_9.run(0);
        motor_10.run(0);
        motor_1.run(0);
        motor_2.run(0);
    }
}
//shai
void loop(){
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
}
