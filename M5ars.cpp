#include "M5ars.h"

uint8_t M5ars_knee_set(uint8_t Knee_id,uint8_t angle)
{
  uint8_t Servo_CH=Knee_id*2;
  uint8_t Servo_angle;

  switch (Knee_id)
  {
    case 1:
      Servo_angle=KNEE_1_ANGLE-angle;
      break;
    case 2:
      Servo_angle=KNEE_2_ANGLE+angle;
      break;
    case 3:
      Servo_angle=KNEE_3_ANGLE+angle;
      break;
    case 4:
      Servo_angle=KNEE_4_ANGLE-angle;
      break;
    default:
      return 1;
      break;
  }

  Servo_angle_set(Servo_CH,Servo_angle);
  return 0;
}

uint8_t M5ars_leg_set (uint8_t Leg_id ,uint8_t angle)
{
  uint8_t Servo_CH=Leg_id*2-1;
  uint8_t Servo_angle;

  switch (Leg_id)
  {
    case 1:
      Servo_angle=LEG_1_ANGLE-angle;
      break;
    case 2:
      Servo_angle=LEG_2_ANGLE+angle;
      break;
    case 3:
      Servo_angle=LEG_3_ANGLE+angle;
      break;
    case 4:
      Servo_angle=LEG_4_ANGLE-angle;
      break;
    default:
      return 1;
      break;
  }

  Servo_angle_set(Servo_CH,Servo_angle);
  return 0;
}

int8_t M5ars_knee_read(uint8_t Knee_id)
{
  uint8_t Servo_CH=Knee_id*2;
  uint8_t Servo_angle;
  uint8_t angle;

  Servo_angle=Servo_angle_read(Servo_CH);

  switch (Knee_id)
  {
    case 1:
      angle=KNEE_1_ANGLE-Servo_angle;
      break;
    case 2:
      angle=-KNEE_2_ANGLE+Servo_angle;
      break;
    case 3:
      angle=-KNEE_3_ANGLE+Servo_angle;
      break;
    case 4:
      angle=KNEE_4_ANGLE-Servo_angle;
      break;
    default:
      break;
  }

  return angle;
}

int8_t M5ars_leg_read (uint8_t Leg_id)
{
  uint8_t Servo_CH=Leg_id*2-1;
  uint8_t Servo_angle;
  int8_t angle;

  Servo_angle=Servo_angle_read(Servo_CH);

  switch (Leg_id)
  {
    case 1:
      angle=Servo_angle-LEG_1_ANGLE;
      break;
    case 2:
      angle=Servo_angle-LEG_2_ANGLE;
      break;
    case 3:
      angle=-Servo_angle+LEG_3_ANGLE;
      break;
    case 4:
      angle=-Servo_angle+LEG_4_ANGLE;
      break;
    default:
      break;
  }

  return angle;
}

void M5ars_move(uint8_t time,char m)
{

  switch (m)
  {
    case KNEE_1_UP:
      M5ars_knee_set(1,KNEE_UP_ANGLE);
      break;
    case KNEE_1_DOWN:
      M5ars_knee_set(1,KNEE_DOWN_ANGLE);
      break;
    case KNEE_2_UP:
      M5ars_knee_set(2,KNEE_UP_ANGLE);
      break;
    case KNEE_2_DOWN:
      M5ars_knee_set(2,KNEE_DOWN_ANGLE);
      break;
    case KNEE_3_UP:
      M5ars_knee_set(3,KNEE_UP_ANGLE);
      break;
    case KNEE_3_DOWN:
      M5ars_knee_set(3,KNEE_DOWN_ANGLE);
      break;
    case KNEE_4_UP:
      M5ars_knee_set(4,KNEE_UP_ANGLE);
      break;
    case KNEE_4_DOWN:
      M5ars_knee_set(4,KNEE_DOWN_ANGLE);
      break;
    case LEG_1_FORWARD:
      M5ars_leg_set(1,LEG_FORWARD_ANGLE);
      break;
    case LEG_1_BACKWARD:
      M5ars_leg_set(1,LEG_BACKWARD_ANGLE);
      break;
    case LEG_2_FORWARD:
      M5ars_leg_set(2,LEG_FORWARD_ANGLE);
      break;
    case LEG_2_BACKWARD:
      M5ars_leg_set(2,LEG_BACKWARD_ANGLE);
      break;
    case LEG_3_FORWARD:
      M5ars_leg_set(3,LEG_FORWARD_ANGLE);
      break;
    case LEG_3_BACKWARD:
      M5ars_leg_set(3,LEG_BACKWARD_ANGLE);
      break;
    case LEG_4_FORWARD:
      M5ars_leg_set(4,LEG_FORWARD_ANGLE);
      break;
    case LEG_4_BACKWARD:
      M5ars_leg_set(4,LEG_BACKWARD_ANGLE);
      break;
    case TEMPO:
      delay(time);
      break;                              
    default:
      break;
  }
}


void M5ars_backward(uint8_t time)
{
  for (char m: backwardArray)
  {
    M5ars_move(time,m);
  }
}

void M5ars_forward(uint8_t time)
{
  for (char m: forwardArray)
  {
    M5ars_move(time,m);
  }
}

void M5ars_turn_right(uint8_t time)
{
  for (char m: turnRightArray)
  {
    M5ars_move(time,m);
  }
}

void M5ars_turn_left(uint8_t time)
{
  for (char m: turnLeftArray)
  {
    M5ars_move(time,m);
  }
}

void M5ars_position_start(uint8_t time)
{

  int knee_order[] = {1, 3, 2, 4};

  for(int i=1;i<=4;i++)
  {
    M5ars_knee_set(i,0);
  }

  delay(time);

  for(int i=0;i<4;i++)
  {
    if (M5ars_leg_read(knee_order[i])!=0)
    {
      M5ars_knee_set(knee_order[i],KNEE_UP_ANGLE);
      delay(time);
      M5ars_leg_set(knee_order[i],0);
      delay(time);
      M5ars_knee_set(knee_order[i],KNEE_DOWN_ANGLE);
      delay(time);
    }
    
  }
    
}



