#include "SymbolData.h"

namespace bnss {

	SymbolData::SymbolData(std::string name, size_t section_index, size_t offset, bool local) noexcept : name_(name), section_index_(section_index), offset_(offset), local_(local) {}

	std::string SymbolData::name() const noexcept {
		return name_;
	}

	size_t SymbolData::sectionIndex() const noexcept {
		return section_index_;
	}

	size_t SymbolData::offset() const noexcept {
		return offset_;
	}

	bool SymbolData::local() const noexcept {
		return local_;
	}

	void SymbolData::exportSymbol() noexcept {
		local_ = false;
	}
}
