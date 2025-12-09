#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeOrion.h>
MeDCMotor motor_9(9);//motore di destra
MeDCMotor motor_10(10);//motore di sinistra
MeDCMotor motor_1(1);//motore stringimento (potenza negativa->allarga, potenza positiva-> stringe)
MeDCMotor motor_2(2);//motore alzata (potenza negativa->si abbassa, potenza positiva-> si alza)
MeUltrasonicSensor ultrasonic_8(8); //sensore ultrasuoni, per rilevare gli ostacoli
MeLineFollower linefollower_6(6);   //sensore per seguire il percorso dato (se )

void setup(){
    int robapresa=0;
    resetbraccio();
    motor_9.run(120);
    motor_10.run(120);
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
    }}
    motor_9.run(150);
    // motor_10.run(-100);
    _delay(0.75);
    motor_10.run(150);
    while (robapresa==1)
    {
        switch (linefollower_6.readSensors())
        {
        case 3://lato destro e sinistro del sensore sono su colore bianco, il robot si ferma
            motor_9.run(0);
            motor_10.run(0);
            break;
        case 2: //girare a destra
            motor_9.run(0);
            motor_10.run(80);
            break;
        case 1: //girare a sinistra
            motor_9.run(80);
            motor_10.run(0);
            break;
        default: //in qualsiasi altro caso il robot va avanti
            motor_9.run(120);
            motor_10.run(120);
            break;
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
void loop(){_loop();}

void _delay(float s){
    long fine = millis() + s * 1000;
    while(millis() < fine)_loop();
}

void _loop(){}