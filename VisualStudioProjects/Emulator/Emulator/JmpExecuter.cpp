#include "JmpExecuter.h"

namespace bnssemulator {

	void JmpExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto address = context.getOperandAddress(instruction, 0);
		context.jumpTo(address);
	}
}
