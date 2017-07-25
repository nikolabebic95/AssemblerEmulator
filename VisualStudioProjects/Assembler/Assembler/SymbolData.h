#ifndef _symbol_data_h_
#define _symbol_data_h_
#include <string>

namespace bnss {
	
	/**
	 * \brief Class representing data about one symbol
	 */
	class SymbolData {
	public:
		/**
		 * \brief Construct a SymbolData object
		 */
		SymbolData(std::string name, size_t section_index, size_t offset, bool local) noexcept;

		/**
		 * \brief Gets the name of the symbol
		 * \return Name of the symbol
		 */
		std::string name() const noexcept;
	private:
		std::string name_;
		size_t section_index_;
		size_t offset_;
		bool local_;
	};
}

#endif
