#ifndef _memory_direct_h_
#define _memory_direct_h_
#include "Operand.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	/**
	 * \brief Class representing the memory direct operand
	 */
	class MemoryDirect : public Operand {
	public:
		explicit MemoryDirect(MicroRiscExpression address) noexcept;
		void packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const override;
		void resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		void resolveSymbolTable(const SymbolTable &symbol_table) noexcept override;
		void resolveImports(std::unordered_set<std::string> imported_symbols) noexcept override;
		AddressMode addressMode() const noexcept override;
	private:
		MicroRiscExpression address_;
	};
}

#endif
