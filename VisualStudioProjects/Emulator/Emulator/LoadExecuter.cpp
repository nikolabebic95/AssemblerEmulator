#include "LoadExecuter.h"
#include "OperandType.h"
#include "MessageException.h"
#include "StringHelper.h"

namespace bnssemulator {

	static const int32_t UNSIGNED_BYTE_MASK = 0x000000ff;
	static const int32_t UNSIGNED_WORD_MASK = 0x0000ffff;

	static const int32_t SIGNED_BYTE_TEST = 0x00000080;
	static const int32_t SIGNED_WORD_TEST = 0x00008000;

	static const int32_t SIGNED_BYTE_FILL = 0xffffff00;
	static const int32_t SIGNED_WORD_FILL = 0xffff0000;

	static uint32_t fill(OperandType type, int32_t operand) {
		switch (type) {
		case UNSIGNED_BYTE:
			return operand & UNSIGNED_BYTE_MASK;
		case SIGNED_BYTE:
			if ((operand & SIGNED_BYTE_TEST) != 0) {
				return operand | SIGNED_BYTE_FILL;
			}

			return operand;
		case UNSIGNED_WORD:
			return operand & UNSIGNED_WORD_MASK;
		case SIGNED_WORD:
			if ((operand & SIGNED_WORD_TEST) != 0) {
				return operand | SIGNED_WORD_FILL;
			}

			return operand;
		case REGULAR_DOUBLE_WORD:
			return operand;
		default:
			throw MessageException("Invalid operand type: " + StringHelper::toHexString(static_cast<int8_t>(type)));
		}
	}

	void LoadExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto num_of_bytes = instruction.type == REGULAR_DOUBLE_WORD ? 4 : instruction.type == UNSIGNED_WORD || instruction.type == SIGNED_WORD ? 2 : 1;
		auto operand = context.getOperand(instruction, 1, num_of_bytes);
		auto &reg = context.getRegister(instruction.register0);
		reg.value(fill(static_cast<OperandType>(instruction.type), operand));
	}
}
