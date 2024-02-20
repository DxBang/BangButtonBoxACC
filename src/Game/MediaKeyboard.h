#ifndef BANG_h
	#include "Bang.h"
#endif

#ifndef HID_PROJECT_VERSION
	#include <HID-Project.h>
#endif

class MediaKeyboard : public Game {
	public:
		MediaKeyboard() {
			this->isKeyboard = true;
			this->isConsumer = true;
		};
		void input(unsigned char input, bool pressed) override {
			switch (input) {
				case R_ENCODER_M_UP:
					if (pressed) {
						this->keyPress(KEY_RIGHT_CTRL);
						if (this->heldEncoder) {
							this->keyTap(KEY_RIGHT_ARROW, 5);
						} else {
							this->keyTap(KEY_RIGHT_ARROW, 1);
						}
						this->keyRelease(KEY_RIGHT_CTRL);
					}
				break;
				case R_ENCODER_M_DN:
					if (pressed) {
						this->keyPress(KEY_RIGHT_CTRL);
						if (this->heldEncoder) {
							this->keyTap(KEY_LEFT_ARROW, 5);
						} else {
							this->keyTap(KEY_LEFT_ARROW, 1);
						}
						this->keyRelease(KEY_RIGHT_CTRL);
					}
				break;
				case B_ENCODER_M_PH:
					if (pressed) {
						this->enhance();
					}
				break;
				// 0xC0
				case R_ENCODER_R_UP:
					if (pressed) {
						if (this->heldEncoder) {
							this->consumerTap(HID_CONSUMER_FRAME_FORWARD, 5);
						} else {
							this->consumerTap(HID_CONSUMER_FRAME_FORWARD, 1);
						}
					}
				break;
				case R_ENCODER_R_DN:
					if (pressed) {
						if (this->heldEncoder) {
							this->consumerTap(HID_CONSUMER_FRAME_BACK, 5);
						} else {
							this->consumerTap(HID_CONSUMER_FRAME_BACK, 1);
						}
					}
				break;
				case B_ENCODER_R_PH:
					if (pressed) {
						this->consumerPress(HID_CONSUMER_MARK);
					}
				break;
				case R_ENCODER_L_UP:
					if (pressed) {
						if (this->heldEncoder) {
							this->consumerTap(MEDIA_VOLUME_UP, 5);
						} else {
							this->consumerTap(MEDIA_VOLUME_UP, 1);
						}
					}
				break;
				case R_ENCODER_L_DN:
					if (pressed) {
						if (this->heldEncoder) {
							this->consumerTap(MEDIA_VOLUME_DOWN, 5);
						} else {
							this->consumerTap(MEDIA_VOLUME_DOWN, 1);
						}
					}
				break;
				case B_ENCODER_L_PH:
					if (pressed) {
						this->consumerPress(MEDIA_VOLUME_MUTE);
					}
				break;
				case B_NAV_UP:
					if (pressed) {
						this->consumerPress(MEDIA_PLAY_PAUSE);
					}
				break;
				case B_NAV_LEFT:
					if (pressed) {
						this->consumerPress(MEDIA_PREVIOUS);
					}
				break;
				case B_NAV_RIGHT:
					if (pressed) {
						this->consumerPress(MEDIA_NEXT);
					}
				break;
				case B_NAV_DOWN:
					if (pressed) {
						this->consumerPress(MEDIA_STOP);
					}
				break;
				case B_NAV_SELECT:
					if (pressed) {
						this->consumerPress(MEDIA_REWIND);
					}
				break;
				case B_MFD_ELECTRONICS:
					if (pressed) {
						this->consumerPress(MEDIA_FAST_FORWARD);
					}
				break;




			}
		};

};
