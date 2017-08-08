#include "InstructionToken.h"
#include "InstructionBitFieldUnion.h"
#include "SecondPassData.h"
#include "Register.h"
#include "MessageException.h"

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

	void InstructionToken::secondPass(SecondPassData &data) const {
		if (data.currentSectionType() != TEXT) {
			throw MessageException("Instructions can only exist in text sections");
		}

		auto pair = packInstruction();
		data.addData(pair.first, std::list<RelocationRecord>());

		if (length() == 8) {
			data.addData(pair.second.first, pair.second.second);
		}
	}

	void InstructionToken::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		for (auto &operand : operands_) {
			operand->resolveSymbolTable(symbol_table);
		}
	}

	void InstructionToken::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		for (auto &operand : operands_) {
			operand->resolveImports(imported_symbols);
		}
	}

	void InstructionToken::resolveCurrentPcSymbol(size_t section_index, size_t offset) noexcept {
		for (auto &operand: operands_) {
			operand->resolveCurrentPcSymbol(section_index, offset);
		}
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

	std::pair<uint32_t, std::pair<uint32_t, std::list<RelocationRecord>>> InstructionToken::packInstruction() const {
		std::pair<uint32_t, std::pair<uint32_t, std::list<RelocationRecord>>> ret;
		InstructionBitFieldUnion instruction;
		
		instruction.bit_field.operation_code = code_;
		instruction.bit_field.address_mode = REGISTER_DIRECT; // Default address mode
		instruction.bit_field.register0 = NONE;
		instruction.bit_field.register1 = NONE;
		instruction.bit_field.register2 = NONE;
		instruction.bit_field.type = type_;
		
		for (auto &operand : operands_) {
			operand->packToInstruction(instruction, ret.second.first, ret.second.second);
		}

		// ReSharper disable once CppSomeObjectMembersMightNotBeInitialized
		ret.first = instruction.data;
		return ret;
	}
}
