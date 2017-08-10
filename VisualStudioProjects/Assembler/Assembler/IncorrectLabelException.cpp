#include "IncorrectLabelException.h"

namespace bnssassembler {

	IncorrectLabelException::IncorrectLabelException(std::string label) noexcept : MessageException("The label \"" + label + "\" is in incorrect format") {}
}
