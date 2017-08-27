#include "NotExecuter.h"

namespace bnssemulator {

	void NotExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto &dst = context.getRegister(instruction.register0);
		auto &src = context.getRegister(instruction.register1);

		dst = ~src;
	}
}
