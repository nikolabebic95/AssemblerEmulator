#ifndef _register_indirect_h_
#define _register_indirect_h_
#include "Operand.h"
#include "Register.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the register indirect operand
	 */
	class RegisterIndirect : public Operand {
	public:
		explicit RegisterIndirect(Register reg) noexcept;
		void packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const override;
		AddressMode addressMode() const noexcept override;
	private:
		Register reg_;
	};
}

#endif
