#ifndef BANG_h
	#include "Bang.h"
#endif

#ifndef HID_PROJECT_VERSION
	#include <HID-Project.h>
#endif

class GameKeyboard : public Game {
	public:
		GameKeyboard() {
			this->isKeyboard = true;
			debugln("GameKeyboard");
		};
		void input(unsigned char input, bool pressed) override {
			switch (input) {
				// engine
				case B_ENGINE:
					this->key(KEYPAD_MULTIPLY, pressed);
				break;
				case B_IGNITION:
					this->key(KEY_5, pressed);
				break;
				case B_PIT_LIMITER:
					this->key(KEY_6, pressed);
				break;
				// lights
				case B_LIGHT:
					this->key(KEY_2, pressed);
				break;
				case B_FLASH:
					this->key(KEY_1, pressed);
				break;
				case B_RAINLIGHT:
					this->key(KEY_3, pressed);
				break;
				case B_WIPER:
					this->key(KEY_4, pressed);
				break;
				// mfd
				case B_MFD_PITSTOP:
					this->key(KEY_8, pressed);
				break;
				case B_MFD_STANDINGS:
					this->key(KEY_9, pressed);
				break;
				case B_MFD_POSITIONS:
					this->key(KEY_0, pressed);
				break;
				case B_MFD_ELECTRONICS:
					this->key(KEY_BACKSPACE, pressed);
				break;
				// nav
				case B_NAV_SELECT:
					this->key(KEY_RETURN, pressed);
				break;
				case B_NAV_UP:
					this->key(KEY_UP_ARROW, pressed);
				break;
				case B_NAV_DOWN:
					this->key(KEY_DOWN_ARROW, pressed);
				break;
				case B_NAV_LEFT:
					this->key(KEY_LEFT_ARROW, pressed);
				break;
				case B_NAV_RIGHT:
					this->key(KEY_RIGHT_ARROW, pressed);
				break;
				// banged engine
				case BANGED + B_IGNITION:
					this->key(KEY_F5, pressed);
				break;
				case BANGED + B_ENGINE:
					this->key(KEYPAD_DIVIDE, pressed);
				break;
				case BANGED + B_PIT_LIMITER:
					this->key(KEY_F6, pressed);
				break;
				// banged lights
				case BANGED + B_LIGHT:
					this->key(KEY_F2, pressed);
				break;
				case BANGED + B_FLASH:
					this->key(KEY_F1, pressed);
				break;
				case BANGED + B_RAINLIGHT:
					this->key(KEY_F3, pressed);
				break;
				case BANGED + B_WIPER:
					this->key(KEY_F4, pressed);
				break;
				// banged mfd
				case BANGED + B_MFD_PITSTOP:
					this->key(KEY_F8, pressed);
				break;
				case BANGED + B_MFD_STANDINGS:
					this->key(KEY_F9, pressed);
				break;
				case BANGED + B_MFD_POSITIONS:
					this->key(KEY_F10, pressed);
				break;
				case BANGED + B_MFD_ELECTRONICS:
					this->key(KEYPAD_SUBTRACT, pressed);
				break;
				// banged nav
				case BANGED + B_NAV_SELECT:
					this->key(KEYPAD_ADD, pressed);
				break;
				case BANGED + B_NAV_UP:
					this->key(KEY_UP_ARROW, pressed);
				break;
				case BANGED + B_NAV_DOWN:
					this->key(KEY_DOWN_ARROW, pressed);
				break;
				case BANGED + B_NAV_LEFT:
					this->key(KEY_LEFT_ARROW, pressed);
				break;
				case BANGED + B_NAV_RIGHT:
					this->key(KEY_RIGHT_ARROW, pressed);
				break;
				default:
					debug("B: ");
					debug(input);
					debug(" = ");
					debugln(pressed);
				break;
			}
		}
};
