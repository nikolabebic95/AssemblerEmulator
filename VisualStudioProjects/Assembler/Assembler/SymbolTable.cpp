#include "SymbolTable.h"
#include "SymbolData.h"
#include "PrintHelpers.h"
#include <iostream>
#include <iomanip>

namespace bnssassembler {

	SymbolTable &SymbolTable::operator+=(const SymbolData & data) {
		insert(make_pair(data.name(), data));
		return *this;
	}

	bool SymbolTable::contains(std::string symbol) const noexcept {
		return count(symbol) > 0;
	}

	void SymbolTable::exportSymbol(std::string symbol) noexcept {
		(*this)[symbol].exportSymbol();
	}

	std::ostream & operator<<(std::ostream &os, const SymbolTable &table) {
		std::cout << UPPER_LEFT << multiple(HORIZONTAL, 81) << UPPER_RIGHT << std::endl;
		std::cout << VERTICAL << UPPER_LEFT << multiple(HORIZONTAL, 79) << UPPER_RIGHT << VERTICAL << std::endl;
		std::cout << VERTICAL << VERTICAL << std::setw(79) << std::left << " Symbol table:" << VERTICAL << VERTICAL << std::endl;
		std::cout << VERTICAL << LOWER_LEFT << multiple(HORIZONTAL, 79) << LOWER_RIGHT << VERTICAL << std::endl;
		std::cout << T_RIGHT << multiple(HORIZONTAL, 47) << T_DOWN << multiple(HORIZONTAL, 9) << T_DOWN << multiple(HORIZONTAL, 8) << T_DOWN << multiple(HORIZONTAL, 14) << T_LEFT << std::endl;
		std::cout << VERTICAL << "                     Name                      " << VERTICAL << " Section " << VERTICAL << " Offset " << VERTICAL << " Global/Local " << VERTICAL << std::endl;
		std::cout << T_RIGHT << multiple(HORIZONTAL, 47) << ALL_FOUR << multiple(HORIZONTAL, 9) << ALL_FOUR << multiple(HORIZONTAL, 8) << ALL_FOUR << multiple(HORIZONTAL, 14) << T_LEFT << std::endl;

		os << table.size() << std::endl;
		for (auto &entry : table) {
			os << entry.second << std::endl;
		}
		
		std::cout << LOWER_LEFT << multiple(HORIZONTAL, 47) << T_UP << multiple(HORIZONTAL, 9) << T_UP << multiple(HORIZONTAL, 8) << T_UP << multiple(HORIZONTAL, 14) << LOWER_RIGHT << std::endl;

		return os;
	}
}
