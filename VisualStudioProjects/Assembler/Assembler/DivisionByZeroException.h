#ifndef _division_by_zero_exception_h_
#define _division_by_zero_exception_h_
#include "MessageException.h"

namespace bnss {
	
	/**
	 * \brief Exception class representing division by zero
	 */
	class DivisionByZeroException : public MessageException {
	public:
		DivisionByZeroException() noexcept;
	};
}

#endif
