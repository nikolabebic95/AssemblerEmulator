#include "ExpressionBuilder.h"
#include <list>
#include "InvalidExpressionException.h"
#include <regex>
#include "CommonRegexes.h"
#include "ExpressionToken.h"
#include "ExpressionTokenFactory.h"

namespace bnss {

	/**
	 * \brief Fixes the expression that starts with an unary minus sign
	 * \param infix_expression Reference to the expression that will be fixed
	 * \param token_extractor Regex used to extract the first token from the string
	 */
	static void fixUnaryMinusStart(std::string &infix_expression, std::regex token_extractor) {
		if (regex_match(infix_expression, token_extractor)) {
			auto token_string = regex_replace(infix_expression, token_extractor, "$1");
			if (token_string == "-") {
				infix_expression = "0 " + infix_expression;
			}
		}
	}

	static std::list<std::shared_ptr<ExpressionToken>> infixToPostfix(std::string infix_expression) {
		std::list<std::shared_ptr<ExpressionToken>> ret;
		std::stack<std::shared_ptr<ExpressionToken>> stack;
		auto rank = 0;

		static std::regex end_of_infix("[[:space:]]");
		static std::regex token_extractor("[[:space:]]*(" + LITERAL + "|" + OPERATOR + "|" + SYMBOL + ")(.*)");

		fixUnaryMinusStart(infix_expression, token_extractor);

		while (true) {			
			if (infix_expression.size() == 0 || regex_match(infix_expression, end_of_infix)) {
				break;
			}

			if (!regex_match(infix_expression, token_extractor)) {
				throw InvalidExpressionException();
			}

			auto token_string = regex_replace(infix_expression, token_extractor, "$1");
			infix_expression = regex_replace(infix_expression, token_extractor, "$3");
			auto token = ExpressionTokenFactory::create(token_string);
			token->process(ret, stack, rank);
		}

		while (!stack.empty()) {
			ExpressionBuilder::popToPostfix(ret, stack, rank);
		}

		if (rank != 1) {
			throw MessageException("Invalid expression rank");
		}

		return ret;
	}

	/**
	 * \brief Builds a tree from the postfix expression
	 * \param postfix_expression Postfix expression
	 * \return Pointer to the root of the tree
	 */
	static std::shared_ptr<Expression> postfixToTree(const std::list<std::shared_ptr<ExpressionToken>> &postfix_expression) {
		if (postfix_expression.size() == 0) {
			return nullptr;
		}

		std::stack<std::reference_wrapper<std::shared_ptr<Expression>>> stack;
		std::shared_ptr<Expression> root = nullptr;
		stack.push(root);
		for (auto iterator = postfix_expression.rbegin(); iterator != postfix_expression.rend(); ++iterator) {
			if (stack.empty()) {
				throw MessageException("Invalid expression - not enough operators");
			}

			std::shared_ptr<Expression> &curr = stack.top();
			stack.pop();
			curr = iterator->get()->create();
			curr->pushChildren(stack);
		}

		return root;
	}

	static bool validateTree(std::shared_ptr<Expression> expression) noexcept {
		return expression->validate();
	}

	MicroRiscExpression ExpressionBuilder::build(std::string infix_expression) {
		auto postfix = infixToPostfix(infix_expression);
		auto tree = postfixToTree(postfix);
		return MicroRiscExpression(tree);
	}

	void ExpressionBuilder::popToPostfix(std::list<std::shared_ptr<ExpressionToken>>& output, std::stack<std::shared_ptr<ExpressionToken>>& stack, int & expression_rank) {
		if (stack.empty()) {
			throw MessageException("The oppening brace is missing");
		}

		auto top = stack.top();
		stack.pop();
		output.push_back(top);

		expression_rank += top->rank();
		if (expression_rank < 1) {
			throw MessageException("The expression is invalid - too many operators");
		}
	}
}
