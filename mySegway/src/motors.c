#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define RANGE	100
#define INITIAL_VALUE 0

void init_motors()
{
  wiringPiSetup();

  // initialize left motor (wiring pin 2 & 3)
  softPwmCreate(2, INITIAL_VALUE, RANGE);
  softPwmCreate(3, INITIAL_VALUE, RANGE);

  // initialize right motor (wiring pin 4 & 5)
  softPwmCreate(4, INITIAL_VALUE, RANGE);
  softPwmCreate(5, INITIAL_VALUE, RANGE);
}

void stop_motors()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
//  printf("motor stopped!!\n");
  // exit(1);
}

double left_speed;
double right_speed;

void motors(double speed, double left_offset, double right_offset)
{

// to come to me, drive pin 3&5 to some power
// to away from me, drive pin 2&4 to some power

// 2:LM-, 3:LCE
// 4:RM-, 5:RCE
// put M+ high & M- low will come to me
// put M+ low & M- High will away from me

  left_speed = speed + left_offset;
  right_speed = speed + right_offset;

  // left motor
  if (left_speed < 0)  {
    softPwmWrite(2, (int) -left_speed);
    softPwmWrite(3, 0);
  }
  else
  if (left_speed > 0)  {
    softPwmWrite(3, (int) left_speed);
    softPwmWrite(2, 0);
  }

  // right motor
  if (right_speed < 0)  {
    softPwmWrite(5, (int) -right_speed);
    softPwmWrite(4, 0);
  }
  else
  if (right_speed > 0)  {
    softPwmWrite(4, (int) right_speed);
    softPwmWrite(5, 0);
  }
}



