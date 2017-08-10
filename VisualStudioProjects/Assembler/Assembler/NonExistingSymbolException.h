#ifndef _non_existing_symbol_exception_h_
#define _non_existing_symbol_exception_h_
#include <string>
#include "MessageException.h"

namespace bnssassembler {
	
	class NonExistingSymbolException : public MessageException {
	public:
		explicit NonExistingSymbolException(std::string symbol) noexcept;
	};
}

#endif
