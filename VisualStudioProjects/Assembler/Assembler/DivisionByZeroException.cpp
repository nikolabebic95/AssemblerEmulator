#include "DivisionByZeroException.h"

namespace bnss {

	DivisionByZeroException::DivisionByZeroException() noexcept : MessageException("Error: Division by zero") {}
}
