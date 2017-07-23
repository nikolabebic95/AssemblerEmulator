#include "InvalidDataTypeException.h"

namespace bnss {

	InvalidDataTypeException::InvalidDataTypeException(std::string data_type) noexcept : MessageException(data_type + " is not a valid data type") {}
}
