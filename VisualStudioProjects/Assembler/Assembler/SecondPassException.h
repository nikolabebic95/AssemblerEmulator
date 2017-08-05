#ifndef _second_pass_exception_h_
#define _second_pass_exception_h_
#include "AssemblerException.h"

namespace bnss {
	
	class SecondPassException : public AssemblerException {
	public:
		SecondPassException(size_t line_number, std::string line, std::string specific_message) noexcept;
	protected:
		std::string messageBody() const noexcept override;
	private:
		std::string specific_message_;
	};
}

#endif
