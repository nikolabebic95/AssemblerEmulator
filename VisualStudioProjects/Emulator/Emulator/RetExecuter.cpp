#include "RetExecuter.h"

namespace bnssemulator {

	void RetExecuter::execute(InstructionBitField instruction, Context & context) const {
		context.returnFromSubroutine();
	}
}
