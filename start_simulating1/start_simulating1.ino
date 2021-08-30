#define led_1 13
#define chave 9
#define ON HIGH
#define OFF LOW

void setup()
{
  pinMode(led_1, OUTPUT);
  pinMode(chave, INPUT);
}

void loop()
{
if(chave==true){
  digitalWrite(led_1, ON);
}
  else if
(digitalWrite)(led_1, OFF);
}
