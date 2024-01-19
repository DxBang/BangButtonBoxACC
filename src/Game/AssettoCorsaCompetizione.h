#ifndef BANG_h
	#include "Bang.h"
#endif



class AssettoCorsaCompetizione : public Game {

	public:
		AssettoCorsaCompetizione() {
			isKeyboard = true;
		}
		void button(unsigned char button, bool pressed) override {
			Serial.print("AssettoCorsaCompetizione: ");
			Serial.print(button);
			Serial.print(" ");
			Serial.println(pressed);
			
			switch (button) {
				case B_ENGINE:
					this->startEngine(pressed);
				break;
				case BANGED + B_ENGINE:
					this->bangedStartEngine(pressed);
				break;
				case B_IGNITION:
					this->ignition(pressed);
				break;
				case B_PIT_LIMITER:
					this->pitLimiter(pressed);
				break;
				case B_LIGHT:
					this->cycleLights(pressed);
				break;
				case BANGED + B_LIGHT:
					this->volumeUp(pressed, 5);
				break;
				case B_FLASH:
					this->flash(pressed);
				break;
				case BANGED + B_FLASH:
					this->volumeDown(pressed, 5);
				break;
				case B_RAINLIGHT:
					this->rainLights(pressed);
				break;
				case BANGED + B_RAINLIGHT:
					this->cycleMap(pressed);
				break;
				case B_WIPER:
					this->cycleWiper(pressed);
				break;
				case BANGED + B_WIPER:
					this->cycleHUD(pressed);
				break;
				case B_NAV_UP:
					this->navigationUp(pressed);
				break;
				case B_NAV_DOWN:
					this->navigationDown(pressed);
				break;
				case B_NAV_LEFT:
					this->navigationLeft(pressed);
				break;
				case B_NAV_RIGHT:
					this->navigationRight(pressed);
				break;
				case B_NAV_SELECT:
					this->select(pressed);
				break;



				
				case B_ENCODER_M_PH:
				case B_ENCODER_L_PH:
				case B_ENCODER_R_PH:
				case BANGED + B_ENCODER_M_PH:
				case BANGED + B_ENCODER_L_PH:
				case BANGED + B_ENCODER_R_PH:
					if (pressed) {
						this->enhance();
					}
				break;

				case R_ENCODER_M_UP:
					if (this->enhanced) {
						this->engineMapUp(pressed, 3);
					}
					else {
						this->engineMapUp(pressed, 1);
					}
				break;
				case R_ENCODER_M_DN:
					if (this->enhanced) {
						this->engineMapDown(pressed, 3);
					}
					else {
						this->engineMapDown(pressed, 1);
					}
				break;
				case R_ENCODER_L_UP:
					if (this->enhanced) {
						this->brakeBiasUp(pressed, 10);
					}
					else {
						this->brakeBiasUp(pressed, 5);
					}
					
				break;
				case R_ENCODER_L_DN:
					if (this->enhanced) {
						this->brakeBiasDown(pressed, 10);
					}
					else {
						this->brakeBiasDown(pressed, 5);
					}
				break;
				case R_ENCODER_R_UP:
					if (this->enhanced) {
						this->tractionControlUp(pressed, 3);
					}
					else {
						this->tractionControlUp(pressed, 1);
					}
				break;
				case R_ENCODER_R_DN:
					if (this->enhanced) {
						this->tractionControlDown(pressed, 3);
					}
					else {
						this->tractionControlDown(pressed, 1);
					}
				break;
				case BANGED + R_ENCODER_L_UP:
					if (this->enhanced) {
						this->antilockBrakingSystemUp(pressed, 3);
					}
					else {
						this->antilockBrakingSystemUp(pressed, 1);
					}
				break;
				case BANGED + R_ENCODER_L_DN:
					if (this->enhanced) {
						this->antilockBrakingSystemDown(pressed, 3);
					}
					else {
						this->antilockBrakingSystemDown(pressed, 1);
					}
				break;
				case BANGED + R_ENCODER_R_UP:
					if (this->enhanced) {
						this->tractionControlCutUp(pressed, 3);
					}
					else {
						this->tractionControlCutUp(pressed, 1);
					}
				break;
				case BANGED + R_ENCODER_R_DN:
					if (this->enhanced) {
						this->tractionControlCutDown(pressed, 3);
					}
					else {
						this->tractionControlCutDown(pressed, 1);
					}
				break;
				case BANGED + R_ENCODER_M_UP:
					this->volumeUp(pressed, 5);
				break;
				case BANGED + R_ENCODER_M_DN:
					this->volumeDown(pressed, 5);
				break;



				case B_MFD_PITSTOP:
					this->mfdPitstop(pressed);
				break;
				case BANGED + B_MFD_PITSTOP:
					this->raceLogic(pressed);
				break;
				case B_MFD_STANDINGS:
					this->mfdStandings(pressed);
				break;
				case BANGED + B_MFD_STANDINGS:
					this->dashboardUp(pressed);
				break;
				case B_MFD_POSITIONS:
					this->mfdPositions(pressed);
				break;
				case BANGED + B_MFD_POSITIONS:
					this->dashboardDown(pressed);
				break;
				case B_MFD_ELECTRONICS:
					this->mfdElectronics(pressed);
				break;
				case BANGED + B_MFD_ELECTRONICS:
					this->cycleMFD(pressed);
				break;
				default:
					Serial.print("Unknown button: ");
					Serial.println(button);
				break;
			}
		}

	private:
		void startEngine(bool pressed) {
			// S
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("startEngine");
				}
				*/
				return this->keyHold(KEY_S);
			}
			this->keyRelease(KEY_S);
		}
		void bangedStartEngine(bool pressed) {
			// S for 1.1 seconds
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("bangedStartEngine");
				}
				*/
				this->keyHold(KEY_S, 1000);
			}
		}
		void ignition(bool pressed) {
			// SHIFT + I
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("ignition");
				}
				*/
				this->keyHold(KEY_LEFT_SHIFT);
				this->keyTap(KEY_I);
				this->keyRelease(KEY_LEFT_SHIFT);
			}
		}
		void pitLimiter(bool pressed) {
			// ALT + L
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("pitLimiter");
				}
				*/
				this->keyHold(KEY_LEFT_ALT);
				this->keyTap(KEY_L);
				this->keyRelease(KEY_LEFT_ALT);
			}
		}
		void cycleLights(bool pressed) {
			// L
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("cycleLights");
				}
				*/
				this->keyTap(KEY_L);
			}
		}
		void flash(bool pressed) {
			// SHIFT + L
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("flash");
				}
				*/
				this->keyHold(KEY_LEFT_SHIFT);
				this->keyTap(KEY_L);
				this->keyRelease(KEY_LEFT_SHIFT);
			}
		}
		void rainLights(bool pressed) {
			// CTRL + L
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("rainLights");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_L);
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void indicatorLeft(bool pressed) {
			// ALT + Left Arrow
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("indicatorLeft");
				}
				*/
				this->keyHold(KEY_LEFT_ALT);
				this->keyTap(KEY_LEFT_ARROW);
				this->keyRelease(KEY_LEFT_ALT);
			}
		}
		void indicatorRight(bool pressed) {
			// ALT + Right Arrow
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("B_INDICATOR_RIGHT");
				}
				*/
				this->keyHold(KEY_LEFT_ALT);
				this->keyTap(KEY_RIGHT_ARROW);
				this->keyRelease(KEY_LEFT_ALT);
			}
		}
		void cycleWiper(bool pressed) {
			// ALT + W
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("cycleWiper");
				}
				*/
				this->keyHold(KEY_LEFT_ALT);
				this->keyTap(KEY_W);
				this->keyRelease(KEY_LEFT_ALT);
			}
		}
		void names(bool pressed) {
			// V
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("names");
				}
				*/
				this->keyTap(KEY_V);
			}
		}
		void cycleMFD(bool pressed) {
			// INSERT
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("cycleMFD");
				}
				*/
				this->keyTap(KEY_INSERT);
			}
		}
		void cycleHUD(bool pressed) {
			// F2
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("cycleHUD");
				}
				*/
				this->keyTap(KEY_F2);
			}
		}
		void cycleMap(bool pressed) {
			// SHIFT + M
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("cycleMap");
				}
				*/
				this->keyHold(KEY_LEFT_SHIFT);
				this->keyTap(KEY_M);
				this->keyRelease(KEY_LEFT_SHIFT);	
			}
		}
		void navigationUp(bool pressed) {
			// Up Arrow
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("navigationUp");
				}
				*/
				this->keyTap(KEY_UP_ARROW);
			}
		}
		void navigationDown(bool pressed) {
			// Down Arrow
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("navigationDown");
				}
				*/
				this->keyTap(KEY_DOWN_ARROW);
			}
		}
		void navigationLeft(bool pressed) {
			// Left Arrow
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("navigationLeft");
				}
				*/
				this->keyTap(KEY_LEFT_ARROW);
			}
		}
		void navigationRight(bool pressed) {
			// Right Arrow
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("navigationRight");
				}
				*/
				this->keyTap(KEY_RIGHT_ARROW);
			}
		}
		void select(bool pressed) {
			// Return
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("select");
				}
				*/
				this->keyTap(KEY_RETURN);
			}
		}
		void raceLogic(bool pressed) {
			// ALT + D
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("raceLogic");
				}
				*/
				this->keyHold(KEY_LEFT_ALT);
				this->keyTap(KEY_D);
				this->keyRelease(KEY_LEFT_ALT);
			}
		}
		void dashboardUp(bool pressed) {
			// SHIFT + D
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("dashboardUp");
				}
				*/
				this->keyHold(KEY_LEFT_SHIFT);
				this->keyTap(KEY_D);
				this->keyRelease(KEY_LEFT_SHIFT);
			}
		}
		void dashboardDown(bool pressed) {
			// CTRL + D
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("dashboardDown");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_D);
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void timeTable(bool pressed) {
			// TAB
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("timeTable");
				}
				*/
				this->keyHold(KEY_TAB);
			}
			else {
				this->keyRelease(KEY_TAB);
			}
		}
		void mfdElectronics(bool pressed) {
			// O
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("mfdElectronics");
				}
				*/
				this->keyTap(KEY_O);
			}
		}
		void mfdPitstop(bool pressed) {
			// P
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("mfdPitstop");
				}
				*/
				this->keyTap(KEY_P);
			}
		}
		void mfdStandings(bool pressed) {
			// I
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("mfdStandings");
				}
				*/
				this->keyTap(KEY_I);
			}
		}
		void mfdPositions(bool pressed) {
			// U
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("mfdPositions");
				}
				*/
				this->keyTap(KEY_U);
			}
		}
		void saveReplay(bool pressed) {
			// M
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("saveReplay");
				}
				*/
				this->keyTap(KEY_M);
			}
		}
		void addHighlight(bool pressed) {
			// ALT + M
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("addHighlight");
				}
				*/
				this->keyHold(KEY_LEFT_ALT);
				this->keyTap(KEY_M);
				this->keyRelease(KEY_LEFT_ALT);
			}
		}
		void saveHighlights(bool pressed) {
			// CTRL + M
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("saveHighlights");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_M);
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void cockpit(bool pressed) {
			// 1
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("cockpit");
				}
				*/
				this->keyTap(KEY_1);
			}
		}
		void bonnet(bool pressed) {
			// 2
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("bonnet");
				}
				*/
				this->keyTap(KEY_2);
			}
		}
		void chase(bool pressed) {
			// 3
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("chase");
				}
				*/
				this->keyTap(KEY_3);
			}
		}
		void cycleCamera(bool pressed) {
			// F1
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("cycleCamera");
				}
				*/
				this->keyTap(KEY_F1);
			}
		}
		void cycleDriverWheel(bool pressed) {
			// CTRL + I
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("cycleDriverWheel");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_I);
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void engineMapUp(bool pressed, char times = 1) {
			// SHIFT + E
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("engineMapUp");
				}
				*/
				this->keyHold(KEY_LEFT_SHIFT);
				this->keyTap(KEY_E, times);
				this->keyRelease(KEY_LEFT_SHIFT);
			}
		}
		void engineMapDown(bool pressed, char times = 1) {
			// CTRL + E
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("engineMapDown");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_E, times);
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void brakeBiasUp(bool pressed, char times = 1) {
			// SHIFT + B
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("brakeBiasUp: SHIFT + B");
				}
				*/
				this->keyHold(KEY_LEFT_SHIFT);
				this->keyTap(KEY_B, times);// 10
				this->keyRelease(KEY_LEFT_SHIFT);
			}
		}
		void brakeBiasDown(bool pressed, char times = 1) {
			// CTRL + B
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("brakeBiasDown: CTRL + B");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_B, times); // 10
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void antilockBrakingSystemUp(bool pressed, char times = 1) {
			// SHIFT + A
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("antilockBrakingSystemUp: SHIFT + A");
				}
				*/
				this->keyHold(KEY_LEFT_SHIFT);
				this->keyTap(KEY_A, times); // 2
				this->keyRelease(KEY_LEFT_SHIFT);
			}
		}
		void antilockBrakingSystemDown(bool pressed, char times = 1) {
			// CTRL + A
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("antilockBrakingSystemDown: CTRL + A");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_A, times); // 2
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void tractionControlUp(bool pressed, char times = 1) {
			// SHIFT + T
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("tractionControlUp: SHIFT + T");
				}
				*/
				this->keyHold(KEY_LEFT_SHIFT);
				this->keyTap(KEY_T, times); // 2
				this->keyRelease(KEY_LEFT_SHIFT);
			}
		}
		void tractionControlDown(bool pressed, char times = 1) {
			// CTRL + T
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("tractionControlDown: CTRL + T");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_T, times); // 2
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void tractionControlCutUp(bool pressed, char times = 1) {
			// SHIFT + Y
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("tractionControlCutUp: SHIFT + Y");
				}
				*/
				this->keyHold(KEY_LEFT_SHIFT);
				this->keyTap(KEY_Y, times); // 2
				this->keyRelease(KEY_LEFT_SHIFT);
			}
		}
		void tractionControlCutDown(bool pressed, char times = 1) {
			// CTRL + Y
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("tractionControlCutDown: CTRL + Y");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_Y, times); // 2
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void specialUp(bool pressed, char times = 1) {
			// CTRL + Right Arrow
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("specialUp: CTRL + Right Arrow");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_RIGHT_ARROW, times); // 5
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void specialDown(bool pressed, char times = 1) {
			// CTRL + Left Arrow
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("specialDown: CTRL + Left Arrow");
				}
				*/
				this->keyHold(KEY_LEFT_CTRL);
				this->keyTap(KEY_LEFT_ARROW, times); // 5
				this->keyRelease(KEY_LEFT_CTRL);
			}
		}
		void volumeUp(bool pressed, char times = 1) {
			// NUM PLUS
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("volumeUp: NUM PLUS");
				}
				*/
				this->keyTap(KEYPAD_ADD, times); // 10
			}
		}
		void volumeDown(bool pressed, char times = 1) {
			// NUM MINUS
			if (pressed) {
				/*
				if (DEBUG) {
					Serial.println("volumeDown: NUM MINUS");
				}
				*/
				this->keyTap(KEYPAD_SUBTRACT, times); // 10
			}
		}
};