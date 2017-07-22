#include "RegisterIndirectOffset.h"

namespace bnss {

	RegisterIndirectOffset::RegisterIndirectOffset(Register reg, MicroRiscExpression offset) noexcept : reg_(reg), offset_(offset) {}
}
