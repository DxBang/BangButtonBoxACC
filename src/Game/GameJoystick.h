#ifndef BANG_h
	#include "Bang.h"
#endif

class GameJoystick : public Game {
	public:
		unsigned char hatSwitches[2][4] = {
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		};
		GameJoystick(
			Joystick_* joystick
		) {
			this->isJoystick = true;
			this->isKeyboard = false;
			this->joystick = joystick;
		}
		void begin() {
			// check if joystick is available
			if (this->isJoystick) {
				this->joystick->begin();
			}
			Game::begin();
		}
		void end() {
			// check if joystick is available
			if (this->isJoystick) {
				this->joystick->end();
			}
			Game::end();
		}
		void input(unsigned char input, bool pressed) override {
			if (!this->joystick) {
				debugln("!joystick");
				return;
			}
			bool autoRelease = false;
			int8_t hatSwitch = 0;
			int16_t direction = 0;

			switch (input) {
				case R_ENCODER_M_DN:
				case R_ENCODER_M_UP:
				case R_ENCODER_L_DN:
				case R_ENCODER_L_UP:
				case R_ENCODER_R_DN:
				case R_ENCODER_R_UP:
				case BANGED + R_ENCODER_M_DN:
				case BANGED + R_ENCODER_M_UP:
				case BANGED + R_ENCODER_L_DN:
				case BANGED + R_ENCODER_L_UP:
				case BANGED + R_ENCODER_R_DN:
				case BANGED + R_ENCODER_R_UP:				
					autoRelease = true;
				break;
				case B_NAV_UP:
					hatSwitch = 1;
					this->hatSwitches[hatSwitch][0] = pressed;
					// check if NAV_LEFT is pressed
					if (this->hatSwitches[hatSwitch][1]) {
						direction = 315;
					}
					// check if NAV_RIGHT is pressed
					else if (this->hatSwitches[hatSwitch][3]) {
						direction = 45;
					}
					else {
						direction = 0;
					}
				break;
				case B_NAV_DOWN:
					hatSwitch = 1;
					this->hatSwitches[hatSwitch][1] = pressed;
					// check if NAV_LEFT is pressed
					if (this->hatSwitches[hatSwitch][2]) {
						direction = 225;
					}
					// check if NAV_RIGHT is pressed
					else if (this->hatSwitches[hatSwitch][3]) {
						direction = 135;
					}
					else {
						direction = 180;
					}
				break;
				case B_NAV_LEFT:
					hatSwitch = 1;
					this->hatSwitches[hatSwitch][2] = pressed;
					// check if NAV_UP is pressed
					if (this->hatSwitches[hatSwitch][0]) {
						direction = 315;
					}
					// check if NAV_DOWN is pressed
					else if (this->hatSwitches[hatSwitch][1]) {
						direction = 225;
					}
					else {
						direction = 270;
					}
				break;
				case B_NAV_RIGHT:
					hatSwitch = 1;
					this->hatSwitches[hatSwitch][3] = pressed;
					// check if NAV_UP is pressed
					if (this->hatSwitches[hatSwitch][0]) {
						direction = 45;
					}
					// check if NAV_DOWN is pressed
					else if (this->hatSwitches[hatSwitch][1]) {
						direction = 135;
					}
					else {
						direction = 90;
					}
				break;
			}
			if (hatSwitch > 0) {
				if (pressed) {
					// check if 
					debug("hatSwitch: ");
					debug(hatSwitch);
					debug(" direction: ");
					debugln(direction);
					this->joystick->setHatSwitch(hatSwitch, direction);
				} else {
					this->joystick->setHatSwitch(hatSwitch, JOYSTICK_HATSWITCH_RELEASE);
				}
				return;
			}
			input = input - 2;
			this->joystick->setButton(input, pressed);
			if (autoRelease) {
				this->joystick->setButton(input, false);
			}
		}
};
