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
  //if (digitalRead(1) == HIGH) - START
  //int score = 0
  int timer = 2500;
  
  while (true) {

    //reset after each command
    int current_turn = 0;
    int current_brake = 0;
    bool correct = false;
    
    current_turn = ( (digitalRead(7) == HIGH) ? 1 : 0 );
    
    if ( digitalRead(5) == HIGH ) {
      current_brake = 5;
    } else if ( digitalRead(6) == HIGH ) {
      current_brake = 6;
    } else {
      current_brake = 5;
    }
  
    //choose command
    //int num_command = rand() % 3 + 1;
    int num_command = 1;
  
    digitalWrite(3, HIGH); //turn yellow on

    correct = command(timer, num_command, current_turn, current_brake);
  
    digitalWrite(3, LOW); //turn yellow off
  
    if (correct) {
      digitalWrite(2, HIGH); //turn green on
      delay(1000);
      //tell user they succeeded
      //score++;
      //timer--;
      digitalWrite(2, LOW); //turn green off
      delay(1000);
    } else {
      digitalWrite(4, HIGH); //turn red on
      delay(1000);
      //tell user they failed
      //end game
      //report score
      digitalWrite(4, LOW); //turn red off
      delay(1000);
    }
  }

  //if (score == 99) end game;
}

int command(int timer, int num_command, int previous_turn, int previous_brake) {
  //num_command --> honk = 1, turn = 2, brake = 3
  int count = 0;
  
  while (count<timer) {
    bool did_honk = check_honk();
    bool did_turn = check_turn(previous_turn);
    bool did_brake = check_brake(previous_brake);
    
    switch (num_command) {
      case 1:
        if ( did_honk == true ) { return true; }
        if ( did_turn == true || did_brake == true ) { return false; }
        break;
      case 2:
        if ( did_turn == true ) { return true; }
        if ( did_honk == true || did_brake == true ) { return false; }
        break;
      case 3:
        if ( did_brake == true ) { return true; }
        if ( did_honk == true || did_turn == true ) { return false; }
        break;
    }
    
    delay(1);
    count++;
  }
}

bool check_honk() {
  return digitalRead(8) == HIGH ? true : false;
}

bool check_turn(int previous_turn) {
  switch (previous_turn) {
      case 0:
        if (digitalRead(7) == HIGH)
          return true;
        break;
      case 1:
        if (digitalRead(7) == LOW)
          return true;
        break;
   }

   return false;
}

bool check_brake(int previous_brake) {
  switch (previous_brake) {
    case 6:
      if (digitalRead(5) == HIGH)
        return true;
      break;
    case 5:
      if (digitalRead(6) == HIGH)
        return true;
      break;
  }

  return false;
}
