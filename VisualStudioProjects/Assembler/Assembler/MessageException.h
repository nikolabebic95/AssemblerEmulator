#ifndef _message_exception_h_
#define _message_exception_h_
#include <string>

namespace bnss {
	
	/**
	 * \brief Represents an exception with a string message
	 */
	class MessageException : public std::exception {
	public:
		/**
		 * \brief Constructs a MessageException object with the message
		 * \param message Message
		 */
		explicit MessageException(std::string message) noexcept;

		/**
		 * \brief Gets the message of the exception
		 */
		std::string message() const noexcept;
		const char *what() const noexcept override;
	private:
		std::string message_;
	};
}

#endif
