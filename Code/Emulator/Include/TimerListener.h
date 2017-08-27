#ifndef _timer_listener_h_
#define _timer_listener_h_
#include "Context.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing a listener for the timer events
	 */
	class TimerListener {
	public:
		/**
		 * \brief Listens to timer interrupts and sets the context flag every time it should
		 */
		static void listen(Context *context);
	};
}

#endif
