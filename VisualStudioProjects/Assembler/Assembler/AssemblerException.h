#ifndef _assembler_exception_h_
#define _assembler_exception_h_

#include <string>

namespace bnssassembler {
	
	/**
	 * \brief Class representing the custom exception for the assembler
	 */
	class AssemblerException : public std::exception {
	public:
		/**
		 * \brief Constructs an AssemblerException object
		 * \param line_number Number of the line in the source file which triggered the exception
		 * \param line Line of the source file which triggered the exception
		 */
		explicit AssemblerException(size_t line_number, std::string line) noexcept;

		/**
		 * \brief Gets the message. Note that this should be used instead of what()
		 * \return The message of the exception
		 */
		std::string message() const noexcept;
		const char *what() const noexcept override;
	protected:
		virtual std::string messageBody() const noexcept = 0;
	private:
		size_t line_number_;
		std::string line_;
	};
}

#endif
