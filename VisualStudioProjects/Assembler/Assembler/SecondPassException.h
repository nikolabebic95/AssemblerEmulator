#ifndef _second_pass_exception_h_
#define _second_pass_exception_h_
#include "AssemblerException.h"

namespace bnssassembler {
	
	/**
	 * \brief Represents an exception that happened during the assembler second pass
	 */
	class SecondPassException : public AssemblerException {
	public:
		/**
		* \brief Constructs a SecondPassException object
		* \param line_number Number of the line where the error happened
		* \param line Line where the error happened
		* \param specific_message Specific message about the error that happened
		*/
		SecondPassException(size_t line_number, std::string line, std::string specific_message) noexcept;
	protected:
		std::string messageBody() const noexcept override;
	private:
		std::string specific_message_;
	};
}

#endif
