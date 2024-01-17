#ifndef BANG_h
	#include "Bang.h"
#endif

class BangDebug : public Game {

	public:
		BangDebug() {
			isKeyboard = true;
		}
		void button(unsigned char button, bool pressed) override {
			switch (button) {
				case B_NULL:
					Serial.print("B_NULL: ");
					Serial.println(pressed);
					break;
				case B_ENGINE:
					Serial.print("B_ENGINE: ");
					Serial.println(pressed);
					break;
				case B_IGNITION:
					Serial.print("B_IGNITION: ");
					Serial.println(pressed);
					break;
				case B_PIT_LIMITER:
					Serial.print("B_PIT_LIMITER: ");
					Serial.println(pressed);
					break;
				case B_LIGHT:
					Serial.print("B_LIGHT: ");
					Serial.println(pressed);
					break;
				case B_FLASH:
					Serial.print("B_FLASH: ");
					Serial.println(pressed);
					break;
				case B_RAINLIGHT:
					Serial.print("B_RAINLIGHT: ");
					Serial.println(pressed);
					break;
				case B_WIPER:
					Serial.print("B_WIPER: ");
					Serial.println(pressed);
					break;
				case B_MFD_PITSTOP:
					Serial.print("B_MFD_PITSTOP: ");
					Serial.println(pressed);
					break;
				case B_MFD_STANDINGS:
					Serial.print("B_MFD_STANDINGS: ");
					Serial.println(pressed);
					break;
				case B_MFD_POSITIONS:
					Serial.print("B_MFD_POSITIONS: ");
					Serial.println(pressed);
					break;
				case B_NAV_UP:
					Serial.print("B_NAV_UP: ");
					Serial.println(pressed);
					break;
				case B_NAV_DOWN:
					Serial.print("B_NAV_DOWN: ");
					Serial.println(pressed);
					break;
				case B_NAV_LEFT:
					Serial.print("B_NAV_LEFT: ");
					Serial.println(pressed);
					break;
				case B_NAV_RIGHT:
					Serial.print("B_NAV_RIGHT: ");
					Serial.println(pressed);
					break;
				case B_NAV_SELECT:
					Serial.print("B_NAV_SELECT: ");
					Serial.println(pressed);
					break;
				case B_MFD_ELECTRONICS:
					Serial.print("B_MFD_ELECTRONICS: ");
					Serial.println(pressed);
					break;
				case B_EXTRA_1:
					Serial.print("B_EXTRA_1: ");
					Serial.println(pressed);
					break;
				case B_EXTRA_2:
					Serial.print("B_EXTRA_2: ");
					Serial.println(pressed);
					break;
				case B_EXTRA_3:
					Serial.print("B_EXTRA_3: ");
					Serial.println(pressed);
					break;
				case B_ENCODER_L_PH:
					Serial.print("B_ENCODER_L_PH: ");
					Serial.println(pressed);
					break;
				case B_ENCODER_M_PH:
					Serial.print("B_ENCODER_M_PH: ");
					Serial.println(pressed);
					break;
				case B_ENCODER_R_PH:
					Serial.print("B_ENCODER_R_PH: ");
					Serial.println(pressed);
					break;
				case R_ENCODER_M_UP:
					Serial.print("R_ENCODER_M_UP: ");
					Serial.println(pressed);
					break;
				case R_ENCODER_M_DN:
					Serial.print("R_ENCODER_M_DN: ");
					Serial.println(pressed);
					break;
				case R_ENCODER_L_UP:
					Serial.print("R_ENCODER_L_UP: ");
					Serial.println(pressed);
					break;
				case R_ENCODER_L_DN:
					Serial.print("R_ENCODER_L_DN: ");
					Serial.println(pressed);
					break;
				case R_ENCODER_R_UP:
					Serial.print("R_ENCODER_R_UP: ");
					Serial.println(pressed);
					break;
				case R_ENCODER_R_DN:
					Serial.print("R_ENCODER_R_DN: ");
					Serial.println(pressed);
					break;


				// BANGED Functionality
				case BANGED + B_ENGINE:
					Serial.print("BANGED B_ENGINE: ");
					Serial.println(pressed);
					break;
				case BANGED + B_IGNITION:
					Serial.print("BANGED B_IGNITION: ");
					Serial.println(pressed);
					break;
				case BANGED + B_PIT_LIMITER:
					Serial.print("BANGED B_PIT_LIMITER: ");
					Serial.println(pressed);
					break;
				case BANGED + B_LIGHT:
					Serial.print("BANGED B_LIGHT: ");
					Serial.println(pressed);
					break;
				case BANGED + B_FLASH:
					Serial.print("BANGED B_FLASH: ");
					Serial.println(pressed);
					break;
				case BANGED + B_RAINLIGHT:
					Serial.print("BANGED B_RAINLIGHT: ");
					Serial.println(pressed);
					break;
				case BANGED + B_WIPER:
					Serial.print("BANGED B_WIPER: ");
					Serial.println(pressed);
					break;
				case BANGED + B_MFD_PITSTOP:
					Serial.print("BANGED B_MFD_PITSTOP: ");
					Serial.println(pressed);
					break;
				case BANGED + B_MFD_STANDINGS:
					Serial.print("BANGED B_MFD_STANDINGS: ");
					Serial.println(pressed);
					break;
				case BANGED + B_MFD_POSITIONS:
					Serial.print("BANGED B_MFD_POSITIONS: ");
					Serial.println(pressed);
					break;
				case BANGED + B_NAV_UP:
					Serial.print("BANGED B_NAV_UP: ");
					Serial.println(pressed);
					break;
				case BANGED + B_NAV_DOWN:
					Serial.print("BANGED B_NAV_DOWN: ");
					Serial.println(pressed);
					break;
				case BANGED + B_NAV_LEFT:
					Serial.print("BANGED B_NAV_LEFT: ");
					Serial.println(pressed);
					break;
				case BANGED + B_NAV_RIGHT:
					Serial.print("BANGED B_NAV_RIGHT: ");
					Serial.println(pressed);
					break;
				case BANGED + B_NAV_SELECT:
					Serial.print("BANGED B_NAV_SELECT: ");
					Serial.println(pressed);
					break;
				case BANGED + B_MFD_ELECTRONICS:
					Serial.print("BANGED B_MFD_ELECTRONICS: ");
					Serial.println(pressed);
					break;
				case BANGED + B_EXTRA_1:
					Serial.print("BANGED B_EXTRA_1: ");
					Serial.println(pressed);
					break;
				case BANGED + B_EXTRA_2:
					Serial.print("BANGED B_EXTRA_2: ");
					Serial.println(pressed);
					break;
				case BANGED + B_EXTRA_3:
					Serial.print("BANGED B_EXTRA_3: ");
					Serial.println(pressed);
					break;
				case BANGED + B_ENCODER_L_PH:
					Serial.print("BANGED B_ENCODER_L_PH: ");
					Serial.println(pressed);
					break;
				case BANGED + B_ENCODER_M_PH:
					Serial.print("BANGED B_ENCODER_M_PH: ");
					Serial.println(pressed);
					break;
				case BANGED + B_ENCODER_R_PH:
					Serial.print("BANGED B_ENCODER_R_PH: ");
					Serial.println(pressed);
					break;
				case BANGED + R_ENCODER_M_UP:
					Serial.print("BANGED R_ENCODER_M_UP: ");
					Serial.println(pressed);
					break;
				case BANGED + R_ENCODER_M_DN:
					Serial.print("BANGED R_ENCODER_M_DN: ");
					Serial.println(pressed);
					break;
				case BANGED + R_ENCODER_L_UP:
					Serial.print("BANGED R_ENCODER_L_UP: ");
					Serial.println(pressed);
					break;
				case BANGED + R_ENCODER_L_DN:
					Serial.print("BANGED R_ENCODER_L_DN: ");
					Serial.println(pressed);
					break;
				case BANGED + R_ENCODER_R_UP:
					Serial.print("BANGED R_ENCODER_R_UP: ");
					Serial.println(pressed);
					break;
				case BANGED + R_ENCODER_R_DN:
					Serial.print("BANGED R_ENCODER_R_DN: ");
					Serial.println(pressed);
					break;

				case B_BANG:
					Serial.print("B_BANG: ");
					Serial.println(pressed);
					break;
				default:
					Serial.print("Unknown button: ");
					Serial.println(button);
					break;
			}
		}
};
