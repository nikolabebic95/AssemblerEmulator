#include "RelocationRecord.h"

namespace bnssemulator {

	std::istream &operator>>(std::istream & is, RelocationRecord & data) {
		is >> data.offset_;
		is >> data.absolute_;
		is >> data.section_;
		if (data.section_) {
			is >> data.section_index_;
		}
		else {
			is >> data.symbol_name_;
		}

		return is;
	}
}