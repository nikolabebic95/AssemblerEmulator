#ifndef _symbol_h_
#define _symbol_h_
#include "Expression.h"

namespace bnss {
	
	class Symbol : public Expression {
	public:
		explicit Symbol(std::string name) noexcept;
		int32_t value() const override;
		bool setValue(std::string symbol, std::shared_ptr<Expression> value) noexcept override;
		int symbolCount() const noexcept override;
	private:
		std::string name_;
		std::shared_ptr<Expression> value_ = nullptr;
		bool assigned_ = false;
	};
}

#endif
