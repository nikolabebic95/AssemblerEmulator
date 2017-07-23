#ifndef _invalid_data_type_exception_h_
#define _invalid_data_type_exception_h_
#include "MessageException.h"

namespace bnss {
	
	class InvalidDataTypeException : MessageException {
	public:
		explicit InvalidDataTypeException(std::string data_type) noexcept;
	};
}

#endif
