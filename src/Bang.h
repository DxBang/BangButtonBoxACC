#ifndef BANG_h
	#define BANG_h
#endif

#ifndef JOYSTICK_h
	#include <Joystick.h>
#endif
#ifndef HID_PROJECT_VERSION
	#include <HID-Project.h>
#endif

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
#define B_NAV_UP 9
#define B_NAV_DOWN 10
#define B_NAV_LEFT 11
#define B_NAV_RIGHT 12
#define B_NAV_SELECT 13
#define B_MFD_ELECTRONICS 14
#define B_MFD_PITSTOP 15
#define B_MFD_POSITIONS 16
#define B_MFD_STANDINGS 17
#define B_EXTRA_1 18
#define B_EXTRA_2 19
#define B_EXTRA_3 20

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


unsigned long timer = 0;
unsigned long debugTimer = 0;
unsigned long loopCount = 0;
unsigned char feedbackCount = 0;

const unsigned char feedbackLimit = 10;


const unsigned short controllerReadyDelay = 1000;


bool feedbackBlink = false;
bool pulseBlink = false;
bool bangedBlink = false;
bool activateSystemBlink = false;
unsigned long feedbackTimer = 0;
unsigned long pulseTimer = 0;
unsigned long bangedTimer = 0;
unsigned long bangedModeTimer = 0;
unsigned long enhancedEncoderTimer = 0;
unsigned long prepareSystemTimer = 0;
unsigned long activateSystemTimer = 0;
unsigned long activateSystemModeTimer = 0;
unsigned long controllerReadyTimer = 0;

const unsigned char feedbackInterval = 50;
const unsigned short pulseInterval = 500;
const unsigned short bangedInterval = 500;
const unsigned short activateSystemInterval = 1000;

const unsigned short bangModeDuration = 3000;
const unsigned short enhancedEncoderDuration = 5000;
const unsigned short prepareSystemDuration = 2000;
const unsigned short activateSystemModeDuration = 20000;


unsigned char brightness = 100; // for LED_LIGHTS_PIN, LED_BANG_PIN
unsigned char brightnessMinValue = 0; // for LED_LIGHTS_PIN, LED_BANG_PIN, LED_R_PIN, LED_G_PIN, LED_B_PIN
unsigned char brightnessMaxValue = 127;	// for LED_LIGHTS_PIN, LED_BANG_PIN. LED_R_PIN, LED_G_PIN, LED_B_PIN
unsigned char brightnessStep = 1; // for LED_LIGHTS_PIN, LED_BANG_PIN, LED_R_PIN, LED_G_PIN, LED_B_PIN

unsigned char sleeping = 0;
unsigned long sleepTimer = 0;


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
		Color(HSL hsl) : hue(hsl.h), saturation(hsl.s), lightness(hsl.l) {}
		/*
		Color(RGB rgb) {
			float r = rgb.r / 255.0;
			float g = rgb.g / 255.0;
			float b = rgb.b / 255.0;
			float c_max = max(r, max(g, b));
			float c_min = min(r, min(g, b));
			float delta = c_max - c_min;
			float h, s, l;
			if (delta == 0) {
				h = 0;
			} else if (c_max == r) {
				h = 60 * fmod(((g - b) / delta), 6);
			} else if (c_max == g) {
				h = 60 * (((b - r) / delta) + 2);
			} else if (c_max == b) {
				h = 60 * (((r - g) / delta) + 4);
			}
			if (h < 0) {
				h += 360;
			}
			l = (c_max + c_min) / 2;
			if (delta == 0) {
				s = 0;
			} else {
				s = delta / (1 - abs(2 * l - 1));
			}
			this->hue = h;
			this->saturation = s;
			this->lightness = l;
		}
		*/
		Color(unsigned short hue, float saturation, float lightness) : hue(hue), saturation(saturation), lightness(lightness) {}

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
		// Joystick_ *joystick;
		Game() {};
		virtual void button(unsigned char button, bool pressed) {};
		virtual void begin() {
			if (this->isKeyboard) {
				Keyboard.begin();
			}
			if (this->isConsumer) {
				Consumer.begin();
			}
		};
		virtual void end() {
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
		virtual void debang() {
			this->banged = false;
		};
		virtual bool isBanged() {
			return this->banged;
		};
		virtual void enhance() {
			this->enhanced = true;
			enhancedEncoderTimer = millis();
			pulseTimer = millis();
			feedbackTimer = 0;
		};
		virtual void deEnhance() {
			this->enhanced = false;
			enhancedEncoderTimer = 0;
			pulseTimer = 0;
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
				Serial.print("press: ");
				Serial.println(key);
			}
			*/
			Keyboard.press(key);
		}
		void keyHold(KeyboardKeycode key, unsigned int miliseconds = 0) {
			/*
			if (DEBUG) {
				Serial.print("KEY HOLD: ");
				Serial.print(key);
				Serial.print(" ");
				Serial.println(miliseconds);
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
				Serial.print("KEY TAP: ");
				Serial.print(key);
				Serial.print(" ");
				Serial.println(times);
			}
			*/
			for (unsigned char i = 0; i < times; i++) {
				Serial.print("TAP: ");
				Serial.print(key);
				Serial.print(" ");
				Serial.print(i);
				Serial.print(" ");
				Serial.println(times);
				


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
				Serial.print("KEY RELEASE: ");
				Serial.println(key);
			}
			*/
			Keyboard.release(key);
		}
		void keyReleaseAll() {
			/*
			if (DEBUG) {
				Serial.println("KEY RELEASE ALL");
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
				Serial.print("press: ");
				Serial.println(key);
			}
			*/
			Consumer.press(key);
		}
		void consumerHold(ConsumerKeycode key, unsigned int miliseconds = 0) {
			/*
			if (DEBUG) {
				Serial.print("KEY HOLD: ");
				Serial.print(key);
				Serial.print(" ");
				Serial.println(miliseconds);
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
				Serial.print("KEY TAP: ");
				Serial.print(key);
				Serial.print(" ");
				Serial.println(times);
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
				Serial.print("KEY RELEASE: ");
				Serial.println(key);
			}
			*/
			Consumer.release(key);
		}
		void consumerReleaseAll() {
			/*
			if (DEBUG) {
				Serial.println("KEY RELEASE ALL");
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
				Serial.print("JOY PRESS: ");
				Serial.println(button);
			}
			this->joystick->pressButton(button);
		}
		void joyHold(unsigned char button, unsigned char miliseconds = 0) {
			if (!this->isJoystick) {
				return;
			}
			if (DEBUG) {
				Serial.print("JOY HOLD: ");
				Serial.print(button);
				Serial.print(" ");
				Serial.println(miliseconds);
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
				Serial.print("JOY TAP: ");
				Serial.print(button);
				Serial.print(" ");
				Serial.println(times);
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
				Serial.print("JOY RELEASE: ");
				Serial.println(button);
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
		float intensity;
		Controller(
			const char* name,
			Game* game,
			Color* color,
			Color* colorFeedback,
			Color* colorBanged,
			float intensity = 0.5
		) {
			this->name = name;
			this->game = game;
			this->color = color;
			this->colorFeedback = colorFeedback;
			this->colorBanged = colorBanged;
			this->intensity = intensity;
		};
		void button(unsigned char button, bool pressed) {
			this->game->button(button, pressed);
		};
		void end() {
			// this->debang();
			this->game->end();
		};
		void begin() {
			// this->debang();
			this->game->begin();
		};
		float getIntensity() {
			return this->intensity;
		};
		void setIntensity(float intensity) {
			this->intensity = intensity;
		};
		void bang() {
			this->game->bang();
		};
		void debang() {
			this->game->debang();
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


