#include "KeyboardListener.h"
#include "ConsoleInputOutput.h"

namespace bnssemulator {

	void KeyboardListener::listen(Context * context) {
		while (!context->programFinished()) {
			while (!consoleio::keyboardHit()) {
				if (context->programFinished()) {
					return;
				}
			}

			auto character = consoleio::getCharacter();
			context->pressCharacter(character);
		}
	}
}
