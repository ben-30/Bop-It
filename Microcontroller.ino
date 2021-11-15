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

void loop() {
  
  //while (digitalRead(0) == HIGH) - POWER
  
  while (true) {

    //if (digitalRead(1) == HIGH) - START
    
    //int score = 0
  
    //reset after each command
    bool brake_success = false;
    bool turn_success = false;
    bool honk_success = false;

    int current_turn = ( (digitalRead(7) == HIGH) ? 1 : 0 );
    int current_brake = 0;
    if ( digitalRead(5) == HIGH ) {
      current_brake = 5;
    } else if ( digitalRead(6) == HIGH ) {
      current_brake = 6;
    }
  
    //time to perform command
    int timer = 20;
  
    //choose command
    //int random = rand() % 3 + 1;
    int random = 1;
  
    //turn yellow light on

    honk_success = honk_it(timer);
    turn_success = turn_it(timer, current_turn);
    brake_success = brake_it(timer, current_brake);

    bool correct = false;
  
    switch (random) {
      case 1:
        if ( honk_success == true ) { correct = true; }
        if ( turn_success == true || brake_success == true ) { correct = false; }
        break;
      case 2:
        if ( turn_success == true ) { correct = true; }
        if ( honk_success == true || brake_success == true ) { correct = false; }
        break;
      case 3:
        if ( brake_success == true ) { correct = true; }
        if ( honk_success == true || turn_success == true ) { correct = false; }
        break;
    }
  
    //turn yellow light off
  
    /*if (correct == true) {
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
    if (digitalRead(8) == HIGH) 
      return true;
    delay(1);
    count++;
  }

  return false;
}

bool turn_it(int timer, int previous_turn) {
  int count = 0;
  while (count<timer) {
    switch (previous_turn) {
      case 0:
        if (digitalRead(7) == HIGH) {
          return true;
        }
      case 1:
        if (digitalRead(7) == LOW) {
          return true;
        }
    }
  
    delay(1);
    count++;
  }

  return false;
}

bool brake_it(int timer, int previous_brake) {
  int count = 0;
  while (count<timer) {
    switch (previous_brake) {
      case 6:
        if (digitalRead(5) == HIGH) {
          return true;
        }
      case 5:
        if (digitalRead(6) == HIGH) {
          return true;
        }
    }
  
    delay(1);
    count++;
  }

  return false;
}
