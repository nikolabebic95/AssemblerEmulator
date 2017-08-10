#ifndef _section_data_h_
#define _section_data_h_
#include "SectionType.h"
#include "RelocationRecord.h"
#include <vector>

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
	private:
		SectionType type_ = TEXT;
		bool indexed_ = false;
		size_t index_ = 0;
		size_t location_counter_ = 0;
		uint32_t org_address_ = 0;
		bool org_valid_ = false;
		std::vector<int8_t> data_;
		std::vector<RelocationRecord> relocation_records_;
	};
}

#endif
