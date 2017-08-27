#include "RegisterIndirect.h"

namespace bnssassembler {

	RegisterIndirect::RegisterIndirect(Register reg) noexcept : reg_(reg) {}

	void RegisterIndirect::packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const {
		instruction.bit_field.address_mode = REGISTER_INDIRECT;
		
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

	AddressMode RegisterIndirect::addressMode() const noexcept {
		return REGISTER_INDIRECT;
	}
}
