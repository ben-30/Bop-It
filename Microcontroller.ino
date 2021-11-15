void setup() {
  pinMode(0, INPUT);  //power
  pinMode(1, INPUT);  //start
  pinMode(2, OUTPUT); //green
  pinMode(3, OUTPUT); //yellow
  pinMode(4, OUTPUT); //red
  pinMode(5, INPUT);  //hand brake
  pinMode(6, INPUT);  //hand brake
  pinMode(7, INPUT);  //potentiometer
  pinMode(8, INPUT);  //push button
  
  //////////LCD Stuff//////////
}

//int previous_turn;

void loop() {
  //0 turned to left, 1 turned to right
  previous_turn = (digitalRead(10) == HIGH ? 1 : 0);
  
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
    int random = 2;
  
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
    switch (previous_turn) {
      case 0:
        if (digitalRead(10) == HIGH) {
          previous_turn = 1;
          return true;
        }
      case 1:
        if (digitalRead(10) == LOW) {
          previous_turn = 0;
          return true;
        }
    }
  
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
