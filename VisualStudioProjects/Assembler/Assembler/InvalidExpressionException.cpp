#include "InvalidExpressionException.h"

namespace bnssassembler {

	InvalidExpressionException::InvalidExpressionException() noexcept : MessageException("The expression is invalid") {}
}
