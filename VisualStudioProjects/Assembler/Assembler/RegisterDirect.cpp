#include "RegisterDirect.h"

namespace bnss {

	RegisterDirect::RegisterDirect(Register reg) noexcept : reg_(reg) {}

	AddressMode RegisterDirect::addressMode() const noexcept {
		return REGISTER_DIRECT;
	}
}
