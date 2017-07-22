#include "IncorrectLabelException.h"

namespace bnss {

	IncorrectLabelException::IncorrectLabelException(std::string label) noexcept : MessageException("The label \"" + label + "\" is in incorrect format") {}
}
