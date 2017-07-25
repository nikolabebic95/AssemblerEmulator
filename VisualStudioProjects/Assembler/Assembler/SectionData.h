#ifndef _section_data_h_
#define _section_data_h_
#include "SectionType.h"
#include <functional>

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

		size_t hash() const noexcept;

	private:
		SectionType type_;
		bool indexed_ = false;
		size_t index_ = 0;
		size_t location_counter_ = 0;
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
