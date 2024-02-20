#include <Arduino.h>
#include <Keypad.h>
#include <Joystick.h>
#include <HID-Project.h>
#include <RotaryEncoder.h>
#include <EEPROM.h>

#include <Settings.h>
#include <Bang.h>
#include <Pins.h>

#if DEBUG >= 1
	#include <Game/BangDebug.h>
#endif
#include <Game/AssettoCorsaCompetizione.h>
#include <Game/GameJoystick.h>
#include <Game/GameKeyboard.h>
// #include <Game/MediaKeyboard.h>


// prepare functions
int minMax(double value, int min, int max);
void setController(unsigned char index);
void sendButton(Key button);
void sendRotaryPush(unsigned char button, bool pressed);
void sendRotaryEncoder(unsigned char index, char direction);

void setBrightness(unsigned char value);
void setRGB(unsigned char r, unsigned char g, unsigned char b);
void setRGB(RGB rgb);
void setHSL(HSL hsl);
void setBangLED(unsigned char value);
void setLights(unsigned char value);

void modeDefault();
void modeBanged();
void modeActivateSystem();

void wakeUp();
void stayAwake();
void sleep();
void hybridSleep();

void bootAnimation();

void loadSettings();
void saveSettings();

Keypad buttons = Keypad(
	makeKeymap(buttonsGrid),
	matrixSenders,
	matrixReceivers,
	MATRIX_SENDERS,
	MATRIX_RECEIVERS
);

#define NUM_ENCODERS 3
RotaryEncoder encoders[NUM_ENCODERS] = {
	RotaryEncoder(ROTARY_ENCODER_M_DT_PIN, ROTARY_ENCODER_M_CL_PIN, RotaryEncoder::LatchMode::FOUR3),
	RotaryEncoder(ROTARY_ENCODER_L_DT_PIN, ROTARY_ENCODER_L_CL_PIN, RotaryEncoder::LatchMode::FOUR3),
	RotaryEncoder(ROTARY_ENCODER_R_DT_PIN, ROTARY_ENCODER_R_CL_PIN, RotaryEncoder::LatchMode::FOUR3)
};
long encoderValue[NUM_ENCODERS];

// rotary encoders up actions
unsigned char rotaryUpPins[NUM_ENCODERS] = {
	R_ENCODER_M_UP,
	R_ENCODER_L_UP,
	R_ENCODER_R_UP
};
// rotary encoders down actions
unsigned char rotaryDownPins[NUM_ENCODERS] = {
	R_ENCODER_M_DN,
	R_ENCODER_L_DN,
	R_ENCODER_R_DN
};

// buttons push for rotary encoders pins
unsigned char rotaryPushPins[NUM_ENCODERS] = {
	ROTARY_ENCODER_M_SWT_PIN,
	ROTARY_ENCODER_L_SWT_PIN,
	ROTARY_ENCODER_R_SWT_PIN
};
// id buttons push for rotary encoders
unsigned char rotaryPushButtonIndex[NUM_ENCODERS] = {
	B_ENCODER_M_PH,
	B_ENCODER_L_PH,
	B_ENCODER_R_PH
};

unsigned char rotaryPushStates[NUM_ENCODERS] = {
	0,
	0,
	0
};

Joystick_ joystick(
	JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
	BANGED * 2, 2, // button count, hat switch count
	false, false, false, // x, y, z
	false, false, false, // rx, ry, rz
	false, false, // rudder, throttle
	false, false, false // accelerator, brake, steering
);

Controller controllers[] = {
	#if DEBUG == 1
		Controller(
			"Debug",
			new BangDebug(),
			new Color(0, 1.0, 0.5), // default hsl
			new Color(300, 1.0, 0.5), // pressed hsl
			new Color(240, 1.0, 0.5) // banged hsl
		),
	#endif
	Controller(
		"ACC",
		new AssettoCorsaCompetizione(),
		new Color(120, 1.0, 0.5), // default hsl
		new Color(180, 1.0, 0.5), // pressed hsl
		new Color(240, 1.0, 0.5) // banged hsl
	),
	Controller(
		"Joystick",
		new GameJoystick(&joystick),
		new Color(200, 1.0, 0.5),
		new Color(250, 1.0, 0.5),
		new Color(300, 1.0, 0.5)
	),
	Controller(
		"Keyboard",
		new GameKeyboard(),
		new Color(24, 1.0, 0.5),
		new Color(40, 1.0, 0.5),
		new Color(180, 1.0, 0.5)
	)
	/*,
	Controller(
		"MediaKeyboard",
		new MediaKeyboard(),
		new Color(60, 1.0, 0.5),
		new Color(30, 1.0, 0.5),
		new Color(0, 1.0, 0.5)
	)
	*/
};
unsigned int controllerCount = sizeof(controllers) / sizeof(controllers[0]);
Controller controller = controllers[controllerIndex];

// functions
int minMax(double value, int min, int max) {
	if (value < min) {
		value = min;
	}
	else if (value > max) {
		value = max;
	}
	return round(value);
};

void setController(unsigned char index) {
	debug("Setting Controller: ");
	debugln(index);
	controller.end();
	controllerIndex = index % controllerCount;
	controller = controllers[controllerIndex];
	controller.begin();
	modeDefault();
	controllerReadyTimer = timer;
}

void sendButton(Key button) {
	stayAwake();
	if (controllerReadyTimer) {
		debugln("!Ready");
		return;
	}
	bool pressed = false;
	switch (button.kstate) {
		case PRESSED:
			pressed = true;
		break;
		case RELEASED:
		break;
		default:
			return;
	}
	if (button.kchar == B_BANG) {
		if (pressed) {
			if (activateSystemTimer) {
				modeDefault();
				return;
			}
			prepareSystemTimer = timer;
			if (controller.isBanged()) {
				modeDefault();
				return;
			}
			modeBanged();
			return;
		}
		prepareSystemTimer = 0;
		return;
	}
	if (pressed) {
		feedbackCount++;
		feedbackTimer = timer;
		// feedback(true);
		if (activateSystemTimer) {
			switch (button.kchar) {
				case B_ENGINE:
					debugln("CHANGE PROFILE");
					setController(controllerIndex + 1);
				break;
				case B_IGNITION:
					bangTimedMode = !bangTimedMode;
					debug("Bang Toggle Mode: ");
					debugln(bangTimedMode);
				break;
				case B_PIT_LIMITER:
					saveSettings();
				break;
			}
			return;
		}
		if (controller.isBanged()) {
			controller.input((button.kchar + BANGED), pressed);
			return;
		}
		controller.input(button.kchar, pressed);
		return;
	}
	if (controller.isBanged()) {
		controller.input((button.kchar + BANGED), pressed);
		if (feedbackCount) {
			feedbackCount--;
		}
		return;
	}
	if (feedbackCount) {
		feedbackCount--;
	}
	controller.input(button.kchar, pressed);
}
void sendRotaryPush(unsigned char index, bool pressed) {
	stayAwake();
	if (controllerReadyTimer) {
		debugln("!Ready");
		return;
	}
	unsigned char button = rotaryPushButtonIndex[index];
	if (pressed) {
		feedbackCount++;
		feedbackTimer = timer;
	}
	else if (feedbackCount) {
		feedbackCount--;
	}
	if (controller.isBanged()) {
		controller.input((button + BANGED), pressed);
		return;
	}
	controller.input(button, pressed);
}
void sendRotaryEncoder(unsigned char index, char direction) {
	stayAwake();
	if (controllerReadyTimer) {
		debugln("!Ready");
		return;
	}
	if (activateSystemTimer) {
		switch (index) {
			case 0:
				if (direction == 1) {
					setBrightness(brightness + brightnessStep);
				}
				else {
					setBrightness(brightness - brightnessStep);
				}
				activateSystemTimer = timer;
			break;
		}
		return;
	}
	feedbackTimer = timer;
	switch (direction) {
		case 1:
			if (controller.isBanged()) {
				controller.input((rotaryUpPins[index] + BANGED), true);
				return;
			}
			controller.input(rotaryUpPins[index], true);
			return;
		case -1:
			if (controller.isBanged()) {
				controller.input((rotaryDownPins[index] + BANGED), true);
				return;
			}
			controller.input(rotaryDownPins[index], true);
			return;
		default:
			return;
	}
}

void setRGB(unsigned char r, unsigned char g, unsigned char b) {
	analogWrite(LED_R_PIN, r);
	analogWrite(LED_G_PIN, g);
	analogWrite(LED_B_PIN, b);
}
void setRGB(RGB rgb) {
	setRGB(rgb.r, rgb.g, rgb.b);
}
void setHSL(HSL hsl) {
	Color color = Color(hsl.h, hsl.s, hsl.l);
	setRGB(color.getRGB());
}
void setBangLED(unsigned char value) {
	analogWrite(LED_BANG_PIN, 
		min(
			max(
				value,
				brightnessMinValue
			),
			brightnessMaxValue
		)
	);
}
void setLights(unsigned char value) {
	analogWrite(LED_LIGHTS_PIN, 
		min(
			max(
				value,
				brightnessMinValue
			),
			brightnessMaxValue
		)
	);
}
void setBrightness(unsigned char value) {
	brightness = minMax(value, brightnessMinValue, brightnessMaxValue);
	setLights(brightness);
	setBangLED(brightness);
	float l = (float) brightness / 255;
	controller.color->setLightness(l);
	controller.colorBanged->setLightness(l);
	controller.colorFeedback->setLightness(l);
}

void modeDefault() {
	feedbackTimer = 0;
	enhancedEncoderTimer = 0;
	bangedTimer = 0;
	prepareSystemTimer = 0;
	activateSystemTimer = 0;
	setBrightness(brightness);
	setRGB(controller.color->getRGB());
	controller.deBang();
	controller.deEnhance();
}
void modeBanged() {
	setRGB(controller.colorBanged->getRGB());
	if (bangTimedMode) {
		bangedTimer = timer;
	}
	controller.bang();
}
void modeActivateSystem() {
	if (activateSystemTimer) {
		return;
	}
	bangedTimer = 0;
	prepareSystemTimer = 0;
	activateSystemTimer = timer;
	controller.deBang();
	controller.deEnhance();
}

void wakeUp() {
	sleeping = 0;
	RGB rgb = controller.color->getRGB();
	setRGB(rgb.r, rgb.g, rgb.b);
	setLights(brightness);
	setBangLED(brightness);
}
void stayAwake() {
	sleepTimer = timer;
	if (sleeping > 0) {
		wakeUp();
	}
}
void sleep() {
	sleeping = 1;
	Color color = Color(controller.color->getHSL());
	float l = color.getLightness();
	color.setLightness(l / 2);
	unsigned char b = l * 255;
	setRGB(color.getRGB());
	setLights(b);
	setBangLED(b);
}
void hybridSleep() {
	sleeping = 2;
	Color color = Color(controller.color->getHSL());
	color.setLightness(0);
	setRGB(color.getRGB());
	setLights(0);
	setBangLED(0);
}

void bootAnimation() {
	Color color = Color(0, 1.0, 0.0);
	float percent;
	for (unsigned int i = 0; i < 360; i++) {
		percent = (float) i / 720;
		color.setHue(i);
		color.setLightness(percent);
		setRGB(color.getRGB());
		delay(5);
	}
}

void loadSettings() {
	unsigned char c;
	bool b;
	c = EEPROM.read(0);
	if (c != 255) {
		brightness = c;
	}
	c = EEPROM.read(1);
	if (c != 255) {
		controllerIndex = c;
	}
	b = EEPROM.read(2);
	if (b) {
		bangTimedMode = (bool) b;
	}
}
void saveSettings() {
	if (EEPROM.read(0) != brightness) {
		EEPROM.write(0, brightness);
	}
	if (EEPROM.read(1) != controllerIndex) {
		EEPROM.write(1, controllerIndex);
	}
	if (EEPROM.read(2) != bangTimedMode) {
		EEPROM.write(2, bangTimedMode);
	}
	for (unsigned char i = 0; i < 3; i++) {
		delay(100);
		setLights(0);
		delay(100);
		setLights(brightness);
	}
}

void setup() {
	delay(500);
	pinMode(LED_BANG_PIN, OUTPUT);
	pinMode(LED_LIGHTS_PIN, OUTPUT);
	pinMode(LED_R_PIN, OUTPUT);
	pinMode(LED_G_PIN, OUTPUT);
	pinMode(LED_B_PIN, OUTPUT);
	pinMode(ROTARY_ENCODER_M_SWT_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_L_SWT_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_R_SWT_PIN, INPUT_PULLUP);
	/*
	// INPUT_PULLUP not needed as they are set in RotaryEncoder.cpp
	pinMode(ROTARY_ENCODER_M_DT_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_M_CL_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_L_DT_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_L_CL_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_R_DT_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_R_CL_PIN, INPUT_PULLUP);
	*/
	bootAnimation();
	delay(1000);
	setBangLED(32);
	delay(1000);
	setLights(32);
	delay(1000);
	if (DEBUG) {
		Serial.begin(115200);
		setBangLED(128);
		delay(100);
		setBangLED(0);
		delay(100);
		setBangLED(128);
		delay(100);
		setBangLED(32);
	}
	buttons.setDebounceTime(50);
	debugln("Bang Evolution");
	timer = millis();
	loadSettings();
	setController(controllerIndex);
	stayAwake();
	// TXLED0;
	// RXLED0;
	// pinMode(17, OUTPUT);
	// digitalWrite(17, HIGH);
	// PCICR |= (1 << PCIE0);
	// PCMSK0 |= (1 << PCINT2) | (1 << PCINT4);
	// sei();
}

void loop() {
	/* timer events */
	timer = millis();
	if (controllerReadyTimer) {
		if (timer - controllerReadyTimer < controllerReadyDelay) {
			setBangLED(0);
			delay(50);
			setBangLED(brightness);
			delay(50);
			return;
		}
		controllerReadyTimer = 0;
	}
	/* input events */
	for (unsigned char i = 0; i < NUM_ENCODERS; i++) {
		encoders[i].tick();
		int newPosition = encoders[i].getPosition();
		if (newPosition != encoderValue[i]) {
			encoderValue[i] = newPosition;
			encoderChanged = true;
			char direction = (char) encoders[i].getDirection();
			sendRotaryEncoder(i, direction);
		}
		if (digitalRead(rotaryPushPins[i]) == LOW) {
			if (rotaryPushStates[i] == 0) {
				rotaryPushStates[i] = 1;
				sendRotaryPush(i, true);
			}
		} else {
			if (rotaryPushStates[i] == 1) {
				rotaryPushStates[i] = 0;
				sendRotaryPush(i, false);
			}
		}
	}
	if (buttons.getKeys()) {
		for (unsigned char i = 0; i < LIST_MAX; i++) {
			if (buttons.key[i].stateChanged) {
				sendButton(buttons.key[i]);
			}
		}
	}
	/* sleep events */
	switch (sleeping) {
		case 1: // unit is in hyper sleep...
			delay(30);
			if (timer - sleepTimer > hybridSleepDelay) {
				hybridSleep();
			}
		break;
		case 2: // unit is in hyper sleep...
			delay(60);
		break;
		default:
			// delayMicroseconds(50);
			if (timer - sleepTimer > sleepDelay) {
				sleep();
			}
		break;
	}
	/* debug events */
	#if DEBUG == 1
		loopCount++;
		if (timer - debugTimer > 10000) {
			bench("Loop: ");
			bench(loopCount);
			bench(" | CTRL: ");
			benchln(controller.name);
			loopCount = 0;
			debugTimer = timer;
		}
	#endif
	/* feedback event */
	if (feedbackTimer) {
		if (!bangBlinkTimer) {
			bangBlinkTimer = timer;
		}
		if (timer - bangBlinkTimer > feedbackInterval) {
			bangBlinkTimer = timer;
			if (feedbackBlink) {
				setBangLED(brightness);
			}
			else {
				setBangLED(0);
			}
			feedbackBlink = !feedbackBlink;
		}
		if (!feedbackCount
			&& timer - feedbackTimer > feedbackDuration) {
			feedbackTimer = 0;
			bangBlinkTimer = 0;
			feedbackBlink = false;
			setBangLED(brightness);
		}
	}
	/* pulse event */
	if (enhancedEncoderTimer) {
		if (!bangBlinkTimer) {
			bangBlinkTimer = timer;
		}
		if (feedbackTimer) {
			enhancedEncoderTimer = timer;
		}
		if (timer - bangBlinkTimer > pulseInterval) {
			bangBlinkTimer = timer;
			if (pulseBlink) {
				setBangLED(brightness);
			}
			else {
				setBangLED(0);
			}
			pulseBlink = !pulseBlink;
		}
		if (timer - enhancedEncoderTimer > enhancedEncoderDuration) {
			controller.deEnhance();
			bangBlinkTimer = 0;
			pulseBlink = false;
			setBangLED(brightness);
		}
	}
	/* bang events */
	if (bangTimedMode && bangedTimer) {
		if (!bangBlinkTimer) {
			bangBlinkTimer = timer;
		}
		if (timer - bangedTimer > bangedDuration) {
			Serial.println("!banged timed");
			bangedTimer = 0;
			bangBlinkTimer = 0;
			bangedBlink = false;
			setRGB(controller.color->getRGB());
			controller.deBang();
		}
		if (timer - bangBlinkTimer > bangedInterval) {
			bangBlinkTimer = timer;
			if (bangedBlink) {
				setRGB(controller.color->getRGB());
			}
			else {
				setRGB(controller.colorBanged->getRGB());
			}
			bangedBlink = !bangedBlink;
		}
	}
	/* prepare tp emter system */
	if (prepareSystemTimer && timer - prepareSystemTimer > prepareSystemDuration && !activateSystemTimer) {
		modeActivateSystem();
	}
	/* system events */
	if (activateSystemTimer) {
		if (!engineBlinkTimer) {
			engineBlinkTimer = timer;
		}
		if (feedbackTimer) {
			activateSystemTimer = timer;
		}
		if (engineBlinkTimer && timer - engineBlinkTimer > activateSystemInterval) {
			engineBlinkTimer = timer;
			if (activateSystemBlink) {
				setRGB(controller.colorBanged->getRGB());
			}
			else {
				setRGB(controller.colorFeedback->getRGB());
			}
			activateSystemBlink = !activateSystemBlink;
		}
	}
}
