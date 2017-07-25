#ifndef _immediate_h_
#define _immediate_h_
#include "Operand.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	/**
	 * \brief Class representing the immediate operand
	 */
	class Immediate : public Operand {
	public:
		explicit Immediate(MicroRiscExpression value) noexcept;
		void resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		AddressMode addressMode() const noexcept override;
	private:
		MicroRiscExpression value_;
	};
}

#endif
