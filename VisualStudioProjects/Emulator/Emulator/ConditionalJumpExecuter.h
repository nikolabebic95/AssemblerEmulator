#ifndef _conditional_jump_executer_h_
#define _conditional_jump_executer_h_
#include "Executer.h"

namespace bnssemulator {
	
	/**
	 * \brief Base executer for conditional jump instructions
	 */
	class ConditionalJumpExecuter : public Executer {
	public:
		void execute(InstructionBitField instruction, Context &context) const override;
	protected:
		/**
		 * \brief Tests whether the jump should happen
		 * \param negative Negative flag of the register
		 * \param zero Zero flag of the register
		 * \param overflow Overflow flag of the register
		 * \param carry Carry flag of the register
		 * \return Whether the jump should happen
		 */
		virtual bool test(bool negative, bool zero, bool overflow, bool carry) const noexcept = 0;
	};
}

#endif
