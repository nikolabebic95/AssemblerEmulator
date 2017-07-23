#include "InvalidDataDefinitionException.h"

namespace bnss {

	InvalidDataDefinitionException::InvalidDataDefinitionException(std::string data) noexcept : MessageException(data + " can not be parsed as data") {}
}