#ifndef _section_data_h_
#define _section_data_h_
#include "SectionType.h"
#include "RelocationRecord.h"
#include <vector>
#include <istream>

namespace bnssemulator {
	
	class SectionData {
	public:
		/**
		* \brief Loads the object from stream
		* \param is Input stream
		* \param data Reference to the object that should be loaded
		* \return Input stream
		*/
		friend std::istream &operator>>(std::istream &is, SectionData &data);

		/**
		 * \brief Checks whether the section already has a starting address
		 * \return Whether the section already has a starting address
		 */
		bool hasAddress() const noexcept;

		/**
		 * \brief Gets the starting address of the section
		 * \return Starting address of the section
		 */
		uint32_t address() const noexcept;

		/**
		 * \brief Sets the starting address of the section
		 * \return Starting address of the section
		 */
		void address(uint32_t address) noexcept;

		/**
		 * \brief Gets the size of the sections
		 * \return Size of the section
		 */
		size_t size() const noexcept;

		/**
		 * \brief Gets the type of the section
		 * \return Type of the section
		 */
		SectionType type() const noexcept;

		/**
		 * \brief Gets the data vector of the section
		 * \return Data vector of the section
		 */
		std::vector<uint8_t> &data() noexcept;

		/**
		 * \brief Gets the data vector of the section
		 * \return Data vector of the section
		 */
		const std::vector<uint8_t> &data() const noexcept;
	private:
		SectionType type_ = TEXT;
		bool indexed_ = false;
		size_t index_ = 0;
		size_t location_counter_ = 0;
		uint32_t org_address_ = 0;
		bool org_valid_ = false;
		std::vector<uint8_t> data_;
		std::vector<RelocationRecord> relocation_records_;
	};
}

#endif

