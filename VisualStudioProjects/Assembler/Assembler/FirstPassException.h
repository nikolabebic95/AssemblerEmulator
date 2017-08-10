#ifndef _first_pass_exception_h_
#define _first_pass_exception_h_
#include "AssemblerException.h"

namespace bnssassembler {
	
	class FirstPassException : public AssemblerException {
	public:
		FirstPassException(size_t line_number, std::string line, std::string specific_message) noexcept;
	protected:
		std::string messageBody() const noexcept override;
	private:
		std::string specific_message_;
	};
}

#endif
