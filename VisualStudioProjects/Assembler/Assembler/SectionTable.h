#ifndef _section_table_h_
#define _section_table_h_
#include <vector>
#include "SectionData.h"
#include <unordered_set>

namespace bnss {
	
	/**
	 * \brief Class representing the table of sections
	 */
	class SectionTable : std::vector<SectionData> {
	public:
		/**
		 * \brief Insert new section into the table
		 * \param data Section data to be inserted
		 * \return Reference to this section table after the insertion
		 */
		SectionTable &operator+=(const SectionData &data);

		/**
		 * \brief Increasses the current section index
		 */
		void nextSection() noexcept;

		/**
		 * \brief Gets the current section type
		 * \return Current section type
		 */
		SectionType currentSectionType() const noexcept;

		/**
		* \brief Adds 8 bits of data to the current section
		* \param data Data to be addded
		* \param relocations List of relocation records for the data
		*/
		void addData(uint8_t data, std::list<RelocationRecord> &relocations);

		/**
		* \brief Adds 16 bits of data to the current section
		* \param data Data to be addded
		* \param relocations List of relocation records for the data
		*/
		void addData(uint16_t data, std::list<RelocationRecord> &relocations);

		/**
		* \brief Adds 32 bits of data to the current section
		* \param data Data to be addded
		* \param relocations List of relocation records for the data
		*/
		void addData(uint32_t data, std::list<RelocationRecord> &relocations);

		/**
		* \brief Gets the current section
		* \return Current section
		*/
		SectionData &current() noexcept;

		/**
		 * \brief Gets the current section
		 * \return Current section
		 */
		const SectionData &current() const noexcept;

		/**
		 * \brief Writes the content of the object to a stream
		 * \param os Stream where the content will be written
		 * \param section_table Data that will be written
		 */
		friend std::ostream &operator<<(std::ostream &os, const SectionTable &section_table);

		using vector::back;
		using vector::empty;
		using vector::size;
	private:
		std::unordered_set<SectionData> set_;
		size_t current_index_ = -1;
	};
}

#endif
