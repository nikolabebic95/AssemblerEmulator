#ifndef _first_pass_data_h_
#define _first_pass_data_h_
#include "SymbolTable.h"
#include "SectionTable.h"
#include "SymbolDefinition.h"
#include <unordered_set>

namespace bnss {
	
	/**
	 * \brief Class representing the data that the two-pass assembler will modify in the first pass
	 */
	class FirstPassData {
	public:
		/**
		 * \brief Increases the location counter of the current section
		 */
		void incLocationCounter(size_t offset);

		/**
		 * \brief Inserts a symbol into the symbol table
		 */
		void insertSymbol(std::string symbol);

		/**
		 * \brief Inserts a non-indexed section into the section table
		 * \param type Type of the section
		 */
		void insertSection(SectionType type);

		/**
		 * \brief Inserts an indexed section into the section table
		 * \param type Type of the section
		 * \param index Index of the section
		 */
		void insertSection(SectionType type, size_t index);

		/**
		 * \brief Inserts a symbol definition into the vector
		 * \param symbol SymbolDefinition object to insert
		 */
		void insertSymbolDefinition(SymbolDefinition symbol);

		/**
		 * \brief Get the symbol definitions
		 * \return Symbol definitions
		 */
		std::unordered_set<SymbolDefinition> symbolDefinitions() const noexcept;
	private:
		SymbolTable symbol_table_;
		SectionTable section_table_;
		std::unordered_set<SymbolDefinition> symbol_definitions_;

		/**
		 * \brief Inserts a section into the section table
		 * \param section_data Section data to be inserted
		 */
		void insertSection(SectionData section_data);
	};
}

#endif
