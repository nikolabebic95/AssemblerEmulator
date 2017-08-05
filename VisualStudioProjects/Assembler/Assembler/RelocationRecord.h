#ifndef _relocation_record_h_
#define _relocation_record_h_
#include <string>
#include "DataType.h"

namespace bnss {
	
	/**
	 * \brief Class representing one relocation record
	 */
	class RelocationRecord {
	public:
		RelocationRecord() = default;

		/**
		 * \brief Create a relocation record using a section
		 * \param absolute Boolean value indicating whether the relocation is absolute or relative
		 * \param section_index Index of relocation section
		 */
		RelocationRecord(bool absolute, size_t section_index) noexcept;

		/**
		 * \brief Create a relocation record using a symbol
		 * \param absolute Boolean value indicating whether the relocation is absolute or relative
		 * \param symbol_name Name of the relocation symbol
		 */
		RelocationRecord(bool absolute, std::string symbol_name) noexcept;

		/**
		 * \brief Sets the offset of the relocation
		 * \param offset New offset
		 */
		void offset(size_t offset) noexcept;

		/**
		 * \brief Sets the data type of the relocation
		 */
		void dataType(DataType data_type) noexcept;

		/**
		 * \brief Gets the section index of the relocation
		 * \return Section index
		 */
		size_t sectionIndex() const noexcept;

		/**
		 * \brief Gets the symbol name of the relocation
		 * \return Symbol name
		 */
		std::string symbol_name() const noexcept;

		/**
		 * \brief Test whether the relocation is by section or by symbol
		 * \return Whether the relocation is by section
		 */
		bool section() const noexcept;
	private:
		size_t offset_ = 0;
		bool absolute_;
		size_t section_index_ = 0;
		std::string symbol_name_;
		bool section_;
		DataType data_type_ = DOUBLE_WORD;
	};
}

#endif
