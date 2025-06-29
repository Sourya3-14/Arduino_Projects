#include<SPI.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>

Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1);

#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define BUZZER_PIN 2

#define SNAKE_MAX_LENGTH 16
int snake_x[16];
int snake_y[16];
int snake_length = 2;
int score = 0;
int snake_dir = 0;  // 0 = right, 1 = up, 2 = left, 3 = down
int food_x;
int food_y;
int i=0;

void setup() {
  display.begin(0x3c);
  display.clearDisplay();
  display.display();

  pinMode(BUZZER_PIN, OUTPUT);

  //randomSeed(analogRead(0));
  food_x = random(0, display.width() / 8);
  food_y = random(0, display.height() / 8);

  snake_x[0] = 0;
  snake_y[0] = 0;
  snake_x[1] = 1;
  snake_y[1] = 0;

  drawSnake();
  drawFood();
}

void loop() {
  delay(80);

  //Joystick Control
  int xVal = analogRead(JOYSTICK_X);
  int yVal = analogRead(JOYSTICK_Y);

  if (xVal > 850 && snake_dir != 2) {  // Right
    snake_dir = 0;
  } else if (xVal < 150 && snake_dir != 0) {  // Left
    snake_dir = 2;
  } else if (yVal > 850 && snake_dir != 1) {  // Down
    snake_dir = 3;
  } else if (yVal < 150 && snake_dir != 3) {  // UP
    snake_dir = 1;
  }
  for (int i =snake_length - 1;i>0; i--) {
    snake_x[i] = snake_x[i-1];
    snake_y[i] = snake_y[i-1];
  }

  switch (snake_dir) {
    case 0:
      snake_x[0]++;
      break;
    case 1:
      snake_y[0]--;
      break;
    case 2:
      snake_x[0]--;
      break;
    case 3:
      snake_y[0]++;
      break;
  }

  if (snake_x[0] < 0) {
    snake_x[0] = display.width() / 8 - 1;
  }
  else if (snake_x[0] >= display.width() / 8) {
    snake_x[0] = 0;
  }

  if (snake_y[0] < 0) {
    snake_y[0] = display.height() / 8 - 1;
  } 
  else if (snake_y[0] >= display.height() / 8) {
    snake_y[0] = 0;
  }

  //Eat Apple
  if (snake_x[0] == food_x && snake_y[0] == food_y) {
    if ( snake_length < 16) {
      snake_length++;
    }
    i++;
    if(i!=5){
     score = score + 1;
    }
    if(i==5){
      score=score+5;
      i=0;
    }
    digitalWrite(BUZZER_PIN, HIGH);
    delay(10);
    digitalWrite(BUZZER_PIN, LOW);

    food_x = random(0, display.width() / 8);
    food_y = random(0, display.height() / 8);
  }

  for (int i = 1; i < snake_length; i++) {
    if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
      gameOver();
      Reset();
    }
  }

  display.clearDisplay();
  drawSnake();
  if(i!=5){
    drawFood();
  }
  if(i==4){
    DrawFood();
  }
  display.display();
}

void drawSnake() {

  for (int i = 0; i < snake_length; i++) {
    display.fillRect(snake_x[i] * 8, snake_y[i] * 8, 7, 7, SH110X_WHITE);
  }
}

void drawFood() {
  display.fillRect(food_x * 8, food_y * 8, 5, 5, SH110X_WHITE);
}

void DrawFood() {
  display.fillRect(food_x * 8, food_y * 8, 8, 8, SH110X_WHITE);
}

void gameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(5, 20);
  display.println("Game Over!");
  display.setCursor(15, 40);
  display.print("Score: ");
  display.println(score);
  display.display();
  delay(3000);
}

void Reset() {
  score = 0;
  food_x = random(0, display.width() / 8);
  food_y = random(0, display.height() / 8);
  snake_length = 2;
  snake_dir = 0;  // 0 = right, 1 = up, 2 = left, 3 = down
  snake_x[0] = 0;
  snake_y[0] = 0;
  snake_x[1] = 1;
  snake_y[1] = 0;
}

