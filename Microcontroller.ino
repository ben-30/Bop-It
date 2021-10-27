void setup() {
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  
  bool honking = false; 
  bool turning = false;
  bool braking = false;

  int timer = 20;

  honking = honk_it(timer);
  digitalWrite(0, (honking ? HIGH : LOW));
  turning = turn_it(timer);
  digitalWrite(1, (turning ? HIGH : LOW));
  braking = brake_it(timer);
  digitalWrite(2, (braking ? HIGH : LOW));
}

bool honk_it(int timer) {
  digitalWrite(8, HIGH);

  int count = 0;
  while (count<timer) {
    if (digitalRead(9) == HIGH) { return true; }
    delay(1);
    count++;
  }

  return false;
}

bool turn_it(int timer) {
  digitalWrite(7, HIGH);

  int count = 0;
  while (count<timer) {
    if (digitalRead(10) == HIGH) { return true; }
    delay(1);
    count++;
  }

  return false;
}

bool brake_it(int timer) {
  digitalWrite(6, HIGH);

  int count = 0;
  while (count<timer) {
    if (digitalRead(11) == HIGH) { return true; }
    delay(1);
    count++;
  }

  return false;
}
