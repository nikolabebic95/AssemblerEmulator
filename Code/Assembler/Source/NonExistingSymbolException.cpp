#include "NonExistingSymbolException.h"

namespace bnssassembler {

	NonExistingSymbolException::NonExistingSymbolException(std::string symbol) noexcept : MessageException("The symbol \"" + symbol + "\" is not defined") {}
}
