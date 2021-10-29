void setup() {
  //drive output per command
  pinMode(8, OUTPUT);
  
  //check input per command
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  //LED screen
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  //power button, start button
  pinMode(0, INPUT);
  pinMode(1, INPUT);

  //green, yellow, red
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  //while (digitalRead(0) == HIGH) - POWER
  while (true) {

    //if (digitalRead(1) == HIGH) - START
    
    //int score = 0

    digitalWrite(8, HIGH);
  
    //reset after each command
    bool action_success = false;
  
    //time to perform command
    int timer = 20;
  
    //choose command
    //int random = rand() % 3 + 1;
    int random = 1;
  
    //turn yellow light on
  
    switch (random) {
      case 1:
        action_success = honk_it(timer);
        digitalWrite(2, (action_success ? HIGH : LOW));
        break;
      case 2:
        action_success = turn_it(timer);
        digitalWrite(3, (action_success ? HIGH : LOW));
        break;
      case 3:
        action_success = brake_it(timer);
        digitalWrite(4, (action_success ? HIGH : LOW));
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

  //if (score == 99) end game;
}

bool honk_it(int timer) {
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
  int count = 0;
  while (count<timer) {
    if (digitalRead(11) == HIGH)
      return true;
    delay(1);
    count++;
  }

  return false;
}
