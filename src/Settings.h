
unsigned char controllerIndex = 0;

bool encoderChanged = false;


unsigned long timer = 0;
unsigned long debugTimer = 0;
unsigned long loopCount = 0;
unsigned char feedbackCount = 0;


bool bangTimedMode = false; // true = timed, false = toggle
const unsigned short controllerReadyDelay = 1000;

// const unsigned char feedbackLimit = 10;

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

unsigned long bangedModeTimer = 0;

unsigned long enhancedEncoderTimer = 0;
const unsigned short enhancedEncoderDuration = 5000;

unsigned long prepareSystemTimer = 0;
const unsigned short prepareSystemDuration = 2000;

unsigned long activateSystemTimer = 0;
const unsigned short activateSystemInterval = 1000;
const unsigned short activateSystemDuration = 10000;

unsigned long activateSystemModeTimer = 0;


unsigned long controllerReadyTimer = 0;

unsigned char brightness = 100; // for LED_LIGHTS_PIN, LED_BANG_PIN
unsigned char brightnessMinValue = 0; // for LED_LIGHTS_PIN, LED_BANG_PIN, LED_R_PIN, LED_G_PIN, LED_B_PIN
unsigned char brightnessMaxValue = 127;	// for LED_LIGHTS_PIN, LED_BANG_PIN. LED_R_PIN, LED_G_PIN, LED_B_PIN
unsigned char brightnessStep = 1; // for LED_LIGHTS_PIN, LED_BANG_PIN, LED_R_PIN, LED_G_PIN, LED_B_PIN

unsigned char sleeping = 0;
unsigned long sleepTimer = 0;
