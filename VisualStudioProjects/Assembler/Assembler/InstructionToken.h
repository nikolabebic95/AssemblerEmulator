#ifndef _instruction_token_h_
#define _instruction_token_h_

#include "Token.h"
#include <vector>
#include "Operand.h"
#include "InstructionCode.h"
#include <memory>
#include "OperandType.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the instruction in an assembler source file
	 */
	class InstructionToken : public Token {
	public:
		/**
		 * \brief Constructs an InstructionToken object
		 * \param line_number Number of the line where the instruction is
		 * \param line Line where the instruction is
		 * \param code Instruction code
		 * \param operands Vector of operands of the instruction
		 * \param type Type of the operand
		 */
		InstructionToken(size_t line_number, std::string line, InstructionCode code, std::vector<std::shared_ptr<Operand>> operands, OperandType type = DEFAULT) noexcept;

		void resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		void firstPass(FirstPassData &data) const override;
		void secondPass(SecondPassData &data) const override;
		void resolveSymbolTable(const SymbolTable &symbol_table) noexcept override;
		void resolveImports(std::unordered_set<std::string> imported_symbols) noexcept override;
		void resolveCurrentPcSymbol(size_t section_index, size_t offset) noexcept override;
	private:
		InstructionCode code_;
		OperandType type_;
		std::vector<std::shared_ptr<Operand>> operands_;

		/**
		 * \brief Gets the length of the instruction in bytes
		 * \return Length of the instruction in bytes
		 */
		size_t length() const;

		std::pair<uint32_t, std::pair<uint32_t, std::list<RelocationRecord>>> packInstruction() const;
	};
}

#endif
