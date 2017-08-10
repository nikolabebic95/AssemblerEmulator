#include "AddOperation.h"
#include "SubtractOperation.h"
#include "RelocationRecord.h"

namespace bnssassembler {

	int32_t AddOperation::calculate(int32_t lhs, int32_t rhs) const noexcept {
		return lhs + rhs;
	}

	static void split(std::list<RelocationRecord> &original, std::list<RelocationRecord> &left, std::list<RelocationRecord> &right) {
		for (auto &element : original) {
			if (element.opposite()) {
				element.toggleOpposite();
				right.push_back(element);
			}
			else {
				left.push_back(element);
			}
		}
	}

	std::list<RelocationRecord> AddOperation::generateRelocations() const {
		auto original = Operation::generateRelocations();
		std::list<RelocationRecord> left;
		std::list<RelocationRecord> right;

		split(original, left, right);
		return SubtractOperation::generateRelocations(left, right);
	}

}
