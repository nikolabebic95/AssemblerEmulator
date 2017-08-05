#ifndef _token_h_
#define _token_h_

#include "FirstPassData.h"

namespace bnss {

	/**
	 * \brief Class representing one token of the assembler source file
	 */
	class Token {
	public:
		/**
		 * \brief Constructs a token
		 * \param line_number Number of the line in the assembler source file
		 * \param line Line in the assembler source file
		 */
		Token(size_t line_number, std::string line) noexcept;
		
		/**
		 * \brief Resolves symbol definitions in a token
		 * \param symbols Vector od symbol definitions that should be resolved
		 */
		virtual void resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept;

		/**
		 * \brief Executes the first pass over the token
		 * \param data Data that the token will modify
		 */
		virtual void firstPass(FirstPassData &data) const = 0;

		/**
		 * \brief Executes the second pass over the token
		 * \param data Data that the token will modify
		 */
		virtual void secondPass(SecondPassData &data) const = 0;

		/**
		 * \brief Check whether the token can use the ORG address
		 */
		virtual bool usesAddress() const noexcept;

		/**
		 * \brief Resolves the symbols from the symbol table and updates relocation info
		 * \param symbol_table Symbol table
		 */
		virtual void resolveSymbolTable(const SymbolTable &symbol_table) noexcept;

		/**
		 * \brief Resolves the imported symbols and updates relocation info
		 * \param imported_symbols Collection of imported symbols
		 */
		virtual void resolveImports(std::unordered_set<std::string> imported_symbols) noexcept;

		/**
		 * \brief Get the line number of the token
		 * \return Line number
		 */
		size_t lineNumber() const noexcept;

		/**
		 * \brief Get the line of the token
		 * \return line
		 */
		std::string line() const noexcept;

		virtual ~Token() = default;
	private:
		size_t line_number_;
		std::string line_;
	};
}

#endif
