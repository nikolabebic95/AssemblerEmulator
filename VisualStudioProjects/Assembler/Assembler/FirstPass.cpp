#include "FirstPass.h"
#include "MessageException.h"
#include "FirstPassException.h"

namespace bnss {

	FirstPassData FirstPass::execute(std::vector<std::shared_ptr<Token>> tokens) {
		FirstPassData ret;
		for (auto &token : tokens) {
			try {
				token->resolveSymbolDefinitions(ret.symbolDefinitions());
				token->firstPass(ret);
			}
			catch (MessageException &exception) {
				throw FirstPassException(token->lineNumber(), token->line(), exception.message());
			}
		}

		return ret;
	}
}
