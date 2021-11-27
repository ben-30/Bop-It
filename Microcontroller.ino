#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

//If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#define SSD1306_LCDHEIGHT 64
#if (SSD1306_LCDHEIGHT != 64)
#error ("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  //pin mapping
  pinMode(0, INPUT);  //power
  pinMode(1, INPUT);  //start
  pinMode(2, OUTPUT); //green
  pinMode(3, OUTPUT); //yellow
  pinMode(4, OUTPUT); //red
  pinMode(5, INPUT);  //hand brake
  pinMode(6, INPUT);  //hand brake
  pinMode(7, INPUT);  //potentiometer
  pinMode(8, INPUT);  //push button

  //LCD code
  Serial.begin(9600);
  //by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  //init done

  //clear the buffer
  display.clearDisplay();
}

void loop() {
  
  //TODO: while (digitalRead(0) == HIGH) - POWER
  //TODO: if (digitalRead(1) == HIGH) - START
  int timer = 5000;
  int score = 0;
  
  while (true) {

    //reset after each command
    bool correct = false;
    int current_turn = get_current_turn();
    int current_brake = get_current_brake();
  
    //choose command --> honk = 1, turn = 2, brake = 3
    int num_command = rand() % 3 + 1; //random
    //int num_command = 1; //manually set for testing

    //display chosen command
    String display_command = get_string(num_command);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(display_command);
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.display();

    //turn yellow on
    digitalWrite(3, HIGH);

    //check if input is correct or incorrect (or time-out)
    correct = command(timer, num_command, current_turn, current_brake);

    //turn yellow off
    digitalWrite(3, LOW);

    //clear display
    display.clearDisplay();

    if (correct) {
      //turn green on
      digitalWrite(2, HIGH);
      
      //display success
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Nice Job!");
      display.setTextColor(BLACK, WHITE); // 'inverted' text
      display.display();
      delay(2000);
      display.clearDisplay();

      //increment score, decrement time
      score++;
      timer -= 50;

      //turn green off
      digitalWrite(2, LOW);
      delay(1000);
    } else {
      //turn red on
      digitalWrite(4, HIGH);
      
      //display fail
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("You Lose!");
      display.setTextColor(BLACK, WHITE); // 'inverted' text
      display.display();
      delay(2000);
      display.clearDisplay();

      //display final score
      display.println("Score:");
      display.display();
      delay(2000);
      display.clearDisplay();
      display.write(score);
      delay(2000);
      display.clearDisplay();

      //turn red off
      digitalWrite(4, LOW); 
      
      //TODO: end game
      delay(1000);
    }
  }

  //TODO: if (score == 99) end game;
}

//check if potentiometer is high or low
int get_current_turn() {
  return (digitalRead(7) == HIGH) ? 1 : 0;
}

//check how the handbrake is oriented
int get_current_brake() {
  if ( digitalRead(5) == HIGH ) {
    return 5;
  } else if ( digitalRead(6) == HIGH ) {
    return 6;
  } else {
    return 5;
  }
}

//get string to display for command
String get_string(int num_command) {
    string return_string = "";
    
    switch (num_command) {
      case 1:
        return_string = "Honk It!";
        break;
      case 2:
        return_string = "Turn It!";
        break;
      case 3:
        return_string = "Brake It!";
        break;
    }

    return return_string;
}

//true if correct input
//false if incorrect input or time-out
int command(int timer, int num_command, int previous_turn, int previous_brake) {
  int count = 0;
  
  while (count<timer) {
    bool did_honk = check_honk();
    bool did_turn = check_turn(previous_turn);
    bool did_brake = check_brake(previous_brake);

    //check all inputs, only want desired command input to be true
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

  return false; //time runs out
}

//true if button pressed
//looking for high reading
bool check_honk() {
  return digitalRead(8) == HIGH ? true : false;
}

//true if wheel turned to opposite direction
//looking for change in potentiometer reading
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

//true if handbrake changes orientation
//looking for change in which digital pin high
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
