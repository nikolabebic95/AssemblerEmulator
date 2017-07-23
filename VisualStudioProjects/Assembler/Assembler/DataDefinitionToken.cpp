#include "DataDefinitionToken.h"

namespace bnss {

	DataDefinitionToken::DataDefinitionToken(std::vector<Data> data, size_t line_number, std::string line) noexcept : Token(line_number, line), data_(data) {}
}
