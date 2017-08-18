#include "TimerListener.h"
#include <chrono>
#include <thread>

namespace bnssemulator {

	void TimerListener::listen(Context * context) {
		using namespace std::literals::chrono_literals;

		while (!context->programFinished()) {
			std::this_thread::sleep_for(100ms);
			context->timerTriggered(true);
		}
	}
}
