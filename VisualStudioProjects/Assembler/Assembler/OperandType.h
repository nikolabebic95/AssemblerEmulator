#ifndef _operand_type_h_
#define _operand_type_h_
#include <cstdint>

namespace bnssassembler {
	
	/**
	 * \brief Enum representing the operand type
	 */
	enum OperandType : int8_t {
		DEFAULT					= 0b000,
		UNSIGNED_BYTE			= 0b011,
		SIGNED_BYTE				= 0b111,
		REGULAR_BYTE			= 0b111,
		UNSIGNED_WORD			= 0b001,
		SIGNED_WORD				= 0b101,
		REGULAR_WORD			= 0b101,
		REGULAR_DOUBLE_WORD		= 0b000
	};
}

#endif
