#ifndef _relocation_record_h_
#define _relocation_record_h_
#include <string>
#include <istream>

namespace bnssemulator {
	
	class RelocationRecord {
	public:
		/**
		* \brief Loads the object from stream
		* \param is Input stream
		* \param data Reference to the object that should be loaded
		* \return Input stream
		*/
		friend std::istream &operator>>(std::istream &is, RelocationRecord &data);	

		/**
		 * \brief Gets the offset of the relocation record
		 * \return Offset of the relocation record
		 */
		size_t offset() const noexcept;

		/**
		 * \brief Checks whether the relocation is absolute or relative
		 * \return Whether the relocation is absolute or relative
		 */
		bool absolute() const noexcept;

		/**
		* \brief Gets the section index of the relocation
		* \return Section index
		*/
		size_t sectionIndex() const noexcept;

		/**
		* \brief Gets the symbol name of the relocation
		* \return Symbol name
		*/
		std::string symbolName() const noexcept;

		/**
		* \brief Test whether the relocation is by section or by symbol
		* \return Whether the relocation is by section
		*/
		bool section() const noexcept;
	private:
		size_t offset_ = 0;
		bool absolute_ = false;
		size_t section_index_ = 0;
		std::string symbol_name_;
		bool section_ = false;
	};
}

#endif
