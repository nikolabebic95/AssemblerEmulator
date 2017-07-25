#ifndef _memory_direct_h_
#define _memory_direct_h_
#include "Operand.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	/**
	 * \brief Class representing the memory direct operand
	 */
	class MemoryDirect : public Operand {
	public:
		explicit MemoryDirect(MicroRiscExpression address) noexcept;
		void resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		AddressMode addressMode() const noexcept override;
	private:
		MicroRiscExpression address_;
	};
}

#endif
