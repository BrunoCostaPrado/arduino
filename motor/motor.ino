#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Stepper.h>

char auth[] = "hmhrU6DSpBKi0NS01ag919tQFqDJQkEU";
char ssid[] = "Fatte";
char pass[] = "dedonocuegritaria";
const int stepsPerRevolution = 200; 
Stepper myStepper(stepsPerRevolution, 16, 13, 15, 10);
int xVal=512;

BlynkTimer timer;

const byte L298N_A_pin = D1; // GPI05
const byte L298N_A_In1_pin = D2; //GPI04
const byte L298N_A_In2_pin = D3; //GPI0

const byte L298N_B_In3_pin = D4; // GPI02
const byte L298N_B_In4_pin = D5; // GPIO14
const byte L298N_B_pin = D6; //GPI12

const byte Korna_pin = D0; //GPI016  //Korna

WidgetLED led1(V1); //Sol
WidgetLED led2(V2); //Sag
WidgetLED led3(V3); //A1
WidgetLED led4(V4); //B1
WidgetLED led5(V5); //Far
WidgetLED led6(V6); //Arka 
WidgetLED led7(V7); //A2
WidgetLED led8(V8); //B2

byte SolSinyal = 0;
byte SagSinyal = 0;
byte ArkaLamba = 0;
int param=0;



void setup() {
   
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);
BLYNK_WRITE(V10);
/* Korna*/  
  digitalWrite(Korna_pin,param.asInt());



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

  
  if( (xVal < 500)  ){
     myStepper.step(1);
     delayMicroseconds(3000);
  }else if( xVal > 550){
     myStepper.step(-1);
     delayMicroseconds(3000);
  }

  
}
BLYNK_WRITE(V1)
{
  xVal = param[0].asInt();
 // int y = param[1].asInt();    
}
BLYNK_WRITE(V2)
{
   if( param.asInt() == 1){
        xVal = 0;
   }else{
        xVal = 512;
   }
}
BLYNK_WRITE(V3)
{
   if( param.asInt() == 1){
        xVal = 1000;
   }else{
        xVal = 512;
   }
}
