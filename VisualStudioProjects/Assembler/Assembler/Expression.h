#ifndef _expression_h_
#define _expression_h_
#include <cstdint>
#include <memory>
#include <stack>
#include "SymbolTable.h"
#include <unordered_set>
#include <list>
#include "RelocationRecord.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the math expression
	 */
	class Expression {
	public:
		/**
		 * \brief Evaluates the expression
		 * \throw Throws if the expression has variables or could not be evaluated (for example, division by zero)
		 */
		virtual int32_t value() const = 0;

		/**
		 * \brief Traverses the subtree and sets the value for the symbol
		 * \param symbol Name of the symbol
		 * \param value New value of the symbol
		 * \return Whether the symbol was found and the value was set
		 */
		virtual bool setValue(std::string symbol, std::shared_ptr<Expression> value) noexcept;

		/**
		 * \brief Validates the expression
		 * \return Boolean value indicating whether the expression is correct
		 */
		virtual bool validate() const noexcept;

		/**
		* \brief Tests whether the expression contains a Symbol
		* \return Boolean value indicating whether the expression contains a Symbol
		*/
		virtual bool containsSymbol() const noexcept;

		/**
		 * \brief Counts the symbols in the expression
		 * \return Number of symbols in the expression
		 */
		virtual int symbolCount() const noexcept;
		
		/**
		 * \brief Pushes the children to the stack
		 * \param stack Reference to the stack
		 */
		virtual void pushChildren(std::stack<std::reference_wrapper<std::shared_ptr<Expression>>> &stack) const noexcept;

		/**
		 * \brief Resolves the symbols from the symbol table and sets the relocation info
		 * \param symbol_table Symbol table
		 */
		virtual void resolveSymbolTable(const SymbolTable &symbol_table) noexcept;

		/**
		 * \brief Resolves the imported symbols and sets the relocation info
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
		 * \brief Generates the relocation records for the subtree
		 * \return Collection of relocation records
		 */
		virtual std::list<RelocationRecord> generateRelocations() const;
		virtual ~Expression() = default;
	};
}

#endif
