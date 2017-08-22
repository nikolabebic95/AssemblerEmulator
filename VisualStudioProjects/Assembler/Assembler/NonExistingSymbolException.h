#ifndef _non_existing_symbol_exception_h_
#define _non_existing_symbol_exception_h_
#include <string>
#include "MessageException.h"

namespace bnssassembler {
	
	/**
	 * \brief Exception representing the non existing symbol
	 */
	class NonExistingSymbolException : public MessageException {
	public:
		/**
		 * \brief Constructs a NonExistingSymbolException object
		 * \param symbol Non existing symbol
		 */
		explicit NonExistingSymbolException(std::string symbol) noexcept;
	};
}

#endif
