#include "IntExecuter.h"

namespace bnssemulator {

	void IntExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto &entry = context.getRegister(instruction.register0);
		
		if (entry == 0) {
			context.finishProgram();
			return;
		}

		context.jumpToInterrupt(entry);
	}
}
