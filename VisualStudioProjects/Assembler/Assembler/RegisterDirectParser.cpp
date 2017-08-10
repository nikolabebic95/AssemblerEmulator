#include "RegisterDirectParser.h"
#include "RegisterParser.h"
#include "RegisterDirect.h"

namespace bnssassembler {

	std::shared_ptr<Operand> RegisterDirectParser::parse(std::string str) const {
		try {
			return std::make_shared<RegisterDirect>(RegisterParser::parse(str));
		}
		catch (...) {
			return nullptr;
		}
	}
}
