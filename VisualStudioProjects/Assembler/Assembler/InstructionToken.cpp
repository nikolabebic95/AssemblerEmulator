#include "InstructionToken.h"

namespace bnss {

	InstructionToken::InstructionToken(size_t line_number, std::string line, InstructionCode code, std::vector<std::shared_ptr<Operand>> operands, OperandType type) noexcept : Token(line_number, line), code_(code), type_(type), operands_(operands) {}

	void InstructionToken::resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &operand : operands_) {
			operand->resolveSymbols(symbols);
		}
	}

	void InstructionToken::firstPass(FirstPassData &data) const {
		data.incLocationCounter(length());
	}

	size_t InstructionToken::length() const {
		for (auto &operand : operands_) {
			if (
				operand->addressMode() == IMMEDIATE ||
				operand->addressMode() == MEMORY_DIRECT ||
				operand->addressMode() == REGISTER_INDIRECT_OFFSET)
				return 8;
		}

		return 4;
	}
}
