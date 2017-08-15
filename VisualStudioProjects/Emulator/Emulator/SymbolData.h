#ifndef _symbol_data_h_
#define _symbol_data_h_
#include <string>
#include <istream>

namespace bnssemulator {
	
	class SymbolData {
	public:
		/**
		* \brief Gets the name of the symbol
		* \return Name of the symbol
		*/
		std::string name() const noexcept;

		/**
		* \brief Loads the object from stream
		* \param is Input stream
		* \param data Reference to the object that should be loaded
		* \return Input stream
		*/
		friend std::istream &operator>>(std::istream &is, SymbolData &data);

		/**
		 * \brief Gets the index of the section where the symbol is defined
		 * \return Index of the section where the symbol is defined
		 */
		size_t sectionIndex() const noexcept;

		/**
		 * \brief Gets the offset of the symbol from the start of the section
		 * \return Offset of the symbol from the start of the section
		 */
		size_t offset() const noexcept;
	private:
		std::string name_;
		size_t section_index_ = 0;
		size_t offset_ = 0;
		bool local_ = false;
	};
}

#endif
