#ifndef BANG_h
	#include "Bang.h"
#endif

#define LED_BANG_PIN 13
#define LED_R_PIN 9
#define LED_G_PIN 10
#define LED_B_PIN 11
#define LED_LIGHTS_PIN 3

#define ROTARY_ENCODER_M_CL_PIN 8
#define ROTARY_ENCODER_M_DT_PIN 16

#define ROTARY_ENCODER_L_CL_PIN 0
#define ROTARY_ENCODER_L_DT_PIN 1

#define ROTARY_ENCODER_R_CL_PIN 2
#define ROTARY_ENCODER_R_DT_PIN 7

#define ROTARY_ENCODER_M_SWT_PIN 12
#define ROTARY_ENCODER_L_SWT_PIN 14
#define ROTARY_ENCODER_R_SWT_PIN 15

#define MATRIX_SENDERS 4
#define MATRIX_RECEIVERS 5

#define MATRIX_SENDER_1_PIN 4
#define MATRIX_SENDER_2_PIN 5
#define MATRIX_SENDER_3_PIN 6
#define MATRIX_SENDER_4_PIN A0

#define MATRIX_RECEIVER_1_PIN A1
#define MATRIX_RECEIVER_2_PIN A2
#define MATRIX_RECEIVER_3_PIN A3
#define MATRIX_RECEIVER_4_PIN A4
#define MATRIX_RECEIVER_5_PIN A5

unsigned char matrixSenders[MATRIX_SENDERS] = {
	MATRIX_SENDER_1_PIN,
	MATRIX_SENDER_2_PIN,
	MATRIX_SENDER_3_PIN,
	MATRIX_SENDER_4_PIN
};
unsigned char matrixReceivers[MATRIX_RECEIVERS] = {
	MATRIX_RECEIVER_1_PIN,
	MATRIX_RECEIVER_2_PIN,
	MATRIX_RECEIVER_3_PIN,
	MATRIX_RECEIVER_4_PIN,
	MATRIX_RECEIVER_5_PIN
};

unsigned char buttonsGrid[MATRIX_RECEIVERS][MATRIX_SENDERS] = {
	{B_BANG, B_IGNITION, B_ENGINE, B_PIT_LIMITER},
	{B_LIGHT, B_RAINLIGHT, B_WIPER, B_FLASH},
	{B_MFD_PITSTOP, B_MFD_STANDINGS, B_MFD_POSITIONS, B_MFD_ELECTRONICS},
	{B_NAV_SELECT, B_NAV_UP, B_NAV_DOWN, B_NAV_LEFT},
	{B_NAV_RIGHT, B_I, B_LOVE, B_RACING}
};
