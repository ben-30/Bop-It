#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
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
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  //Pin mapping
  pinMode(0, INPUT);  //power
  pinMode(1, INPUT);  //start
  pinMode(2, OUTPUT); //green
  pinMode(3, OUTPUT); //yellow
  pinMode(4, OUTPUT); //red
  pinMode(5, INPUT);  //hand brake
  pinMode(6, INPUT);  //hand brake
  pinMode(7, INPUT);  //potentiometer
  pinMode(8, INPUT);  //push button

  //LCD Code
  Serial.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done

  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
  
  //while (digitalRead(0) == HIGH) - POWER
  //if (digitalRead(1) == HIGH) - START
  //int score = 0
  int timer = 5000;
  int score = 0;
  
  while (true) { //Change while(true) to while(cont) 

    //reset after each command
    int current_turn = 0;
    int current_brake = 0;
    bool honk_success = false;
    bool turn_success = false;
    bool brake_success = false;
    bool correct = false;
    
    current_turn = ( (digitalRead(7) == HIGH) ? 1 : 0 ); //Checks if pot is high or low

    //Checks how the handbrake is orierneted
    if ( digitalRead(5) == HIGH ) {
      current_brake = 5;
    } else if ( digitalRead(6) == HIGH ) {
      current_brake = 6;
    } else {
      current_brake = 5;
    }
  
    //choose command
    int random = rand() % 3 + 1;
    //int random = 1;

    String command = "";
    //Command string to display 
    switch(random){
      case 1:
        command = "Honk It!";
        break;
      case 2:
        command = "Turn It!";
        break;
      case 3:
        command = "Brake It!"; 
        break;
    }

    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(command);
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.display();
    //delay(2000);
    

  
    digitalWrite(3, HIGH); //turn yellow on
    

    //Calls functions
    int count=0;
    while(count<timer&&!(honk_success||turn_success||brake_success)){
      honk_success = honk_it(timer);
      turn_success = turn_it(timer, current_turn);
      brake_success = brake_it(timer, current_brake);
      delay(1);
      count++;
    }
    
    //Checks if the correct input is entered and the other two have not changed
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

    display.clearDisplay();
    digitalWrite(3, LOW); //turn yellow off
    
    if (correct == true) {
      digitalWrite(2, HIGH); //turn green on
      // Sucess LCD
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Nice Job!");
      display.setTextColor(BLACK, WHITE); // 'inverted' text
      display.display();
      delay(2000);
      display.clearDisplay();

      score++;
      timer -= 50;
      delay(1000);
    }else{
      digitalWrite(4, HIGH); //turn red on
      //Fail LED
      // text display tests
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("You Lose!");
      display.setTextColor(BLACK, WHITE); // 'inverted' text
      display.display();
      delay(2000);
      display.clearDisplay();

      display.println("Score:");
      display.display();
      delay(2000);
      display.clearDisplay();

      display.write(score);
      //display.display();
      delay(2000);
      display.clearDisplay();
      
      //end game
      //report score
      delay(1000);
    }
  
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    delay(1000);
  }

  //if (score == 99) end game;
}

bool honk_it(int timer) {
  int count = 0;
    if (digitalRead(8) == HIGH) 
      return true;
  return false;
}

bool turn_it(int timer, int previous_turn) {
  int count = 0;
    switch (previous_turn) { //Chooses case if pot is truned left or right
      case 0: //If pot was on left, check if it was turned right
        if (digitalRead(7) == HIGH) {
          return true;
        }
      case 1://If pot was on right, check if it was turned left
        if (digitalRead(7) == LOW) {
          return true;
        }
    }
  return false;
}

bool brake_it(int timer, int previous_brake) {
  int count = 0;
    switch (previous_brake) {
      case 6: //If switch was up, check if turned low
        if (digitalRead(5) == HIGH) {
          return true;
        }
      case 5: //If switch was low, check if turned high
        if (digitalRead(6) == HIGH) {
          return true;
        }
  }
  return false;
}
