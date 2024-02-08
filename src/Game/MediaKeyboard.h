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
		};
		void input(unsigned char input, bool pressed) override {
			switch (input) {
				

			}
		};

};
