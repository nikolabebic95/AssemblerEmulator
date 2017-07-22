#include "InvalidExpressionException.h"

namespace bnss {

	InvalidExpressionException::InvalidExpressionException() noexcept : MessageException("The expression is invalid") {}
}
