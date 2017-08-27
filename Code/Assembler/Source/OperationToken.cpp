#include "OperationToken.h"
#include "MessageException.h"
#include "ExpressionBuilder.h"

namespace bnssassembler {
	void OperationToken::process(std::list<std::shared_ptr<ExpressionToken>>& output, std::stack<std::shared_ptr<ExpressionToken>>& stack, int & expression_rank) const {
		while (!stack.empty() && stack.top()->stackPriority() >= inputPriority()) {
			ExpressionBuilder::popToPostfix(output, stack, expression_rank);
		}

		if (isClosingBrace()) {
			if (!stack.empty()) {
				stack.pop();
			}
			else {
				throw MessageException("The opening brace is missing");
			}
		}
		else {
			stack.push(clone("dummy"));
		}
	}

	bool OperationToken::isClosingBrace() const noexcept {
		return false;
	}
}
