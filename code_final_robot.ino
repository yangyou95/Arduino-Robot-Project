#include "DualMC33926MotorShield.h"
#include <math.h>
DualMC33926MotorShield moteur;
int servoPin = 6;  
float val=0;//Pour La Capteur
char GP2D12;//Pour La Capteur
char a,b;// Pour La Capteur
float fd=0,ld=0,rd;//fd=front distance ld=left distance rd=right distance

void setup() {
  pinMode(servoPin, OUTPUT); //  Define OUTPUT de la servomoteur
    Serial.begin(9600);
     moteur.init();

}
void forward()
{
   moteur.setM1Speed(200);
 delay(1000);
 moteur.setM2Speed(200);
 delay(1000);
}
void Gauche()
{
     moteur.setM1Speed(0);
 delay(1000);
 moteur.setM2Speed(150);
 delay(60);
}

void Droite()
{
     moteur.setM1Speed(150);
 delay(60);
 moteur.setM2Speed(0);
 delay(1000);
}

void arrete()
{
     moteur.setM1Speed(0);
 delay(1000);
 moteur.setM2Speed(0);
 delay(1000);
}


void servo(int angle) { //define un fonction pour servomoteur tourner certain l'angle
  

    int pulsewidth = (angle * 11) + 500;
    digitalWrite(servoPin, HIGH);  
    delayMicroseconds(pulsewidth);   
    digitalWrite(servoPin, LOW);    
    delayMicroseconds(20000 - pulsewidth);  
    delay(100);  
}  

float mesure() //define un fonction pour la capteur mesure la distance
   
{
   
   float tmp;
   
   tmp = analogRead(A0);
   
   tmp=tmp*4/1024;   
   
   tmp=8.7328*pow(tmp,-0.912)+0.25;    // fonction pour calculer la distance
   

   
   return tmp;
   
}



void loop() {
  for(int i=0;i<50;i++) { //donne 50 implusations

    servo(90);  //tourner devant
    delay(200);
    fd=mesure();//mesure la distance devant
    Serial.print("DISTANCE AVANT=");
    Serial.println(fd);
    delay(2000);
       if(fd<=20)
       {
        arrete();
        delay(500);
        servo(50); //servo tourner a droite
        delay(500);
        rd=read_gp2d12_range();//mesure la distance de droite
        Serial.print("DISTANCE DROITE=");
        Serial.println(rd);
        delay(500);
        servo(130);//tourner a gauche
        delay(500);
        ld=read_gp2d12_range();//mesure la distance de gauche
        Serial.print("DISTANCE GAUCHE=");
        Serial.println(ld);
        delay(500);
        servo(90);//servo retourner la avant

 //Partie controle la movement     
         if(rd>ld)
         {
          Droite();
          delay(450);//TESTE
         }
         else if(ld>rd)
         {
          Gauche();
          delay(450);//TESTE
         }
         else
         {
          forward();
         }
         }
         else
         forward();
    
}}
