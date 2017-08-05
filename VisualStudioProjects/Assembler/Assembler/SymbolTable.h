#ifndef _symbol_table_h_
#define _symbol_table_h_
#include "SymbolData.h"
#include <unordered_map>

namespace bnss {

	/**
	 * \brief Class representing the symbol table
	 */
	class SymbolTable : std::unordered_map<std::string, SymbolData> {
	public:
		/**
		 * \brief Inserts a symbol into the table
		 * \param data Symbol to be inserted
		 * \return Reference to this SymbolTable object after the insertion
		 */
		SymbolTable &operator+=(const SymbolData &data);

		/**
		 * \brief Check if the table contains a symbol
		 * \param symbol Symbol to be checked
		 * \return Whether the symbol exists in the table
		 */
		bool contains(std::string symbol) const noexcept;

		/**
		 * \brief Export a symbol
		 * \param symbol Symbol to be exported
		 */
		void exportSymbol(std::string symbol) noexcept;

		using unordered_map::at;
	};
}

#endif
