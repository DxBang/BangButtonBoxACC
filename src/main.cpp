#include <Arduino.h>
#include <Keypad.h>
#include <Joystick.h>
#include <HID-Project.h>
#include <RotaryEncoder.h>
#include <Bang.h>
#include <Game/BangDebug.h>
#include <Game/AssettoCorsaCompetizione.h>

#define DEBUG 1

// 10 mins / 900000 ( 5000 debug )
#define SLEEP_TIME 900000
// 30 mins / 1800000 ( 20000 debug )
#define HYPER_SLEEP_TIME 1800000

/*
D0	Rotary Encoder Left CLK
D1	Rotary Encoder Left DT
D2	Rotary Encoder Right DT
D3	Lights
D4	Matrix Col 2
D5	Matrix Col 3
D6	Matrix Col 4
D7	Rotary Encoder Right CLK
D8	Rotary Encoder Middle CLK
D9	RGB LED R
D10	RGB LED G
D11	RGB LED B
D12	Rotary Encoder Middle SWT
D13	Bang LED
D14	Rotary Encoder Left SWT
D15	Rotary Encoder Right SWT
D16	Rotary Encoder Middle DT
D17	Can't use for output
A0	Matrix Row 1
A1	Matrix Row 2
A2	Matrix Row 3
A3	Matrix Row 4
A4	Matrix Row 5
A5	Matrix Col 1

~ = PWM
^ = INT
/ = PCINT

              Board: Arduino Micro
                 ------USB------
        Bang LED | ~D13    D12 | RE Middle SWT
                 | 3V3   ~/D11 | RGB LED B
                 | AREF  ~/D10 | RGB LED G
    Matrix Row 1 | A0     ~/D9 | RGB LED R
    Matrix Row 2 | A1      /D8 | RE Middle CLK
    Matrix Row 3 | A2      ^D7 | RE Right CLK
    Matrix Row 4 | A3      ~D6 | Matrix Col 4
    Matrix Row 5 | A4      ~D5 | Matrix Col 3
    Matrix Col 1 | A5       D4 | Matrix Col 2
                 |         ~D3 | Lights
                 |        ~^D2 | RE Right DT
       5V for RE | 5V      GND | GND
                 | RST     RST |
             GND | GND     ^D0 | RE Left CLK
                 | VIN     ^D1 | RE Left DT
    RE Left SWT  | D14    /D17 | 
   RE Right SWT  | D15    /D16 | RE Middle DT
                 ---------------

*/


#include <Smurf.h>
// #include <Dev.h>

/*


*/

// check of PIN has PWM


// put function declarations here:


unsigned char controllerIndex = 0;



unsigned char visualState = 0; // 0 = default, 1 = pressed, 2 = banged, 3 = activateChangeProfile




unsigned char pressCount = 0;


bool encoderChanged = false;

// prepare functions
void setRGB(unsigned char r, unsigned char g, unsigned char b);
void setRGB(RGB rgb);
void setHSL(HSL hsl);
void setBangLED(unsigned char value);
void setLights(unsigned char value);
void setController(unsigned char index);

void feedback();

void modeDefault();
void modeBanged();
void modeActivateChangeProfile();

void sendInput(unsigned char button, bool pressed);
void sendButton(Key button);
void sendRotaryPush(unsigned char button, bool pressed);
void sendRotaryEncoder(unsigned char index, char direction);

void wakeUp();
void stayAwake();
void sleep();
void hyperSleep();


Keypad buttons = Keypad(
	makeKeymap(buttonsGrid),
	rowPins,
	colPins,
	NUM_ROWS,
	NUM_COLS
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



Controller controllers[] = {
	Controller(
		"Bang Debug",
		new BangDebug(),
		new Color(0, 1.0, 0.5), // default hsl
		new Color(300, 1.0, 0.0), // pressed hsl
		new Color(240, 1.0, 0.5), // banged hsl
		0.5
	),
	Controller(
		"Assetto Corsa Competizione",
		new AssettoCorsaCompetizione(),
		new Color(120, 1.0, 0.5), // default hsl
		new Color(160, 1.0, 1.0), // pressed hsl
		new Color(240, 1.0, 0.5), // banged hsl
		0.5
	)
};
unsigned int controllerCount = sizeof(controllers) / sizeof(controllers[0]);
Controller controller = controllers[controllerIndex];


// functions
void setController(unsigned char index) {
	if (DEBUG) {
		Serial.print("Setting Controller: ");
		Serial.println(index);
	}
	// feedback(false);
	controllers[controllerIndex].end();
	controllerIndex = index % controllerCount;
	controller = controllers[controllerIndex];
	controller.begin();
	if (DEBUG) {
		Serial.print("Controller: ");
		Serial.println(controller.name);
	}
	modeDefault();
	// pressCount = 1;
	controllerReady = false;
	controllerChangeTimer = timer;
}

void sendInput(unsigned char button, bool pressed) {
	if (DEBUG) {
		Serial.print("Send Input: ");
		Serial.print(button);
		Serial.print(" | ");
		Serial.println(pressed);
	}
	if (controller.isBanged()) {
		// modeFeedback();
		controller.button((button + BANGED), pressed);
		// controller.debang();
		bangedTimer = 0;
		return;
	}
	controller.button(button, pressed);
}
void sendButton(Key button) {
	stayAwake();
	if (!controllerReady) {
		if (DEBUG) {
			Serial.println("Controller Not Ready");
		}
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
	/*
	Serial.print("Button: ");
	Serial.print(button.kchar);
	Serial.print(" | ");
	Serial.print(button.kcode);
	Serial.print(" | ");
	Serial.println(button.kstate);
	*/
	
	
	if (button.kchar == B_BANG) {
		if (pressed) {
			prepareChangeProfileTimer = timer;
			// blink = !controller.isBanged();
			if (controller.isBanged()) {
				if (DEBUG) {
					Serial.println("debang");
				}
				// setRGB(controller.color->getRGB());
				modeDefault();
				return;
			}
			if (DEBUG) {
				Serial.println("BANG");
			}
			// setRGB(controller.colorBanged->getRGB());
			modeBanged();
			return;
		}
		prepareChangeProfileTimer = 0;
		return;
	}
	if (pressed) {
		pressCount++;
		feedback();
		// feedback(true);
		if (activateChangeProfile && button.kchar == B_ENGINE) {
			if (DEBUG) {
				Serial.println("ACTIVATE CHANGE PROFILE");
			}
			setController(controllerIndex + 1);
			return;
		}
		if (controller.isBanged()) {
			// modeFeedback();
			if (button.kchar == B_IGNITION) {
				bangToggleMode = !bangToggleMode;
				if (DEBUG) {
					Serial.print("Bang Toggle Mode: ");
					Serial.println(bangToggleMode);
				}
				modeDefault();
				return;
			}
			controller.button((button.kchar + BANGED), pressed);
			// controller.debang();
			bangedTimer = 0;
			return;
		}
		// modeFeedback();
		controller.button(button.kchar, pressed);
		return;
	}
	if (controller.isBanged()) {
		controller.button((button.kchar + BANGED), pressed);
		if (!bangToggleMode) {
			controller.debang();
		}
		pressCount--;
		return;
	}
	pressCount--;
	controller.button(button.kchar, pressed);
}
void sendRotaryPush(unsigned char index, bool pressed) {
	stayAwake();
	if (!controllerReady) {
		if (DEBUG) {
			Serial.println("Controller Not Ready");
		}
		return;
	}
	unsigned char button = rotaryPushButtonIndex[index];
	/*
	Serial.print("Rotary Push: ");
	Serial.print(button);
	Serial.print(" | ");
	Serial.println(pressed);
	*/
	if (pressed) {
		pressCount++;
		feedback();
	}
	else {
		pressCount--;
	}
	if (controller.isBanged()) {
		controller.button((button + BANGED), pressed);
		// controller.debang();
		return;
	}
	controller.button(button, pressed);
}
void sendRotaryEncoder(unsigned char index, char direction) {
	stayAwake();
	if (!controllerReady) {
		if (DEBUG) {
			Serial.println("Controller Not Ready");
		}
		return;
	}
	/*
	Serial.print("Rotary Encoder: ");
	Serial.print(index);
	Serial.print(" | ");
	Serial.println(direction);
	*/
	
	if (controller.isBanged()) {
		if (index == 0) {
			// change brightness to up/down to 0-255
			if (direction == 1) {
				brightness += brightnessStep;
				if (brightness > brightnessMaxValue) {
					brightness = brightnessMaxValue;
				}
			}
			else {
				brightness -= brightnessStep;
				if (brightness < brightnessMinValue) {
					brightness = brightnessMinValue;
				}
			}
			setLights(brightness);
			setBangLED(brightness);
			// adjust controller light intensity from brightness of 0-127 to 0.0-0.5
			HSL c = controller.color->getHSL();
			c.l = (float) brightness / (float) brightnessMaxValue * 0.5;
			controller.color->setHSL(c.h, c.s, c.l);
			c = controller.colorFeedback->getHSL();
			c.l = (float) brightness / (float) brightnessMaxValue * 1.0;
			controller.colorFeedback->setHSL(c.h, c.s, c.l);
			c = controller.colorBanged->getHSL();
			c.l = (float) brightness / (float) brightnessMaxValue * 0.5;
			controller.colorBanged->setHSL(c.h, c.s, c.l);

			setHSL(c);
			return;
		}
	}

	switch (direction) {
		case 1:
			feedback();
			if (controller.isBanged()) {
				controller.button((rotaryUpPins[index] + BANGED), true);
				return;
			}
			controller.button(rotaryUpPins[index], true);
			return;
		case -1:
			feedback();
			if (controller.isBanged()) {
				controller.button((rotaryDownPins[index] + BANGED), true);
				return;
			}
			controller.button(rotaryDownPins[index], true);
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

void feedback() {
	if (!feedbackTimer) {
		feedbackTimer = timer;
	}
	feedbackCount = 0;
}

void modeDefault() {
	
	feedbackTimer = 0;
	pulseTimer = 0;
	bangedTimer = 0;
	prepareChangeProfileTimer = 0;
	activateChangeProfileTimer = 0;
	activateChangeProfile = false;
	setRGB(controller.color->getRGB());
	// get brightness from controller intensity as float and convert to 0-255 of min and max
	brightness = min(
		max(
			(unsigned char) (controller.getIntensity() * 255),
			brightnessMinValue
		),
		brightnessMaxValue
	);
	setLights(brightness);
	setBangLED(brightness);
	controller.debang();
}
void modeBanged() {
	setRGB(controller.colorBanged->getRGB());
	if (!bangToggleMode) {
		bangedTimer = timer;
	}
	feedbackTimer = timer;
	controller.bang();
}
void modeActivateChangeProfile() {
	if (DEBUG) {
		Serial.println("ACTIVATE CHANGE PROFILE");
	}
	if (activateChangeProfile) {
		return;
	}
	bangedTimer = 0;
	prepareChangeProfileTimer = 0;
	activateChangeProfile = true;
	activateChangeProfileTimer = timer;
	pulseTimer = timer;
	bangedBlink = controller.isBanged();
	controller.debang();
}

void wakeUp() {
	if (DEBUG) {
		Serial.println("Waking...");
	}
	sleeping = 0;
	RGB rgb = controller.color->getRGB();
	setRGB(rgb.r, rgb.g, rgb.b);
	setLights(brightness);
	setBangLED(brightness / 2);
}
void stayAwake() {
	sleepTimer = timer;
	if (sleeping > 0) {
		wakeUp();
	}
}
void sleep() {
	if (DEBUG) {
		Serial.println("Sleeping...");
	}
	sleeping = 1;
	HSL c = controller.color->getHSL();
	c.l = 0.1;
	Color color = Color(c.h, c.s, c.l);
	setRGB(color.getRGB());
	setLights(c.l);
	setBangLED(c.l);
}
void hyperSleep() {
	if (DEBUG) {
		Serial.println("Hyper Sleeping...");
	}
	sleeping = 2;
	HSL c = controller.color->getHSL();
	c.l = 0.005;
	Color color = Color(c.h, c.s, c.l);
	setRGB(color.getRGB());
	setLights(c.l);
	setBangLED(c.l);
}


void setup() {
	// set the LED_BANG_PIN as an output:
	pinMode(LED_BANG_PIN, OUTPUT);
	pinMode(LED_R_PIN, OUTPUT);
	pinMode(LED_G_PIN, OUTPUT);
	pinMode(LED_B_PIN, OUTPUT);
	pinMode(LED_LIGHTS_PIN, OUTPUT);

	pinMode(ROTARY_ENCODER_M_SWT_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_L_SWT_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_R_SWT_PIN, INPUT_PULLUP);

	/*
	pinMode(ROTARY_ENCODER_LA_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_LB_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_RA_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_RB_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_MA_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_MB_PIN, INPUT_PULLUP);

	pinMode(ROTARY_ENCODER_LP_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_RP_PIN, INPUT_PULLUP);
	pinMode(ROTARY_ENCODER_MP_PIN, INPUT_PULLUP);
	*/


	// set the LED_BANG_PIN to the initial brightness:
	Color color = Color(240, 1.0, 0.25);
	setRGB(color.getRGB());
	delay(5000);
	timer = millis();
	setLights(brightness);
	setBangLED(brightness / 2);
	if (DEBUG) {
		Serial.begin(115200);
		Serial.println("Bang Button Box - Assetto Corsa Competizione!");
	}
	buttons.setDebounceTime(50);
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

void checkEncoders() {
	// Serial.println("rotaryEncoderChanged");
}

void loop() {
	timer = millis();

	if (!controllerReady && (timer - controllerChangeTimer > controllerChangeDelay)) {
		controllerReady = true;
		controllerChangeTimer = 0;
		if (DEBUG) {
			Serial.print("Controller Ready: ");
			Serial.println(controller.name);
		}
	}
	if (feedbackTimer && timer - feedbackTimer > feedbackInterval) {
		feedbackTimer = timer;
		if (feedbackBlink) {
			setBangLED(0);
			Serial.println("feedback off");
		}
		else {
			setBangLED(brightness);
			Serial.println("feedback on");
		}
		feedbackCount++;
		feedbackBlink = !feedbackBlink;
		if (feedbackCount > feedbackLimit) {
			feedbackBlink = false;
			feedbackTimer = 0;
			feedbackCount = 0;
		}
	}

	if (pulseTimer && timer - pulseTimer > pulseInterval) {
		pulseTimer = timer;
		
		if (pulseBlink) {
			setBangLED(0);
			setLights(0);
			pulseBlink = false;
		}
		else {
			setBangLED(brightness);
			setLights(brightness);
			pulseBlink = true;
		}
	}
	if (bangedTimer && timer - bangedTimer > bangedInterval) {
		bangedTimer = timer;
		if (bangedBlink) {
			// toogle between default and banged controller color
			setRGB(controller.colorBanged->getRGB());
		}
		else {
			setRGB(controller.color->getRGB());
		}
		bangedBlink = !bangedBlink;
	}
	if (enhancedEncoderTimer && timer - enhancedEncoderTimer > enhancedEncoderDuration) {
		enhancedEncoderTimer = 0;
		pulseBlink = false;
		pulseTimer = 0;
		setBangLED(brightness);
		setLights(brightness);
		controller.game->deEnhance();
	}

	if (!bangToggleMode) {
		if (timer - bangedTimer > bangedDuration) {
			modeDefault();
		}
	}
	if (prepareChangeProfileTimer && timer - prepareChangeProfileTimer > prepareChangeProfileDuration) {
		modeActivateChangeProfile();
	}
	if (activateChangeProfileTimer && timer - activateChangeProfileTimer > activateChangeProfileInterval) {
		activateChangeProfileTimer = timer;
		
		if (activateChangeProfileBlink) {
			setRGB(controller.colorBanged->getRGB());
		}
		else {
			setRGB(controller.color->getRGB());
		}
		if (timer - activateChangeProfileTimer > activateChangeProfileDuration) {
			modeDefault();
		}
		activateChangeProfileBlink = !activateChangeProfileBlink;
	}

	for (unsigned char i = 0; i < NUM_ENCODERS; i++) {
		encoders[i].tick();
		int newPosition = encoders[i].getPosition();
		if (newPosition != encoderValue[i]) {
			/*
			Serial.print("Encoder: ");
			Serial.print(i);
			Serial.print(" | Position: ");
			Serial.print(newPosition);
			Serial.println(" |");
			*/
			encoderValue[i] = newPosition;
			encoderChanged = true;
			char direction = (char) encoders[i].getDirection();
			sendRotaryEncoder(i, direction);
		}
	}
	// check encoder push buttons
	for (unsigned char i = 0; i < NUM_ENCODERS; i++) {
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

	switch (sleeping) {
		case 1: // unit is in hyper sleep...
			delay(50);
			if (timer - sleepTimer > HYPER_SLEEP_TIME) {
				hyperSleep();
			}
		break;
		case 2: // unit is in hyper sleep...
			// 1 loop per secondv
			delay(100);
		break;
		default:
			// delay half of a nano second
			delayMicroseconds(100);
			if (timer - sleepTimer > SLEEP_TIME) {
				sleep();
			}
		break;
	}

	loopCount++;
	if (timer - debugTimer > 10000) {
		Serial.print("Loop: ");
		Serial.print(loopCount);
		Serial.print(" | Controller: ");
		Serial.print(controller.name);
		Serial.println(" |");
		loopCount = 0;
		debugTimer = timer;
	}
	// delay(200);
}
