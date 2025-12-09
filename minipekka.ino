#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeOrion.h>
#include <EEPROM.h>

MeDCMotor motor_9(9);//motore di destra
MeDCMotor motor_10(10);//motore di sinistra
MeDCMotor motor_1(1);//motore stringimento braccio (potenza negativa->allarga, potenza positiva-> stringe)
MeDCMotor motor_2(2);//motore alzata braccio (potenza negativa->si abbassa, potenza positiva-> si alza)
MeUltrasonicSensor ultrasonic_8(8); //sensore ultrasuoni, per rilevare gli ostacoli
MeLineFollower linefollower_6(6);   //sensore per seguire il percorso dato (se presente)

void setup(){
    int robapresa=EEPROM.read(0);
    if(robapresa==0){resetbraccio();}
    motor_9.run(120);
    motor_10.run(120);
    while(1){
        switch (linefollower_6.readSensors())
        {
        case 3://lato destro e sinistro del sensore sono su colore bianco, il robot si ferma
            motor_9.run(0);
            motor_10.run(0);
            if(robapresa==1){
                resetbraccio();
                robapresa=0;
                EEPROM.write(0, robapresa);
            }
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
        if((ultrasonic_8.distanceCm()) < (16) && robapresa==0){
            motor_9.run(0);
            motor_10.run(0);
            motor_1.run(120);
            motor_2.run(-100);
            _delay(1);
            motor_1.run(0);
            motor_2.run(0);
            robapresa=1;
            EEPROM.write(0, robapresa);
        }
    }
}

void resetbraccio(){//resetta il braccio, allargando il braccio e alzandolo
    motor_1.run(-120);
    motor_2.run(120);
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
