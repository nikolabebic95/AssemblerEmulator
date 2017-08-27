#include "MessageException.h"

namespace bnssemulator {

	MessageException::MessageException(std::string message) noexcept : message_(message) {}

	std::string MessageException::message() const noexcept {
		return message_;
	}

	const char * MessageException::what() const noexcept {
		return message_.c_str();
	}
}
