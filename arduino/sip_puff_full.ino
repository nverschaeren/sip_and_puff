#include <Q2HX711.h>
#include "Keyboard.h"
// #include "Mouse.h"

/* connect the sensors to pin 2-9 */
Q2HX711 SENSOR_01(2, 3);
Q2HX711 SENSOR_02(4, 5);
Q2HX711 SENSOR_03(6, 7);
Q2HX711 SENSOR_04(8, 9);
 
/* sensor state: 0 neutral, 1 sipp, 2 puff */
int sensorStates [] = {0, 0, 0, 0};

/* initial sensor value */
int sensorInitValues [] = {0, 0, 0, 0};

/* calibration led */
int calibrationLed = 14;

/* sip-puff detection led */
int actionLed = 15;

/* calibration counter */
int calibrationCounterInitial = 500;
int calibrationCounter = 2;
bool calibrating = false;

/* CTRL key */
/* OSX: */
char ctrlKey = KEY_LEFT_GUI;
/* Windows and Linux: */
// char ctrlKey = KEY_LEFT_CTRL;

/* debug modus set to true to test sensors */
bool debug = false;

void setup() {
  if (debug) {
    Serial.begin(9600);
  }
  pinMode(calibrationLed, OUTPUT);
  pinMode(actionLed, OUTPUT);
  Keyboard.begin();
  calibrate();
}

void loop() {
  if (!calibrating) {
    updateSensorState(0, SENSOR_01.read() / 10000 );
    delay(10);
    updateSensorState(1, SENSOR_02.read() / 10000 );
    delay(10);
    updateSensorState(2, SENSOR_03.read() / 10000 );
    delay(10);
    updateSensorState(3, SENSOR_04.read() / 10000 );
    delay(10);
    sendKeys();
    calibrationCounter--;
    if (calibrationCounter == 0) {
      calibrationCounter = calibrationCounterInitial;
      calibrate();
    }
  }
  delay(100);
}

void calibrate() {
  calibrating = true;
  delay(300);
  digitalWrite(calibrationLed, HIGH);
  sensorInitValues[0] = SENSOR_01.read() / 10000;
  delay(100);
  sensorInitValues[1] = SENSOR_02.read() / 10000;
  delay(100);
  sensorInitValues[2] = SENSOR_03.read() / 10000;
  delay(100);
  sensorInitValues[3] = SENSOR_04.read() / 10000;
  delay(100);
  digitalWrite(calibrationLed, LOW);
  calibrating = false;
}

void updateSensorState(int sensor, int curValue) {
  int state_sensor = sensorStates[sensor];
  int init_val_sensor = sensorInitValues[sensor];
  if (state_sensor == 0) {
    if (curValue < init_val_sensor - 10) {
      /* Sip detected */
      sensorStates[sensor] = 1;
    }
    if (curValue > init_val_sensor + 10) {
      /* puff detected */
      sensorStates[sensor] = 2;
    }
  } else if (state_sensor == 1 or state_sensor == 2) {
    /* sip or puff state ended */
    sensorStates[sensor] = 0;
  }
}

void sendKeys() {
  // Keyboard.press(KEY_LEFT_SHIFT);
  // Keyboard.press(KEY_LEFT_ALT);
  switch (sensorStates[0]) {
    case 1:
      // sip 1
      digitalWrite(actionLed, HIGH);
      keyboardSend(KEY_ESC, "ESC");
      break;
    case 2:
      // puff 1
      digitalWrite(actionLed, HIGH);
      keyboardSend(0x20, "SPACE"); // SPACE
      //Mouse.move(0, +40);
      break;
    default:
      break;
  }
  switch (sensorStates[1]) {
    case 1:
      // sip 2
      digitalWrite(actionLed, HIGH);
      keyboardSend(KEY_RETURN, "RETURN");
      break;
    case 2:
      // puff 2
      digitalWrite(actionLed, HIGH);
      keyboardSend(KEY_RIGHT_ARROW, "RIGHT");
      // Mouse.move(+40, 0);
      break;
    default:
      break;
  }
  switch (sensorStates[2]) {
    case 1:
      // sip 3
      digitalWrite(actionLed, HIGH);
      keyboardSend(KEY_DOWN_ARROW, "DOWN");
      break;
    case 2:
      // puff 3
      digitalWrite(actionLed, HIGH);
      keyboardSend(KEY_BACKSPACE, "BACKSPACE");
    default:
      break;
  }
  switch (sensorStates[3]) {
    case 1:
      // sip 4
      digitalWrite(actionLed, HIGH);
      keyboardSend(KEY_LEFT_SHIFT, "LEFT");
      delay(10);
      keyboardSend(KEY_TAB, "TAB");
      break;
    case 2:
      // puff 4
      digitalWrite(actionLed, HIGH);
      keyboardSend(KEY_TAB, "TAB");
      break;
    default:
      break;
  }
  delay(100);
  Keyboard.releaseAll();
  digitalWrite(actionLed, LOW);
}

void keyboardSend(char key, char* keyLabel) {
  if (debug) {
    Serial.print(keyLabel);
    Serial.println();
  } else {
    Keyboard.press(key);
  }
}