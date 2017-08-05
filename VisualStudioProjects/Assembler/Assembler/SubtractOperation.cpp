#include "SubtractOperation.h"
#include "MessageException.h"
#include "StringHelper.h"

namespace bnss {

	bool SubtractOperation::containsSymbol() const noexcept {
		if (Operation::containsSymbol()) {
			return symbolCount() == 0;
		}

		return false;
	}

	int SubtractOperation::symbolCount() const noexcept {
		return left()->symbolCount() - right()->symbolCount();
	}

	static void generateMaps(const std::list<RelocationRecord> &source, std::unordered_map<size_t, std::pair<RelocationRecord, size_t>> sections, std::unordered_map<std::string, std::pair<RelocationRecord, size_t>> symbols) {
		for (auto &element : source) {
			if (element.section()) {
				if (sections.count(element.sectionIndex()) > 0) {
					sections[element.sectionIndex()].second++;
				}
				else {
					sections[element.sectionIndex()] = std::make_pair(element, 1);
				}
			}
			else {
				if (symbols.count(element.symbol_name()) > 0) {
					symbols[element.symbol_name()].second++;
				}
				else {
					symbols[element.symbol_name()] = std::make_pair(element, 1);
				}
			}
		}
	}

	std::list<RelocationRecord> SubtractOperation::generateRelocations() const {
		auto left_list = left()->generateRelocations();
		auto right_list = right()->generateRelocations();
		
		std::unordered_map<size_t, std::pair<RelocationRecord, size_t>> left_sections;
		std::unordered_map<size_t, std::pair<RelocationRecord, size_t>> right_sections;

		std::unordered_map<std::string, std::pair<RelocationRecord, size_t>> left_symbols;
		std::unordered_map<std::string, std::pair<RelocationRecord, size_t>> right_symbols;

		generateMaps(left_list, left_sections, left_symbols);
		generateMaps(right_list, right_sections, right_symbols);

		std::list<RelocationRecord> ret;

		for (auto &element : left_sections) {
			if (right_sections.count(element.first) > 0) {
				if (right_sections.count(element.first) > left_sections.count(element.first)) {
					throw MessageException("Symbols from " + StringHelper::numberFormat(element.first + 1) + "th section are subtracted more times than added");
				}

				for (size_t i = 0; i < element.second.second - right_sections[element.first].second; i++) {
					ret.push_back(element.second.first);
				}
			}
		}

		for (auto &element : left_symbols) {
			if (right_symbols.count(element.first) > 0) {
				if (right_symbols.count(element.first) > left_symbols.count(element.first)) {
					throw MessageException("Symbol " + element.first + "is subtracted more times than added");
				}

				for (size_t i = 0; i < element.second.second - right_symbols[element.first].second; i++) {
					ret.push_back(element.second.first);
				}
			}
		}

		return ret;
	}

	int32_t SubtractOperation::calculate(int32_t lhs, int32_t rhs) const noexcept {
		return lhs - rhs;
	}
}
