#include "SecondPass.h"
#include "MessageException.h"
#include "SecondPassException.h"

namespace bnss {

	SecondPassData SecondPass::execute(std::vector<std::shared_ptr<Token>> tokens, FirstPassData && first_pass_data) {
		SecondPassData ret(std::move(first_pass_data));

		for (auto &token : tokens) {
			try {
				if (ret.orgValid() && !token->usesAddress()) {
					throw MessageException("ORG directive must be followed by a section start");
				}

				token->resolveSymbolTable(ret.symbolTable());
				token->resolveImports(ret.importedSymbols());
				token->secondPass(ret);
			} catch (MessageException &exception) {
				throw SecondPassException(token->lineNumber(), token->line(), exception.message());
			}
		}

		return ret;
	}
}
