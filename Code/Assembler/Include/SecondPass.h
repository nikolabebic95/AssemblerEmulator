#ifndef _second_pass_h_
#define _second_pass_h_
#include "SecondPassData.h"
#include "Token.h"

namespace bnssassembler {
	
	/**
	 * \brief Utility class executing the second pass
	 */
	class SecondPass final {
	public:
		/**
		 * \brief Executes the second pass using the first pass
		 * \param tokens Vector of parsed tokens
		 * \param first_pass_data Data generated from the first pass
		 */
		static SecondPassData execute(std::vector<std::shared_ptr<Token>> tokens, FirstPassData &&first_pass_data);
	private:
		SecondPass() = delete;
		SecondPass(SecondPass &) = delete;
		void operator=(SecondPass &) = delete;
	};
}

#endif
