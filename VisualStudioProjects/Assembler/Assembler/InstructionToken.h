#ifndef _instruction_token_h_
#define _instruction_token_h_

#include "Token.h"
#include <vector>
#include "Operand.h"
#include "InstructionCode.h"
#include <memory>
#include "OperandType.h"

namespace bnss {
	
	/**
	 * \brief Class representing the instruction in an assembler source file
	 */
	class InstructionToken : public Token {
	public:
		InstructionToken(size_t line_number, std::string line, InstructionCode code, std::vector<std::shared_ptr<Operand>> operands, OperandType type = DEFAULT) noexcept;

	private:
		InstructionCode code_;
		OperandType type_;
		std::vector<std::shared_ptr<Operand>> operands_;
	};
}

#endif
