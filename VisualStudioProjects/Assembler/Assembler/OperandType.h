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
		BYTE = 3,
		UNSIGNED_WORD = 4,
		SIGNED_WORD = 5,
		WORD = 6,
		DOUBLE_WORD = 7
	};
}

#endif
