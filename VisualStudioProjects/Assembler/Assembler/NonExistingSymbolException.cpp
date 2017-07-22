#include "NonExistingSymbolException.h"

namespace bnss {

	NonExistingSymbolException::NonExistingSymbolException(std::string symbol) noexcept : MessageException("The symbol \"" + symbol + "\" is not defined") {}
}
