#ifndef _operand_h_
#define _operand_h_
#include "SymbolDefinition.h"
#include "AddressMode.h"
#include <unordered_set>
#include "InstructionBitFieldUnion.h"

namespace bnss {
	
	/**
	 * \brief Class representing one operand in an instruction
	 */
	class Operand {
	public:
		/**
		 * \brief Packs the operand into the instruction
		 * \param instruction Reference to the first word of the instruction containing the instruction info
		 * \param second_word Reference to the second word of the instruction containing the address/value/displacement
		 * \param relocations Reference to the list of relocation records
		 */
		virtual void packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const = 0;

		/**
		 * \brief Resolves the defined symbols in the expressions
		 * \param symbols Collection of symbol definitions
		 */
		virtual void resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept;

		/**
		 * \brief Resolves the symbols from the symbol table and updates the relocation info
		 * \param symbol_table Symbol table
		 */
		virtual void resolveSymbolTable(const SymbolTable &symbol_table) noexcept;
		
		/**
		 * \brief Resolves the imported symbols and updates the relocation info
		 * \param imported_symbols Collection of imported symbols
		 */
		virtual void resolveImports(std::unordered_set<std::string> imported_symbols) noexcept;

		/**
		* \brief Resolves the current PC symbol and sets the relocation info
		* \param section_index Current PC section
		* \param offset PC address in relation to the current section beginning
		*/
		virtual void resolveCurrentPcSymbol(size_t section_index, size_t offset) noexcept;

		/**
		 * \brief Gets the address mode of the operand
		 * \return Address mode of the operand
		 */
		virtual AddressMode addressMode() const noexcept = 0;
		virtual ~Operand() = default;
	};
}

#endif
