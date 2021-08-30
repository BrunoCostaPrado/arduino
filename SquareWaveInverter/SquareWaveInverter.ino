bool state = 0;

void setup() {
  Serial.begin(115200);
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B = (1 << WGM12) | (1 << CS11);
  TIMSK1 = 0;
  TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);
  OCR1A = 20000;
  OCR1B = 6000;
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
}

ISR(TIMER1_COMPA_vect) {
  off();
  state = !state;
}

ISR(TIMER1_COMPB_vect) {
  if (state == 0) {
    highon();
  }
  else {
    lowon();
  }
}

void loop() {
}

void off() {
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
}

void highon() {
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}

void lowon() {
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}
