#ifndef _symbol_data_h_
#define _symbol_data_h_
#include <string>

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
	private:
		std::string name_;
		size_t section_index_ = 0;
		size_t offset_ = 0;
		bool local_ = false;
	};
}

#endif
