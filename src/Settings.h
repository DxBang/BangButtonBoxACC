#ifndef SETTINGS_h
	#define SETTINGS_h
#endif

#ifndef DEBUG
	#define DEBUG 0
#endif

#if DEBUG == 1
	#define debug(x) Serial.print(x)
	#define debugln(x) Serial.println(x)
#else
	#define debug(x)
	#define debugln(x)
#endif

unsigned char controllerIndex = 0;

bool encoderChanged = false;


unsigned long timer = 0;
#if DEBUG
	unsigned long debugTimer = 0;
	unsigned long loopCount = 0;
#endif
unsigned char feedbackCount = 0;


bool bangTimedMode = false; // true = timed, false = toggle

bool feedbackBlink = false;
bool pulseBlink = false;
bool bangedBlink = false;
bool activateSystemBlink = false;

unsigned long bangBlinkTimer = 0;
unsigned long engineBlinkTimer = 0;
unsigned long lightBlinkTimer = 0;

unsigned long feedbackTimer = 0;
const unsigned char feedbackInterval = 50;
const unsigned short feedbackDuration = 500;

const unsigned short pulseInterval = 500;

unsigned long bangedTimer = 0;
unsigned long bangedBlinkTimer = 0;
const unsigned short bangedInterval = 500;
const unsigned short bangedDuration = 5000;

unsigned long enhancedEncoderTimer = 0;
const unsigned short enhancedEncoderDuration = 5000;
const unsigned char enhancedEncoderMultiplier = 5;

unsigned long prepareSystemTimer = 0;
const unsigned short prepareSystemDuration = 2000;

unsigned long activateSystemTimer = 0;
const unsigned short activateSystemInterval = 500;
// 
short activateSystemDuration = 20000;

unsigned long controllerReadyTimer = 0;
const unsigned short controllerReadyDelay = 1000;

unsigned char brightness = 60; // for LED_LIGHTS_PIN, LED_BANG_PIN
unsigned char brightnessMinValue = 0; // for LED_LIGHTS_PIN, LED_BANG_PIN, LED_R_PIN, LED_G_PIN, LED_B_PIN
unsigned char brightnessMaxValue = 120;	// for LED_LIGHTS_PIN, LED_BANG_PIN. LED_R_PIN, LED_G_PIN, LED_B_PIN
unsigned char brightnessStep = 1; // for LED_LIGHTS_PIN, LED_BANG_PIN, LED_R_PIN, LED_G_PIN, LED_B_PIN

unsigned char sleeping = 0;
unsigned long sleepTimer = 0;

unsigned long sleepDelay = 900000; // 10 mins / 900000 ( 5000 debug )
unsigned long hybridSleepDelay = 1800000; // 30 mins / 1800000 ( 20000 debug )
