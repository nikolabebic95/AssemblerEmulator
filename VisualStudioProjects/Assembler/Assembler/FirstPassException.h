#ifndef _first_pass_exception_h_
#define _first_pass_exception_h_
#include "AssemblerException.h"

namespace bnssassembler {
	
	/**
	 * \brief Represents an exception that happend during the assembler first pass
	 */
	class FirstPassException : public AssemblerException {
	public:
		/**
		* \brief Constructs a FirstPassException object
		* \param line_number Number of the line where the error happened
		* \param line Line where the error happened
		* \param specific_message Specific message about the error that happened
		*/
		FirstPassException(size_t line_number, std::string line, std::string specific_message) noexcept;
	protected:
		std::string messageBody() const noexcept override;
	private:
		std::string specific_message_;
	};
}

#endif
