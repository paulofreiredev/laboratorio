#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Botões
#define BTN_LEFT  3
#define BTN_UP    4
#define BTN_DOWN  5
#define BTN_RIGHT 6

// Buzzer
#define BUZZER 9

// Tamanho do grid
#define CELL_SIZE 4
#define GRID_W (SCREEN_WIDTH / CELL_SIZE)
#define GRID_H (SCREEN_HEIGHT / CELL_SIZE)

struct Point {
  int x;
  int y;
};

Point snake[100];
int snakeLength = 5;

enum Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN
};

Direction dir = RIGHT;

Point food;

unsigned long lastMove = 0;
const int gameSpeed = 120;

bool gameOver = false;

void playStartupTune() {
  int melody[] = {
    523, 659, 784, 1047,
    784, 659, 523,
    659, 784, 988, 1319
  };

  int duration[] = {
    120,120,120,180,
    120,120,180,
    120,120,120,250
  };

  for (int i = 0; i < 11; i++) {
    tone(BUZZER, melody[i], duration[i]);
    delay(duration[i] + 20);
  }

  noTone(BUZZER);
}

void eatSound() {
  tone(BUZZER, 1000, 60);
  delay(70);
  tone(BUZZER, 1500, 60);
}

void gameOverSound() {
  int notes[] = {700, 600, 500, 400, 300, 200};

  for (int i = 0; i < 6; i++) {
    tone(BUZZER, notes[i], 120);
    delay(130);
  }

  noTone(BUZZER);
}

void spawnFood() {
  bool valid;

  do {
    valid = true;

    food.x = random(0, GRID_W);
    food.y = random(0, GRID_H);

    for (int i = 0; i < snakeLength; i++) {
      if (snake[i].x == food.x &&
          snake[i].y == food.y) {
        valid = false;
      }
    }
  } while (!valid);
}

void drawGame() {
  display.clearDisplay();

  // comida
  display.fillRect(
    food.x * CELL_SIZE,
    food.y * CELL_SIZE,
    CELL_SIZE,
    CELL_SIZE,
    SSD1306_WHITE
  );

  // cobra
  for (int i = 0; i < snakeLength; i++) {
    display.drawRect(
      snake[i].x * CELL_SIZE,
      snake[i].y * CELL_SIZE,
      CELL_SIZE,
      CELL_SIZE,
      SSD1306_WHITE
    );
  }

  display.display();
}

void resetGame() {
  snakeLength = 5;

  snake[0] = {10, 4};
  snake[1] = {9, 4};
  snake[2] = {8, 4};
  snake[3] = {7, 4};
  snake[4] = {6, 4};

  dir = RIGHT;
  gameOver = false;

  spawnFood();
}

void readButtons() {
  if (digitalRead(BTN_LEFT) == LOW && dir != RIGHT)
    dir = LEFT;

  if (digitalRead(BTN_RIGHT) == LOW && dir != LEFT)
    dir = RIGHT;

  if (digitalRead(BTN_UP) == LOW && dir != DOWN)
    dir = UP;

  if (digitalRead(BTN_DOWN) == LOW && dir != UP)
    dir = DOWN;
}

void moveSnake() {
  Point newHead = snake[0];

  switch (dir) {
    case LEFT:
      newHead.x--;
      break;

    case RIGHT:
      newHead.x++;
      break;

    case UP:
      newHead.y--;
      break;

    case DOWN:
      newHead.y++;
      break;
  }

  // colisão parede
  if (newHead.x < 0 ||
      newHead.x >= GRID_W ||
      newHead.y < 0 ||
      newHead.y >= GRID_H) {

    gameOver = true;
    gameOverSound();
    return;
  }

  // colisão consigo mesma
  for (int i = 0; i < snakeLength; i++) {
    if (snake[i].x == newHead.x &&
        snake[i].y == newHead.y) {

      gameOver = true;
      gameOverSound();
      return;
    }
  }

  // move corpo
  for (int i = snakeLength; i > 0; i--) {
    snake[i] = snake[i - 1];
  }

  snake[0] = newHead;

  // comeu
  if (newHead.x == food.x &&
      newHead.y == food.y) {

    snakeLength++;

    if (snakeLength > 99)
      snakeLength = 99;

    eatSound();
    spawnFood();
  }
}

void showGameOver() {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println("GAME");

  display.setCursor(10, 16);
  display.println("OVER");

  display.display();

  delay(2000);

  resetGame();
}

void showSplashScreen() {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 8);
  display.println("SnakeGame");

  display.display();

  playStartupTune();

  delay(2000);
}

void setup() {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  randomSeed(analogRead(A0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  showSplashScreen();

  resetGame();
}

void loop() {
  if (gameOver) {
    showGameOver();
    return;
  }

  readButtons();

  if (millis() - lastMove > gameSpeed) {
    lastMove = millis();

    moveSnake();
    drawGame();
  }
}
