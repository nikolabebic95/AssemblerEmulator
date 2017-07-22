#ifndef _parser_exception_h_
#define _parser_exception_h_
#include "AssemblerException.h"

namespace bnss {
	
	/**
	 * \brief Represents an exception that happend during the parsing of the file
	 */
	class ParserException : public AssemblerException {
	public:
		ParserException(size_t line_number, std::string line, std::string specific_message) noexcept;
		std::string messageBody() const noexcept override;
	private:
		std::string specific_message_;
	};
}

#endif
