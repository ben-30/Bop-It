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
  //while (on_button == true)

  //int score = 0
  
  //reset pins after each command
  for (int pin=6; pin<=8; pin++) 
    digitalWrite(pin, LOW);

  //reset after each command
  bool action_success = false;

  //time to perform command
  int timer = 20;

  //choose command
  //int random = rand() % 3 + 1;
  int random = 1;

  //turn yellow light on

  switch (random) {
    case 1;
      action_success = honk_it(timer);
      digitalWrite(0, (action_success ? HIGH : LOW));
      break;
    case 2;
      action_success = turn_it(timer);
      digitalWrite(1, (action_success ? HIGH : LOW));
      break;
    case 3;
      action_success = brake_it(timer);
      digitalWrite(2, (action_success ? HIGH : LOW));
      break;
  }

  //turn yellow light off

  /*if (action_success == true) {
    green light
    tell user they succeeded
    score++
    timer--
  } else {
    red light
    tell user they failed
  }*/
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
