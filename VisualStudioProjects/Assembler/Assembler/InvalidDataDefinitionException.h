#ifndef _invalid_data_definition_exception_h_
#define _invalid_data_definition_exception_h_
#include "MessageException.h"

namespace bnssassembler {
	
	class InvalidDataDefinitionException : public MessageException {
	public:
		explicit InvalidDataDefinitionException(std::string data) noexcept;
	};
}

#endif
