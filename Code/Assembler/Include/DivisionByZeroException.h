#ifndef _division_by_zero_exception_h_
#define _division_by_zero_exception_h_
#include "MessageException.h"

namespace bnssassembler {
	
	/**
	 * \brief Exception class representing division by zero
	 */
	class DivisionByZeroException : public MessageException {
	public:
		/**
		 * \brief Constructs a DivisionByZeroException object
		 */
		DivisionByZeroException() noexcept;
	};
}

#endif
