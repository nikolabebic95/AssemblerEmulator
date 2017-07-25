#ifndef _register_direct_h_
#define _register_direct_h_
#include "Register.h"
#include "Operand.h"

namespace bnss {
	
	/**
	 * \brief Class representing the register direct operand
	 */
	class RegisterDirect : public Operand {
	public:
		explicit RegisterDirect(Register reg) noexcept;
		AddressMode addressMode() const noexcept override;
	private:
		Register reg_;
	};
}

#endif
