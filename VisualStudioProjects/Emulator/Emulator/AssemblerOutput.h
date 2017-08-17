#ifndef _assembler_output_h_
#define _assembler_output_h_
#include <istream>
#include "SectionData.h"
#include "SymbolData.h"
#include <unordered_set>
#include <vector>
#include <unordered_map>

namespace bnssemulator {
	
	class AssemblerOutput {
	public:
		/**
		 * \brief Loads the object from stream
		 * \param is Input stream
		 * \param data Reference to the object that should be loaded
		 * \return Input stream
		 */
		friend std::istream &operator>>(std::istream &is, AssemblerOutput &data);
		
		/**
		 * \brief Gets the section table
		 * \return Section table
		 */
		std::vector<SectionData> &sectionTable() noexcept;

		/**
		 * \brief Gets the section table
		 * \return Section table
		 */
		const std::vector<SectionData> &sectionTable() const noexcept;

		/**
		 * \brief Gets the symbol table
		 * \return Symbol table
		 */
		std::unordered_map<std::string, SymbolData> &symbolTable() noexcept;

		/**
		 * \brief Gets the symbol table
		 * \return Symbol table
		 */
		const std::unordered_map<std::string, SymbolData> &symbolTable() const noexcept;

		/**
		 * \brief Checks if there are imported symbols
		 * \return Whether there are imported symbols
		 */
		bool importedSymbolsExist() const noexcept;

		/**
		 * \brief Gets the imported symbols as a vector of strings
		 * \return Imported symbols as a vector of strings
		 */
		std::vector<std::string> importedSymbolsAsVector() const noexcept;

		/**
		 * \brief Gets the address of the start of the program
		 * \param start_symbol Symbol representing the start of the program
		 * \return Address of the start of program
		 * \throw Throws if there is no start of program
		 */
		uint32_t startOfProgram(std::string start_symbol) const;
	private:
		std::unordered_set<std::string> imported_symbols_;
		std::vector<SectionData> section_table_;
		std::unordered_map<std::string, SymbolData> symbol_table_;
	};
}

#endif
