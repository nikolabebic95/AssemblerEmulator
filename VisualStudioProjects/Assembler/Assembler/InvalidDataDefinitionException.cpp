#include "InvalidDataDefinitionException.h"

namespace bnssassembler {

	InvalidDataDefinitionException::InvalidDataDefinitionException(std::string data) noexcept : MessageException(data + " can not be parsed as data") {}
}