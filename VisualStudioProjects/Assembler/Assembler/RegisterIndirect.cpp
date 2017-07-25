#include "RegisterIndirect.h"

namespace bnss {

	RegisterIndirect::RegisterIndirect(Register reg) noexcept : reg_(reg) {}

	AddressMode RegisterIndirect::addressMode() const noexcept {
		return REGISTER_INDIRECT;
	}
}
