#ifndef BANG_h
	#include "Bang.h"
#endif

#ifndef JOYSTICK_h
	#include <Joystick.h>
#endif

// Game Profile: Joystick

class GameJoystick : public Game {
	public:
		Joystick_* joystick;
		unsigned char hatSwitches = 0;
		GameJoystick(
			Joystick_* joystick,
			unsigned char hatSwitches = 0
		) {
			this->isJoystick = true;
			this->joystick = joystick;
			this->hatSwitches = hatSwitches;
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
		void button(unsigned char button, bool pressed) override {
			if (!this->joystick) {
				debugln("Joystick not available");
				return;
			}
			bool autoRelease = false;
			int8_t hatSwitch = -1;
			int16_t direction = -1;

			switch (button) {
				case R_ENCODER_M_DN:
				case R_ENCODER_M_UP:
				case R_ENCODER_L_DN:
				case R_ENCODER_L_UP:
				case R_ENCODER_R_DN:
				case R_ENCODER_R_UP:
					autoRelease = true;
				break;
				
				case B_NAV_UP:
					hatSwitch = 1;
					direction = 0;
				break;
				case B_NAV_DOWN:
					hatSwitch = 1;
					direction = 180;
				break;
				case B_NAV_LEFT:
					hatSwitch = 1;
					direction = 90;
				break;
				case B_NAV_RIGHT:
					hatSwitch = 1;
					direction = 270;
				break;
			}
			
			
			if (hatSwitch > 0) {
				if (pressed) {
					// this->joystick->setHatSwitch(hatSwitch, direction);
				} else {
					// this->joystick->setHatSwitch(hatSwitch, JOYSTICK_HATSWITCH_RELEASE);
				}
			}
			else {
				button = button - 2;
				debug("B: ");
				debug(button);
				debug(" ");
				debugln(pressed);
				this->joystick->setButton(button, pressed);
				if (autoRelease) {
					this->joystick->setButton(button, false);
				}
			}
		}
};
