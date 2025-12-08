#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeOrion.h>
MeDCMotor motor_9(9);//motore di destra
MeDCMotor motor_10(10);//motore di sinistra
MeDCMotor motor_1(1);//motore stringimento
MeDCMotor motor_2(2);//motore alzata
MeUltrasonicSensor ultrasonic_8(8); //sensore ultrasuoni

void setup(){
    int robapresa=0;
    motor_1.run(100);
    motor_2.run(100);
    _delay(0.75);
    motor_1.run(0);
    motor_2.run(0);
    motor_9.run(200);
    motor_10.run(200);
    while(robapresa==0){
    if((ultrasonic_8.distanceCm()) > (0)){
        motor_9.run(0);
        motor_10.run(0);
        motor_1.run(0);
        motor_2.run(0);
        robapresa=1
    }
    }
}

void loop(){
    _loop();
}

void _delay(float s){
    long fine = millis() + s * 1000;
    while(millis() < fine)_loop();
}

void _loop(){
}
