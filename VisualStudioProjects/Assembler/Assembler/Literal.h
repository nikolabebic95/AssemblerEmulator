#ifndef _literal_h_
#define _literal_h_
#include "Expression.h"
#include <cstdint>

namespace bnssassembler {
	
	/**
	 * \brief Class representing the literal value
	 */
	class Literal : public Expression {
	public:
		/**
		 * \brief Constructs a Literal object
		 * \param value Value of the 
		 */
		explicit Literal(int32_t value) noexcept;
		int32_t value() const override;
	private:
		int32_t value_;
	};
}

#endif
