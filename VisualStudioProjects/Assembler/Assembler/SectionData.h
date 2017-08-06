#ifndef _section_data_h_
#define _section_data_h_
#include "SectionType.h"
#include <functional>
// ReSharper disable once CppUnusedIncludeDirective
#include <cstddef>
// ReSharper disable once CppUnusedIncludeDirective
#include <utility>
#include <vector>
#include <list>
#include "RelocationRecord.h"

namespace bnss {
	
	/**
	 * \brief Class representing the data about one section
	 */
	class SectionData {
	public:
		/**
		 * \brief Construct a non-indexed SectionData object with the specified type
		 * \param type Type of the section
		 */
		explicit SectionData(SectionType type) noexcept;

		/**
		 * \brief Construct an indexed SectionData object with the specified type and index
		 * \param type Type of the section
		 * \param index Index of the section
		 */
		explicit SectionData(SectionType type, size_t index) noexcept;

		/**
		 * \brief Increases the location counter by an offset
		 * \param offset Offset
		 */
		void incLocationCounter(size_t offset) noexcept;

		/**
		 * \brief Get the type of the section
		 * \return Type of the section
		 */
		SectionType type() const noexcept;

		/**
		 * \brief Check whether the section is indexed
		 * \return Whether the section is indexed
		 */
		bool indexed() const noexcept;

		/**
		 * \brief Get the index of the section
		 * \return Index of the section
		 * 
		 * Undefined when the section is not indexed
		 */
		size_t index() const noexcept;

		/**
		 * \brief Gets the value of the location counter
		 * \return Value of the location counter
		 */
		size_t locationCounter() const noexcept;

		// Operator overloads: 
		friend bool operator==(const SectionData &lhs, const SectionData &rhs) noexcept;
		friend bool operator!=(const SectionData &lhs, const SectionData &rhs) noexcept;

		friend bool operator<(const SectionData &lhs, const SectionData &rhs) noexcept;
		friend bool operator>(const SectionData &lhs, const SectionData &rhs) noexcept;
		friend bool operator<=(const SectionData &lhs, const SectionData &rhs) noexcept;
		friend bool operator>=(const SectionData &lhs, const SectionData &rhs) noexcept;

		/**
		 * \brief Hash the sectionData object
		 * \return Hashed value
		 */
		size_t hash() const noexcept;

		/**
		 * \brief Adds 8 bits of data to the data array
		 * \param data Data to be addded
		 * \param relocations List of relocation records for the data
		 */
		void addData(uint8_t data, std::list<RelocationRecord> &relocations);

		/**
		 * \brief Adds 16 bits of data to the data array
		 * \param data Data to be addded
		 * \param relocations List of relocation records for the data
		 */
		void addData(uint16_t data, std::list<RelocationRecord> &relocations);

		/**
		 * \brief Adds 32 bits of data to the data array
		 * \param data Data to be addded
		 * \param relocations List of relocation records for the data
		 */
		void addData(uint32_t data, std::list<RelocationRecord> &relocations);

		/**
		 * \brief Sets the ORG address
		 * \param address ORG address
		 */
		void org(uint32_t address);

		/**
		* \brief Writes the content of the object to a stream
		* \param os Stream where the content will be written
		* \param data Data that will be written
		*/
		friend std::ostream &operator<<(std::ostream &os, const SectionData &data);
	private:
		SectionType type_;
		bool indexed_ = false;
		size_t index_ = 0;
		size_t location_counter_ = 0;
		uint32_t org_address_ = 0;
		bool org_valid_ = false;

		std::vector<uint8_t> data_;
		std::list<RelocationRecord> relocation_records_;

		/**
		 * \brief Adds 8 bits of data to the data array, without relocation records
		 * \param data Data to be added
		 */
		void addData(uint8_t data);
	};
}

namespace std {
	template <> struct hash<bnss::SectionData> {
		size_t operator()(const bnss::SectionData & section_data) const;
	};

	inline size_t hash<bnss::SectionData>::operator()(const bnss::SectionData & section_data) const {
		return hash<size_t>()(section_data.hash());
	}
}

#endif
