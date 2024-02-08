#ifndef BANG_h
	#define BANG_h
#endif

#ifndef JOYSTICK_h
	#include <Joystick.h>
#endif
#ifndef HID_PROJECT_VERSION
	#include <HID-Project.h>
#endif


void setBangLED(unsigned char value);
void modeDefault();

// Inputs
#define B_NULL 0

#define B_BANG 1
#define B_IGNITION 2
#define B_ENGINE 3
#define B_PIT_LIMITER 4
#define B_LIGHT 5
#define B_RAINLIGHT 6
#define B_WIPER 7
#define B_FLASH 8

#define B_MFD_PITSTOP 9
#define B_MFD_STANDINGS 10
#define B_MFD_POSITIONS 11
#define B_MFD_ELECTRONICS 12

#define B_NAV_SELECT 13
#define B_NAV_UP 14
#define B_NAV_DOWN 15
#define B_NAV_LEFT 16
#define B_NAV_RIGHT 17

#define B_I 18
#define B_LOVE 19
#define B_RACING 20

#define B_ENCODER_M_PH 21
#define R_ENCODER_M_UP 22
#define R_ENCODER_M_DN 23

#define B_ENCODER_L_PH 24
#define R_ENCODER_L_UP 25
#define R_ENCODER_L_DN 26

#define B_ENCODER_R_PH 27
#define R_ENCODER_R_UP 28
#define R_ENCODER_R_DN 29

#define BANGED 29

struct RGB {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct HSL {
	unsigned short h;
	float s;
	float l;
};

class Color {
	private:
		unsigned short hue;
		float saturation;
		float lightness;
	public:
		Color(unsigned short hue, float saturation, float lightness) : hue(hue), saturation(saturation), lightness(lightness) {}
		Color(HSL hsl) : hue(hsl.h), saturation(hsl.s), lightness(hsl.l) {}
		void setHSL(unsigned short hue, float saturation, float lightness) {
			this->hue = hue;
			this->saturation = saturation;
			this->lightness = lightness;
		}
		void setHue(unsigned short hue) {
			this->hue = hue;
		}
		void setSaturation(float saturation) {
			this->saturation = saturation;
		}
		void setLightness(float lightness) {
			this->lightness = lightness;
		}
		unsigned short getHue() {
			return hue;
		}
		float getSaturation() {
			return saturation;
		}
		float getLightness() {
			return lightness;
		}
		HSL getHSL() {
			HSL hsl;
			hsl.h = this->hue;
			hsl.s = this->saturation;
			hsl.l = this->lightness;
			return hsl;
		}
		RGB getRGB() {
			RGB rgb;
			float c = (1 - abs(2 * lightness - 1)) * saturation;
			float h_prime = hue / 60.0;
			float x = c * (1 - abs(fmod(h_prime, 2) - 1));
			float m = lightness - c / 2;
			float r_temp, g_temp, b_temp;
			if (h_prime >= 0 && h_prime < 1) {
				r_temp = c;
				g_temp = x;
				b_temp = 0;
			} else if (h_prime >= 1 && h_prime < 2) {
				r_temp = x;
				g_temp = c;
				b_temp = 0;
			} else if (h_prime >= 2 && h_prime < 3) {
				r_temp = 0;
				g_temp = c;
				b_temp = x;
			} else if (h_prime >= 3 && h_prime < 4) {
				r_temp = 0;
				g_temp = x;
				b_temp = c;
			} else if (h_prime >= 4 && h_prime < 5) {
				r_temp = x;
				g_temp = 0;
				b_temp = c;
			} else {
				r_temp = c;
				g_temp = 0;
				b_temp = x;
			}
			rgb.r = (r_temp + m) * 255;
			rgb.g = (g_temp + m) * 255;
			rgb.b = (b_temp + m) * 255;
			return rgb;
		}
};

class Game {
	public:
		bool heldEncoder = false;
		bool isKeyboard = false;
		bool isConsumer = false;
		bool isJoystick = false;
		bool banged = false;
		bool enhanced = false;
		int miniDelay = 5;
		int shortDelay = 10;
		int mediumDelay = 50;
		int longDelay = 100;
		int longerDelay = 200;
		int longestDelay = 500;
		int tapDelay = 50;
		int recurrenceDelay = 50;
		Joystick_* joystick;
		Game() {};
		virtual void input(unsigned char input, bool pressed) {};
		virtual void begin() {
			this->deBang();
			this->deEnhance();
			if (this->isKeyboard) {
				Keyboard.begin();
			}
			if (this->isConsumer) {
				Consumer.begin();
			}
		};
		virtual void end() {
			this->deBang();
			this->deEnhance();
			if (this->isKeyboard) {
				Keyboard.end();
			}
			if (this->isConsumer) {
				Consumer.end();
			}
		};
		virtual void bang() {
			this->banged = true;
		};
		virtual void deBang() {
			this->banged = false;
		};
		virtual bool isBanged() {
			return this->banged;
		};
		virtual void enhance() {
			this->enhanced = true;
			enhancedEncoderTimer = millis();
		};
		virtual void deEnhance() {
			this->enhanced = false;
			enhancedEncoderTimer = 0;
		};
		/* keybaord */
		void key(KeyboardKeycode keyChar, bool pressed) {
			if (pressed) {
				this->keyPress(keyChar);
			} else {
				this->keyRelease(keyChar);
			}
		}
		void keyPress(KeyboardKeycode key) {
			/*
			if (DEBUG) {
				debug("press: ");
				debugln(key);
			}
			*/
			Keyboard.press(key);
		}
		void keyHold(KeyboardKeycode key, unsigned int miliseconds = 0) {
			/*
			if (DEBUG) {
				debug("KEY HOLD: ");
				debug(key);
				debug(" ");
				debugln(miliseconds);
			}
			*/
			if (miliseconds) {
				Keyboard.press(key);
				delay(miliseconds);
				Keyboard.release(key);
			}
			else {
				Keyboard.press(key);
			}
		}
		void keyTap(KeyboardKeycode key, unsigned char times = 1) {
			/*
			if (DEBUG) {
				debug("KEY TAP: ");
				debug(key);
				debug(" ");
				debugln(times);
			}
			*/
			for (unsigned char i = 0; i < times; i++) {
				Keyboard.press(key);
				delay(this->tapDelay);
				Keyboard.release(key);
				// check if last iteration
				if (i == times - 1) {
					return;
				}
				delay(this->recurrenceDelay);
			}
		}
		void keyRelease(KeyboardKeycode key) {
			/*
			if (DEBUG) {
				debug("KEY RELEASE: ");
				debugln(key);
			}
			*/
			Keyboard.release(key);
		}
		void keyReleaseAll() {
			/*
			if (DEBUG) {
				debugln("KEY RELEASE ALL");
			}
			*/
			Keyboard.releaseAll();
		}
		void consumer(ConsumerKeycode keyChar, bool pressed) {
			if (pressed) {
				this->consumerPress(keyChar);
			} else {
				this->consumerRelease(keyChar);
			}
		}
		void consumerPress(ConsumerKeycode key) {
			/*
			if (DEBUG) {
				debug("press: ");
				debugln(key);
			}
			*/
			Consumer.press(key);
		}
		void consumerHold(ConsumerKeycode key, unsigned int miliseconds = 0) {
			/*
			if (DEBUG) {
				debug("KEY HOLD: ");
				debug(key);
				debug(" ");
				debugln(miliseconds);
			}
			*/
			if (miliseconds) {
				Consumer.press(key);
				delay(miliseconds);
				Consumer.release(key);
			}
			else {
				Consumer.press(key);
			}
		}
		void consumerTap(ConsumerKeycode key, unsigned char times = 1) {
			/*
			if (DEBUG) {
				debug("KEY TAP: ");
				debug(key);
				debug(" ");
				debugln(times);
			}
			*/
			for (unsigned char i = 0; i < times; i++) {
				Consumer.press(key);
				delay(this->tapDelay);
				Consumer.release(key);
				// check if last iteration
				if (i == times - 1) {
					return;
				}
				delay(this->recurrenceDelay);
			}
		}
		void consumerRelease(ConsumerKeycode key) {
			/*
			if (DEBUG) {
				debug("KEY RELEASE: ");
				debugln(key);
			}
			*/
			Consumer.release(key);
		}
		void consumerReleaseAll() {
			/*
			if (DEBUG) {
				debugln("KEY RELEASE ALL");
			}
			*/
			Consumer.releaseAll();
		}
		/* joystick */
		/*
		void joyPress(unsigned char button) {
			if (!this->isJoystick) {
				return;
			}
			if (DEBUG) {
				debug("JOY PRESS: ");
				debugln(button);
			}
			this->joystick->pressButton(button);
		}
		void joyHold(unsigned char button, unsigned char miliseconds = 0) {
			if (!this->isJoystick) {
				return;
			}
			if (DEBUG) {
				debug("JOY HOLD: ");
				debug(button);
				debug(" ");
				debugln(miliseconds);
			}
			if (miliseconds) {
				this->joystick->pressButton(button);
				delay(miliseconds);
				this->joystick->releaseButton(button);
			}
			else {
				this->joystick->pressButton(button);
			}
		}
		void joyTap(unsigned char button, unsigned char times = 1) {
			if (!this->isJoystick) {
				return;
			}
			if (DEBUG) {
				debug("JOY TAP: ");
				debug(button);
				debug(" ");
				debugln(times);
			}
			for (unsigned char i = 0; i < times; i++) {
				this->joystick->pressButton(button);
				delay(this->tapDelay);
				this->joystick->releaseButton(button);
				// check if last iteration
				if (i == times - 1) {
					return;
				}
				delay(this->recurrenceDelay);
			}
		}
		void joyRelease(unsigned char button) {
			if (!this->isJoystick) {
				return;
			}
			if (DEBUG) {
				debug("JOY RELEASE: ");
				debugln(button);
			}
			this->joystick->releaseButton(button);
		}
		void joyReleaseAll() {
			if (!this->isJoystick) {
				return;
			}
			for(unsigned char i = 0; i < 64; i++) {
				this->joystick->releaseButton(i);
			}
		}
		*/
};

class Controller {
	public:
		const char* name;
		Game* game;
		Color* color;
		Color* colorFeedback;
		Color* colorBanged;
		Controller(
			const char* name,
			Game* game,
			Color* color,
			Color* colorFeedback,
			Color* colorBanged
		) {
			this->name = name;
			this->game = game;
			this->color = color;
			this->colorFeedback = colorFeedback;
			this->colorBanged = colorBanged;
		};
		void input(unsigned char input, bool pressed) {
			this->game->input(input, pressed);
		};
		void end() {
			this->game->end();
		};
		void begin() {
			// this->debang();
			this->game->begin();
		};
		float getIntensity() {
			return this->color->getLightness();
		};
		void setIntensity(float intensity) {
			this->color->setLightness(intensity);
		};
		void bang() {
			this->game->bang();
		};
		void deBang() {
			this->game->deBang();
		};
		bool isBanged() {
			return this->game->isBanged();
		};
		void enhance() {
			this->game->enhance();
		};
		void deEnhance() {
			this->game->deEnhance();
		};
		Color* getColor() {
			return this->color;
		};
};


