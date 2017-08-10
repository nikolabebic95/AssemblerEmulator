#include "DivisionByZeroException.h"

namespace bnssassembler {

	DivisionByZeroException::DivisionByZeroException() noexcept : MessageException("Error: Division by zero") {}
}
