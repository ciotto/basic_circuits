#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"
#include <Servo.h>

Servo myservo;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH       700
#define MAX_PULSE_WIDTH       2500
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

uint8_t servonum = 0;

void setup() 
{
  // Serial.begin(9600);
  // Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}
int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  // Serial.println(analog_value);
  return analog_value;
}

void loop() {
  digitalWrite(7, 1);
  analogWrite(6, 255);
  delay(1000);                           // waits for the servo to get there


  // Serial.print("1 set to ");
  // pwm.setPWM(0, 0, pulseWidth(0));
  // pwm.setPWM(1, 0, pulseWidth(0));
  // delay(1000);


  // Serial.print("2 set to ");
  // pwm.setPWM(0, 0, pulseWidth(90));
  // pwm.setPWM(1, 0, pulseWidth(90));
  // delay(1000);


  // Serial.print("3 set to ");
  // pwm.setPWM(0, 0, pulseWidth(180));
  // pwm.setPWM(1, 0, pulseWidth(180));
  // delay(2000);
}