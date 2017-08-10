#ifndef _first_pass_h_
#define _first_pass_h_
#include "FirstPassData.h"
#include "Token.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the executor of the first pass
	 */
	class FirstPass final {
	public:
		static FirstPassData execute(std::vector<std::shared_ptr<Token>> tokens);
	private:
		FirstPass() = delete;
		FirstPass(FirstPass &) = delete;
		void operator=(FirstPass &) = delete;
	};
}

#endif
