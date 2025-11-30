#include <Arduino.h>

int joyX = A0;
int joyY = A1;
int joySW = A2;

int xValue = 0;
int yValue = 0;

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;

int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;

int hours = 12;
int minutes = 0;
bool settingMode = false;
int activeDigit = 0;
unsigned long lastUpdate = 0;

byte numbers[10][7] = {
  {0,0,0,0,0,0,1}, // 0
  {1,0,0,1,1,1,1}, // 1
  {0,0,1,0,0,1,0}, // 2
  {0,0,0,0,1,1,0}, // 3
  {1,0,0,1,1,0,0}, // 4
  {0,1,0,0,1,0,0}, // 5
  {0,1,0,0,0,0,0}, // 6
  {0,0,0,1,1,1,1}, // 7
  {0,0,0,0,0,0,0}, // 8
  {0,0,0,0,1,0,0}  // 9
};

void setup() 
{
  Serial.begin(9600);

  pinMode(joySW, INPUT_PULLUP);

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

void showDigit(int digit, int value) 
{

  digitalWrite(pinA, numbers[value][0] ? LOW : HIGH);
  digitalWrite(pinB, numbers[value][1] ? LOW : HIGH);
  digitalWrite(pinC, numbers[value][2] ? LOW : HIGH);
  digitalWrite(pinD, numbers[value][3] ? LOW : HIGH);
  digitalWrite(pinE, numbers[value][4] ? LOW : HIGH);
  digitalWrite(pinF, numbers[value][5] ? LOW : HIGH);
  digitalWrite(pinG, numbers[value][6] ? LOW : HIGH);

  if (digit == 0) digitalWrite(D1, LOW);
  if (digit == 1) digitalWrite(D2, LOW);
  if (digit == 2) digitalWrite(D3, LOW);
  if (digit == 3) digitalWrite(D4, LOW);

  delayMicroseconds(2000);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

void displayTime() 
{
  int d[4] = {
    hours / 10,
    hours % 10,
    minutes / 10,
    minutes % 10
  };

  for (int i = 0; i < 4; i++) {
    if (settingMode && i == activeDigit) {
      if ((millis() / 300) % 2 == 0) continue;
    }
    showDigit(i, d[i]);
  }
}

void updateClock() 
{
  if (millis() - lastUpdate >= 60000) {
    lastUpdate = millis();
    minutes++;
    if (minutes >= 60) { minutes = 0; hours++; }
    if (hours >= 24) hours = 0;
  }
}


void changeDigit(int delta) 
{
  int h = hours;
  int m = minutes;

  if (activeDigit == 0) h += delta * 10;
  if (activeDigit == 1) h += delta;
  if (activeDigit == 2) m += delta * 10;
  if (activeDigit == 3) m += delta;

  if (h < 0) h = 23;
  if (h > 23) h = 0;
  if (m < 0) m = 59;
  if (m > 59) m = 0;

  hours = h;
  minutes = m;
}

void handleJoystick() 
{
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);

  if (yValue < 300) { changeDigit(+1); delay(200); }
  if (yValue > 700) { changeDigit(-1); delay(200); }

  if (xValue > 700) { activeDigit = (activeDigit + 1) % 4; delay(200); }
  if (xValue < 300) { activeDigit = (activeDigit + 3) % 4; delay(200); }
}

void loop() 
{

  if (digitalRead(joySW) == LOW) {
    delay(200);
    settingMode = !settingMode;
    if (!settingMode) lastUpdate = millis();
  }

  if (settingMode) handleJoystick();
  else updateClock();

  displayTime();
}
