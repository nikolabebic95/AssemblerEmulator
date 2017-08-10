#include "SectionData.h"
#include <istream>

namespace bnssemulator {

	std::istream &operator>>(std::istream & is, SectionData & data) {
		int type;
		is >> type;
		data.type_ = static_cast<SectionType>(type);
		is >> data.indexed_;
		if (data.indexed_) {
			is >> data.index_;
		}

		is >> data.org_valid_;
		if (data.org_valid_) {
			is >> data.org_address_;
		}

		is >> data.location_counter_;
		size_t data_size;
		is >> data_size;
		for (size_t i = 0; i < data_size; i++) {
			int data_byte;
			is >> data_byte;
			data.data_.push_back(static_cast<int8_t>(data_byte));
		}

		size_t relocation_records_size;
		is >> relocation_records_size;
		for (size_t i = 0; i < relocation_records_size; i++) {
			RelocationRecord relocation_record;
			is >> relocation_record;
			data.relocation_records_.push_back(relocation_record);
		}

		return is;
	}
}
