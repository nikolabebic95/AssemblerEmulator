#ifndef _expression_token_factory_h_
#define _expression_token_factory_h_
#include <memory>
#include "ExpressionToken.h"
#include <unordered_map>

namespace bnssassembler {
	
	/**
	 * \brief Utility class used for creating the ExpressionToken objects
	 */
	class ExpressionTokenFactory final {
	public:
		/**
		 * \brief Creates an expression token using the provided string
		 * \param param String used for token creation
		 * \return Pointer to the created token
		 */
		static std::shared_ptr<ExpressionToken> create(std::string param);
	private:
		struct ExpressionTokenFactoryData {
			std::unordered_map<std::string, std::shared_ptr<ExpressionToken>> operators_;
			std::shared_ptr<ExpressionToken> literals_;
			std::shared_ptr<ExpressionToken> symbols_;
			ExpressionTokenFactoryData() noexcept;
		};

		static ExpressionTokenFactoryData &staticData() noexcept;

		ExpressionTokenFactory() = delete;
		ExpressionTokenFactory(ExpressionTokenFactory &) = delete;
		void operator=(ExpressionTokenFactory &) = delete;
	};
}

#endif
