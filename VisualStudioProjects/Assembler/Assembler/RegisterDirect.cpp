#include "RegisterDirect.h"

namespace bnssassembler {

	RegisterDirect::RegisterDirect(Register reg) noexcept : reg_(reg) {}

	void RegisterDirect::packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const {
		if (instruction.bit_field.register0 == NONE) {
			instruction.bit_field.register0 = reg_;
			return;
		}

		if (instruction.bit_field.register1 == NONE) {
			instruction.bit_field.register1 = reg_;
			return;
		}

		if (instruction.bit_field.register2 == NONE) {
			instruction.bit_field.register2 = reg_;
		}
	}

	AddressMode RegisterDirect::addressMode() const noexcept {
		return REGISTER_DIRECT;
	}
}
