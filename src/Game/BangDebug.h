#ifndef SETTINGS_h
	#include "Settings.h"
#endif
#ifndef BANG_h
	#include "Bang.h"
#endif

class BangDebug : public Game {
	public:
		BangDebug() {
			isKeyboard = true;
		}
		void input(unsigned char input, bool pressed) override {
			switch (input) {
				case B_BANG:
					debug("B_BANG: ");
					debugln(pressed);
				break;
				case B_NULL:
					debug("B_NULL: ");
					debugln(pressed);
				break;
				case B_IGNITION:
					debug("B_IGNITION: ");
					debugln(pressed);
				break;
				case B_ENGINE:
					debug("B_ENGINE: ");
					debugln(pressed);
				break;
				case B_PIT_LIMITER:
					debug("B_PIT_LIMITER: ");
					debugln(pressed);
				break;
				case B_LIGHT:
					debug("B_LIGHT: ");
					debugln(pressed);
				break;
				case B_FLASH:
					debug("B_FLASH: ");
					debugln(pressed);
				break;
				case B_RAINLIGHT:
					debug("B_RAINLIGHT: ");
					debugln(pressed);
				break;
				case B_WIPER:
					debug("B_WIPER: ");
					debugln(pressed);
				break;
				case B_MFD_PITSTOP:
					debug("B_MFD_PITSTOP: ");
					debugln(pressed);
				break;
				case B_MFD_STANDINGS:
					debug("B_MFD_STANDINGS: ");
					debugln(pressed);
				break;
				case B_MFD_POSITIONS:
					debug("B_MFD_POSITIONS: ");
					debugln(pressed);
				break;
				case B_MFD_ELECTRONICS:
					debug("B_MFD_ELECTRONICS: ");
					debugln(pressed);
				break;
				case B_NAV_SELECT:
					debug("B_NAV_SELECT: ");
					debugln(pressed);
				break;
				case B_NAV_UP:
					debug("B_NAV_UP: ");
					debugln(pressed);
				break;
				case B_NAV_DOWN:
					debug("B_NAV_DOWN: ");
					debugln(pressed);
				break;
				case B_NAV_LEFT:
					debug("B_NAV_LEFT: ");
					debugln(pressed);
				break;
				case B_NAV_RIGHT:
					debug("B_NAV_RIGHT: ");
					debugln(pressed);
				break;
				case B_I:
					debug("B_I: ");
					debugln(pressed);
				break;
				case B_LOVE:
					debug("B_LOVE: ");
					debugln(pressed);
				break;
				case B_RACING:
					debug("B_RACING: ");
					debugln(pressed);
				break;
				case B_ENCODER_L_PH:
					debug("B_ENCODER_L_PH: ");
					debugln(pressed);
					if (pressed) {
						this->enhance();
					}
				break;
				case B_ENCODER_M_PH:
					debug("B_ENCODER_M_PH: ");
					debugln(pressed);
					if (pressed) {
						this->enhance();
					}
				break;
				case B_ENCODER_R_PH:
					debug("B_ENCODER_R_PH: ");
					debugln(pressed);
					if (pressed) {
						this->enhance();
					}
				break;
				case R_ENCODER_M_UP:
					debug("R_ENCODER_M_UP: ");
					debugln(pressed);
				break;
				case R_ENCODER_M_DN:
					debug("R_ENCODER_M_DN: ");
					debugln(pressed);
				break;
				case R_ENCODER_L_UP:
					debug("R_ENCODER_L_UP: ");
					debugln(pressed);
				break;
				case R_ENCODER_L_DN:
					debug("R_ENCODER_L_DN: ");
					debugln(pressed);
				break;
				case R_ENCODER_R_UP:
					debug("R_ENCODER_R_UP: ");
					debugln(pressed);
				break;
				case R_ENCODER_R_DN:
					debug("R_ENCODER_R_DN: ");
					debugln(pressed);
				break;

				// BANGED Functionality
				case BANGED + B_IGNITION:
					debug("BANGED B_IGNITION: ");
					debugln(pressed);
				break;
				case BANGED + B_ENGINE:
					debug("BANGED B_ENGINE: ");
					debugln(pressed);
				break;
				case BANGED + B_PIT_LIMITER:
					debug("BANGED B_PIT_LIMITER: ");
					debugln(pressed);
				break;
				case BANGED + B_LIGHT:
					debug("BANGED B_LIGHT: ");
					debugln(pressed);
				break;
				case BANGED + B_FLASH:
					debug("BANGED B_FLASH: ");
					debugln(pressed);
				break;
				case BANGED + B_RAINLIGHT:
					debug("BANGED B_RAINLIGHT: ");
					debugln(pressed);
				break;
				case BANGED + B_WIPER:
					debug("BANGED B_WIPER: ");
					debugln(pressed);
				break;
				case BANGED + B_MFD_PITSTOP:
					debug("BANGED B_MFD_PITSTOP: ");
					debugln(pressed);
				break;
				case BANGED + B_MFD_STANDINGS:
					debug("BANGED B_MFD_STANDINGS: ");
					debugln(pressed);
				break;
				case BANGED + B_MFD_POSITIONS:
					debug("BANGED B_MFD_POSITIONS: ");
					debugln(pressed);
				break;
				case BANGED + B_MFD_ELECTRONICS:
					debug("BANGED B_MFD_ELECTRONICS: ");
					debugln(pressed);
				break;
				case BANGED + B_NAV_SELECT:
					debug("BANGED B_NAV_SELECT: ");
					debugln(pressed);
				break;
				case BANGED + B_NAV_UP:
					debug("BANGED B_NAV_UP: ");
					debugln(pressed);
				break;
				case BANGED + B_NAV_DOWN:
					debug("BANGED B_NAV_DOWN: ");
					debugln(pressed);
				break;
				case BANGED + B_NAV_LEFT:
					debug("BANGED B_NAV_LEFT: ");
					debugln(pressed);
				break;
				case BANGED + B_NAV_RIGHT:
					debug("BANGED B_NAV_RIGHT: ");
					debugln(pressed);
				break;
				case BANGED + B_I:
					debug("BANGED B_I: ");
					debugln(pressed);
				break;
				case BANGED + B_LOVE:
					debug("BANGED B_LOVE: ");
					debugln(pressed);
				break;
				case BANGED + B_RACING:
					debug("BANGED B_RACING: ");
					debugln(pressed);
				break;
				case BANGED + B_ENCODER_L_PH:
					debug("BANGED B_ENCODER_L_PH: ");
					debugln(pressed);
					if (pressed) {
						this->enhance();
					}
				break;
				case BANGED + B_ENCODER_M_PH:
					debug("BANGED B_ENCODER_M_PH: ");
					debugln(pressed);
					if (pressed) {
						this->enhance();
					}
				break;
				case BANGED + B_ENCODER_R_PH:
					debug("BANGED B_ENCODER_R_PH: ");
					debugln(pressed);
					if (pressed) {
						this->enhance();
					}
				break;
				case BANGED + R_ENCODER_M_UP:
					debug("BANGED R_ENCODER_M_UP: ");
					debugln(pressed);
				break;
				case BANGED + R_ENCODER_M_DN:
					debug("BANGED R_ENCODER_M_DN: ");
					debugln(pressed);
				break;
				case BANGED + R_ENCODER_L_UP:
					debug("BANGED R_ENCODER_L_UP: ");
					debugln(pressed);
				break;
				case BANGED + R_ENCODER_L_DN:
					debug("BANGED R_ENCODER_L_DN: ");
					debugln(pressed);
				break;
				case BANGED + R_ENCODER_R_UP:
					debug("BANGED R_ENCODER_R_UP: ");
					debugln(pressed);
				break;
				case BANGED + R_ENCODER_R_DN:
					debug("BANGED R_ENCODER_R_DN: ");
					debugln(pressed);
				break;
				default:
					debug("Unknown button: ");
					debugln(input);
				break;
			}
		}
};
