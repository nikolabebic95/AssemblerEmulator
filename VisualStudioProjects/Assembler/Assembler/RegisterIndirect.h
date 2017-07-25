#ifndef _register_indirect_h_
#define _register_indirect_h_
#include "Operand.h"
#include "Register.h"

namespace bnss {
	
	/**
	 * \brief Class representing the register indirect operand
	 */
	class RegisterIndirect : public Operand {
	public:
		explicit RegisterIndirect(Register reg) noexcept;
		AddressMode addressMode() const noexcept override;
	private:
		Register reg_;
	};
}

#endif
