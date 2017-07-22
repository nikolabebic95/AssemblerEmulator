#include "ExpressionTokenFactory.h"
#include <regex>
#include "CommonRegexes.h"
#include "MessageException.h"
#include "LiteralToken.h"
#include "SymbolToken.h"
#include "AddToken.h"
#include "SubtractToken.h"
#include "MultiplyToken.h"
#include "DivideToken.h"
#include "OpeningBraceToken.h"
#include "ClosingBraceToken.h"

namespace bnss {

	std::shared_ptr<ExpressionToken> ExpressionTokenFactory::create(std::string param) {
		if (regex_match(param, LITERAL_REGEX)) {
			return staticData().literals_->clone(param);
		}
		
		if (regex_match(param, OPERATOR_REGEX)) {
			return staticData().operators_[param]->clone(param);
		}
		
		if (regex_match(param, SYMBOL_REGEX)) {
			return staticData().symbols_->clone(param);
		}

		throw MessageException("Invalid expression token: " + param);
	}

	ExpressionTokenFactory::ExpressionTokenFactoryData &ExpressionTokenFactory::staticData() noexcept {
		static ExpressionTokenFactoryData static_data;
		return static_data;
	}

	ExpressionTokenFactory::ExpressionTokenFactoryData::ExpressionTokenFactoryData() noexcept {
		literals_ = std::make_shared<LiteralToken>("1");
		symbols_ = std::make_shared<SymbolToken>("OvdeMoguStaHocuDaNapisem");
		
		auto add = std::make_shared<AddToken>();
		operators_[add->operation()] = add;
		auto sub = std::make_shared<SubtractToken>();
		operators_[sub->operation()] = sub;
		auto mul = std::make_shared<MultiplyToken>();
		operators_[mul->operation()] = mul;
		auto div = std::make_shared<DivideToken>();
		operators_[div->operation()] = div;
		auto opb = std::make_shared<OpeningBraceToken>();
		operators_[opb->operation()] = opb;
		auto clb = std::make_shared<ClosingBraceToken>();
		operators_[clb->operation()] = clb;
	}
}
