#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Stepper.h>

char auth[] = "hmhrU6DSpBKi0NS01ag919tQFqDJQkEU";
char ssid[] = "Fatte";
char pass[] = "dedonocuegritaria";
const int stepsPerRevolution = 200; 

BlynkTimer timer;

const byte L298N_A_pin = D1; // GPI05
const byte L298N_A_In1_pin = D2; //GPI04
const byte L298N_A_In2_pin = D3; //GPI0

const byte L298N_B_In3_pin = D4; // GPI02
const byte L298N_B_In4_pin = D5; // GPIO14
const byte L298N_B_pin = D6; //GPI12
const byte Korna_pin = D0; //GPI016  //Korna

byte SolSinyal = 0;
byte SagSinyal = 0;
byte ArkaLamba = 0;
/*
 * blynk ekranı
 * V0 joystick,  
 * v1,v2, v3, v4,v5,v6,v7,v8 Led  
 * v10  button push
 * v11 button switch
 */
int param=0;



void setup() {
   
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);
BLYNK_WRITE(V10);
/* Korna*/  
  digitalWrite(Korna_pin,param.asInt());
  BLYNK_WRITE(V11) {
/* On Far*/  
  digitalWrite(Led3_pin,param.asInt());
}



void motorSpeed(int prmA, byte prmA1, byte prmA2, int prmB, byte prmB1, byte prmB2)
  analogWrite(L298N_A_pin,prmA);
  analogWrite(L298N_B_pin,prmB);
  
  digitalWrite(L298N_A_In1_pin,prmA1);
  digitalWrite(L298N_A_In2_pin,prmA2);
  digitalWrite(L298N_B_In3_pin,prmB1);
  digitalWrite(L298N_B_In4_pin,prmB2);
}

BLYNK_WRITE(V0) 
  int x = param[0].asInt();
  int y = param[1].asInt();
// x =  -2 -1 0 1 2 
// Y =  -2 -1 0 1 2
 if ((x==0) && (y==0)) // duruyor
 {
   motorSpeed(0,LOW,LOW,0,LOW,LOW); 
   SolSinyal = 0;
   SagSinyal = 0;
   digitalWrite(Led1_pin,LOW);
   digitalWrite(Led2_pin,LOW);
 }
 else if ((x==0) && (y>0)) // düz ileri 
 {
  if (y==1){ motorSpeed(900,HIGH,LOW,900,HIGH,LOW); }
  else { motorSpeed(1023,HIGH,LOW,1023,HIGH,LOW); }
  SolSinyal = 0;
  SagSinyal = 0;
 }
 else if ((y==0) && (x>0))// Tam Sag donuş
 { 
  motorSpeed(900,HIGH,LOW,900,LOW,HIGH); 
  SagSinyal = 1;
  }
 else if ((y>0) && (x>0))// Sag donuş
 {  
  motorSpeed(1023,HIGH,LOW,900,LOW,LOW); 
  SagSinyal = 1;
  }
 else if ((y==0) && (x<0))// Tam sola donuş
 { 
  motorSpeed(900,LOW,HIGH,900,HIGH,LOW); 
  SolSinyal = 1;
  }
 else if ((y>0) && (x<0))// Sola donuş
 {   
  motorSpeed(900,LOW,LOW,1023,HIGH,LOW); 
  SolSinyal = 1;
  }
  
 if ((y<0) && (x<0))// Sola geri
    motorSpeed(900,LOW,LOW,1023,LOW,HIGH); 
 else if ((y<0) && (x>0))// Sag geri
    motorSpeed(1023,LOW,HIGH,900,LOW,LOW); 
 else if ((y<0) && (x==0))// tam geri
   motorSpeed(900,LOW,HIGH,900,LOW,HIGH); 

}

void setup() {
  Serial.begin(115200);
  pinMode(L298N_A_In1_pin,OUTPUT);
  pinMode(L298N_A_In2_pin,OUTPUT);
  pinMode(L298N_B_In3_pin,OUTPUT);
  pinMode(L298N_B_In4_pin,OUTPUT);

 digitalWrite(L298N_A_In1_pin,LOW);
 digitalWrite(L298N_A_In2_pin,LOW);
 digitalWrite(L298N_B_In3_pin,LOW);
 digitalWrite(L298N_B_In4_pin,LOW);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendTemps);
  
  
}
void sendTemps()

void loop() {
  Blynk.run();
  timer.run();

  
}
