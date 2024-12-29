#ifndef _M5ARS_H_
#define _M5ARS_H_

#include <M5StickC.h>
#include "IIC_servo.h"

/*****************************************
 * Contants to finely tune your bot      *
 *****************************************/
#define KNEE_1_ANGLE 84
#define KNEE_2_ANGLE 90
#define KNEE_3_ANGLE 70
#define KNEE_4_ANGLE 90

#define LEG_1_ANGLE  92
#define LEG_2_ANGLE  87
#define LEG_3_ANGLE  90
#define LEG_4_ANGLE  92
/*****************************************
 * Vocabulary for movement               *
 *****************************************/
#define KNEE_1_UP       'A'
#define KNEE_1_DOWN     'a'
#define KNEE_2_UP       'B'
#define KNEE_2_DOWN     'b'
#define KNEE_3_UP       'C'
#define KNEE_3_DOWN     'c'
#define KNEE_4_UP       'D'
#define KNEE_4_DOWN     'd'
#define LEG_1_FORWARD   'E'
#define LEG_1_BACKWARD  'e'
#define LEG_2_FORWARD   'F'
#define LEG_2_BACKWARD  'f'
#define LEG_3_FORWARD   'G'
#define LEG_3_BACKWARD  'g'
#define LEG_4_FORWARD   'H'
#define LEG_4_BACKWARD  'h'
#define TEMPO           ' '

#define KNEE_UP_ANGLE        30
#define KNEE_DOWN_ANGLE       0
#define LEG_FORWARD_ANGLE    30
#define LEG_BACKWARD_ANGLE  -30

uint8_t M5ars_knee_set(uint8_t Knee_id,uint8_t angle);
uint8_t M5ars_leg_set (uint8_t Leg_id ,uint8_t angle);

int8_t M5ars_knee_read(uint8_t Knee_id);
int8_t M5ars_leg_read (uint8_t Leg_id);

void    M5ars_forward(uint8_t time);
void    M5ars_backward(uint8_t time);
void    M5ars_turn_right(uint8_t time);
void    M5ars_turn_left(uint8_t time);
void    M5ars_position_start(uint8_t time);

//const char forwardArray[]   = "CB g E h F cb AD e G H f ad ";
const char forwardArray[]   = "A Ge a  C gE c  B hF b  D Hf d ";

const char backwardArray[]  = "CB G e H f cb AD E g h F ad ";
const char turnRightArray[] = "CB g eh f cb AD E GF H ad ";
const char turnLeftArray[]  = "CB G EH F cb AD e gf h ad ";


#endif
