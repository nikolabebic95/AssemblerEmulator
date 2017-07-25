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

		using vector::back;
		using vector::empty;
		using vector::size;
	private:
		std::unordered_set<SectionData> set_;
	};
}

#endif
