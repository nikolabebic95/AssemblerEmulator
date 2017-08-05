#ifndef _symbol_data_h_
#define _symbol_data_h_
#include <string>

namespace bnss {
	
	/**
	 * \brief Class representing data about one symbol
	 */
	class SymbolData {
	public:
		SymbolData() = default;

		/**
		 * \brief Construct a SymbolData object
		 */
		SymbolData(std::string name, size_t section_index, size_t offset, bool local) noexcept;

		/**
		 * \brief Gets the name of the symbol
		 * \return Name of the symbol
		 */
		std::string name() const noexcept;

		/**
		 * \brief Get the index of the section where the symbol is located
		 * \return Index of section
		 */
		size_t sectionIndex() const noexcept;

		/**
		 * \brief Get the symbol offset from the start of the section
		 * \return Offset from the start of the section
		 */
		size_t offset() const noexcept;

		/**
		 * \brief Get whether the symbol is local or global
		 * \return Boolean value indicating whether the symbol is local
		 */
		bool local() const noexcept;

		/**
		 * \brief Exports the symbol
		 */
		void exportSymbol() noexcept;
	private:
		std::string name_;
		size_t section_index_;
		size_t offset_;
		bool local_;
	};
}

#endif
