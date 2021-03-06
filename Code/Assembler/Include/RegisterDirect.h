#ifndef _register_direct_h_
#define _register_direct_h_
#include "Register.h"
#include "Operand.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the register direct operand
	 */
	class RegisterDirect : public Operand {
	public:
		/**
		 * \brief Constructs a register direct object
		 * \param reg Register
		 */
		explicit RegisterDirect(Register reg) noexcept;

		void packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const override;
		AddressMode addressMode() const noexcept override;
	private:
		Register reg_;
	};
}

#endif
