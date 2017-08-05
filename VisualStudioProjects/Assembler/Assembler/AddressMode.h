#ifndef _address_mode_h_
#define _address_mode_h_

namespace bnss {
	
	/**
	 * \brief Enum representing the address mode
	 */
	enum AddressMode {
		IMMEDIATE					= 0b100,
		REGISTER_DIRECT				= 0b000,
		MEMORY_DIRECT				= 0b110,
		REGISTER_INDIRECT			= 0b010,
		REGISTER_INDIRECT_OFFSET	= 0b111
	};
}

#endif
