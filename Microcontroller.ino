void setup() {
  //bottom right pins
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  //bottom left pins
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  //top left pins
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  //reset pins after each command
  for (int pin=6; pin<=8; pin++) 
    digitalWrite(pin, LOW);

  //reset actions after each command
  bool honking, turning, braking = false;

  //time to perform command
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
    if (digitalRead(9) == HIGH) 
      return true;
    delay(1);
    count++;
  }

  return false;
}

bool turn_it(int timer) {
  digitalWrite(7, HIGH);

  int count = 0;
  while (count<timer) {
    if (digitalRead(10) == HIGH)
      return true;
    delay(1);
    count++;
  }

  return false;
}

bool brake_it(int timer) {
  digitalWrite(6, HIGH);

  int count = 0;
  while (count<timer) {
    if (digitalRead(11) == HIGH)
      return true;
    delay(1);
    count++;
  }

  return false;
}
