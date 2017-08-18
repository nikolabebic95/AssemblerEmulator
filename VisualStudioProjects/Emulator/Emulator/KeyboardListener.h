#ifndef _keyboard_listener_h_
#define _keyboard_listener_h_
#include "Context.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the keyboard listener thread
	 */
	class KeyboardListener final {
	public:
		/**
		 * \brief Listens to keyboard interrupts and sets the context flag every time they fire
		 */
		static void listen(Context &context);
	};
}

#endif
