#include "SubtractOperation.h"
#include "StringHelper.h"

namespace bnssassembler {

	bool SubtractOperation::containsSymbol() const noexcept {
		if (Operation::containsSymbol()) {
			return symbolCount() == 0;
		}

		return false;
	}

	int SubtractOperation::symbolCount() const noexcept {
		return left()->symbolCount() - right()->symbolCount();
	}

	static void generateMaps(const std::list<RelocationRecord> &source, std::unordered_map<size_t, std::pair<RelocationRecord, size_t>> &sections, std::unordered_map<std::string, std::pair<RelocationRecord, size_t>> &symbols) {
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
				if (symbols.count(element.symbolName()) > 0) {
					symbols[element.symbolName()].second++;
				}
				else {
					symbols[element.symbolName()] = std::make_pair(element, 1);
				}
			}
		}
	}

	static void exchange(std::list<RelocationRecord> &left, std::list<RelocationRecord> &right) {
		std::list<RelocationRecord> for_right;
		std::list<RelocationRecord> for_left;

		for (auto &element : left) {
			if (element.opposite()) {
				for_right.push_back(element);
			}
		}

		for (auto &element : right) {
			if (element.opposite()) {
				for_left.push_back(element);
			}
		}

		for (auto &element : for_right) {
			element.toggleOpposite();
			right.push_back(element);
			left.remove(element);
		}

		for (auto &element : for_left) {
			element.toggleOpposite();
			left.push_back(element);
			right.remove(element);
		}
	}

	std::list<RelocationRecord> SubtractOperation::generateRelocations() const {
		auto left_list = left()->generateRelocations();
		auto right_list = right()->generateRelocations();
		return generateRelocations(left_list, right_list);
	}

	std::list<RelocationRecord> SubtractOperation::generateRelocations(std::list<RelocationRecord> left_list, std::list<RelocationRecord> right_list) {
		std::unordered_map<size_t, std::pair<RelocationRecord, size_t>> left_sections;
		std::unordered_map<size_t, std::pair<RelocationRecord, size_t>> right_sections;

		std::unordered_map<std::string, std::pair<RelocationRecord, size_t>> left_symbols;
		std::unordered_map<std::string, std::pair<RelocationRecord, size_t>> right_symbols;

		exchange(left_list, right_list);

		generateMaps(left_list, left_sections, left_symbols);
		generateMaps(right_list, right_sections, right_symbols);

		std::list<RelocationRecord> ret;

		for (auto &element : left_sections) {
			if (right_sections.count(element.first) < left_sections.count(element.first)) {
				for (size_t i = 0; i < element.second.second - right_sections[element.first].second; i++) {
					ret.push_back(element.second.first);
				}
			}
		}

		for (auto &element : right_sections) {
			if (left_sections.count(element.first) < right_sections.count(element.first)) {
				for (size_t i = 0; i < element.second.second - left_sections[element.first].second; i++) {
					element.second.first.toggleOpposite();
					ret.push_back(element.second.first);
				}
			}
		}

		for (auto &element : left_symbols) {
			if (right_symbols.count(element.first) < left_symbols.count(element.first)) {
				for (size_t i = 0; i < element.second.second - right_symbols[element.first].second; i++) {
					ret.push_back(element.second.first);
				}
			}
		}

		for (auto &element : right_symbols) {
			if (left_symbols.count(element.first) < right_symbols.count(element.first)) {
				for (size_t i = 0; i < element.second.second - right_symbols[element.first].second; i++) {
					element.second.first.toggleOpposite();
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
