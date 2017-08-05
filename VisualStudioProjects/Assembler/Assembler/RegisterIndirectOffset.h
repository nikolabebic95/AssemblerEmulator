#ifndef _register_indirect_offset_h_
#define _register_indirect_offset_h_
#include "Operand.h"
#include "Register.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	/**
	 * \brief Class representing the register indirect operand with offset
	 */
	class RegisterIndirectOffset : public Operand {
	public:
		RegisterIndirectOffset(Register reg, MicroRiscExpression offset_or_address, bool absolute);
		void packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const override;
		void resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		void resolveSymbolTable(const SymbolTable &symbol_table) noexcept override;
		void resolveImports(std::unordered_set<std::string> imported_symbols) noexcept override;
		AddressMode addressMode() const noexcept override;
	private:
		Register reg_;
		MicroRiscExpression offset_or_address_;
		bool absolute_ = false;
	};
}

#endif
