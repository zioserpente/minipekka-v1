#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeOrion.h>
MeDCMotor motor_9(9);//motore di destra
MeDCMotor motor_10(10);//motore di sinistra
MeDCMotor motor_1(1);//motore stringimento (potenza negativa->allarga, potenza positiva-> stringe)
MeDCMotor motor_2(2);//motore alzata (potenza negativa->si abbassa, potenza positiva-> si alza)
MeUltrasonicSensor ultrasonic_8(8); //sensore ultrasuoni, per rilevare gli ostacoli

void setup(){
    int robapresa=0;
    resetbraccio();
    motor_9.run(150);
    motor_10.run(150);
    while(robapresa==0){
    if((ultrasonic_8.distanceCm()) < (16)){
        motor_9.run(0);
        motor_10.run(0);
        motor_1.run(100);
        motor_2.run(-100);
        _delay(1);
        motor_1.run(0);
        motor_2.run(0);
        robapresa=1;
    }
    }
}
void resetbraccio(){
    motor_1.run(-120);
    motor_2.run(100);
    _delay(1);
    motor_1.run(0);
    motor_2.run(0);
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
