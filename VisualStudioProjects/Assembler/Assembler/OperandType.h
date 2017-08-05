#ifndef _operand_type_h_
#define _operand_type_h_

namespace bnss {
	
	/**
	 * \brief Enum representing the operand type
	 */
	enum OperandType {
		DEFAULT = 0,
		UNSIGNED_BYTE = 1,
		SIGNED_BYTE = 2,
		REGULAR_BYTE = 3,
		UNSIGNED_WORD = 4,
		SIGNED_WORD = 5,
		REGULAR_WORD = 6,
		REGULAR_DOUBLE_WORD = 7
	};
}

#endif
