#ifndef _immediate_h_
#define _immediate_h_
#include "Operand.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	/**
	 * \brief Class representing the immediate operand
	 */
	class Immediate : public Operand {
	public:
		explicit Immediate(MicroRiscExpression value) noexcept;
		void packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const override;
		void resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		void resolveSymbolTable(const SymbolTable &symbol_table) noexcept override;
		void resolveImports(std::unordered_set<std::string> imported_symbols) noexcept override;
		void resolveCurrentPcSymbol(size_t section_index, size_t offset) noexcept override;
		AddressMode addressMode() const noexcept override;
	private:
		MicroRiscExpression value_;
	};
}

#endif
