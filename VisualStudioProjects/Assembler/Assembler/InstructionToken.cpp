#include "InstructionToken.h"

namespace bnss {

	InstructionToken::InstructionToken(size_t line_number, std::string line, InstructionCode code, std::vector<std::shared_ptr<Operand>> operands, OperandType type) noexcept : Token(line_number, line), code_(code), type_(type), operands_(operands) {}
}
