#include "RegisterIndirectOffset.h"
#include "MessageException.h"

namespace bnss {

	RegisterIndirectOffset::RegisterIndirectOffset(Register reg, MicroRiscExpression offset_or_address, bool absolute) : reg_(reg), offset_or_address_(offset_or_address), absolute_(absolute) {
		if (absolute && reg != PC) {
			throw MessageException("Only PC relative address can be absolute");
		}
	}
}
