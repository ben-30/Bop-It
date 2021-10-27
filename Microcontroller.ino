void setup() {
  pinMode(9, INPUT);
  pinMode(8, OUTPUT);
  pinMode(0, OUTPUT);
}

void loop() {
  bool pressed = honk_it();
  if (pressed) {
    digitalWrite(0, HIGH);
  }
}

bool honk_it() {
  digitalWrite(8, HIGH);

  int count = 0;
  while (count<500) {
    if (digitalRead(9) == HIGH) {
      return true;
    }
    count++;
  }

  return false;
}
