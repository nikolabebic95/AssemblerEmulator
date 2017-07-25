#ifndef _address_mode_h_
#define _address_mode_h_

namespace bnss {
	
	/**
	 * \brief Enum representing the address mode
	 */
	enum AddressMode {
		IMMEDIATE,
		REGISTER_DIRECT,
		MEMORY_DIRECT,
		REGISTER_INDIRECT,
		REGISTER_INDIRECT_OFFSET
	};
}

#endif
