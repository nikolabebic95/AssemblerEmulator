#ifndef _invalid_expression_exception_h_
#define _invalid_expression_exception_h_
#include "MessageException.h"

namespace bnss {

	/**
	 * \brief Exception representing the invalid expression
	 */
	class InvalidExpressionException : MessageException {
	public:
		InvalidExpressionException() noexcept;
	};
}

#endif
