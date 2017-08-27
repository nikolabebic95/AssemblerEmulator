#ifndef _alu_executer_h_
#define _alu_executer_h_
#include "Executer.h"

namespace bnssemulator {
	
	/**
	 * \brief Base class used for executing ALU instructions
	 */
	class AluExecuter : public Executer {
	public:
		void execute(InstructionBitField instruction, Context &context) const override;
	protected:

		/**
		 * \brief Executes the ALU instruction
		 * \param dst Reference to the destination register
		 * \param lhs Left operand register
		 * \param rhs Right operand register
		 */
		virtual void execute(Register &dst, const Register &lhs, const Register &rhs) const = 0;
	};
}

#endif
