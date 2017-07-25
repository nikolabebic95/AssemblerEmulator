#ifndef _operand_h_
#define _operand_h_
#include "SymbolDefinition.h"
#include "AddressMode.h"
#include <unordered_set>

namespace bnss {
	
	/**
	 * \brief Class representing one operand in an instruction
	 */
	class Operand {
	public:
		virtual void resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept;
		virtual AddressMode addressMode() const noexcept = 0;
		virtual ~Operand() = default;
	};
}

#endif
