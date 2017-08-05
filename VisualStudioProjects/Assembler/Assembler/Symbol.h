#ifndef _symbol_h_
#define _symbol_h_
#include "Expression.h"

namespace bnss {
	
	class Symbol : public Expression {
	public:
		explicit Symbol(std::string name) noexcept;
		int32_t value() const override;
		bool setValue(std::string symbol, std::shared_ptr<Expression> value) noexcept override;
		bool containsSymbol() const noexcept override;
		int symbolCount() const noexcept override;
		void resolveSymbolTable(const SymbolTable &symbol_table) noexcept override;
		void resolveImports(std::unordered_set<std::string> imported_symbols) noexcept override;
		std::list<RelocationRecord> generateRelocations() const override;

	private:
		std::string name_;
		
		std::shared_ptr<Expression> value_ = nullptr;
		bool assigned_ = false;

		int32_t relocatable_value_ = 0;
		bool relocatable_ = false;
		size_t section_index_ = 0;
		bool section_ = false;
		bool absolute_ = false;
	};
}

#endif
