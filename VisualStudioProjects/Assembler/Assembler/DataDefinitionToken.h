#ifndef _data_definition_token_h_
#define _data_definition_token_h_
#include <vector>
#include "Data.h"
#include "Token.h"

namespace bnss {
	
	/**
	 * \brief Class representing the data definition token
	 */
	class DataDefinitionToken : public Token {
	public:
		DataDefinitionToken(std::vector<Data> data, size_t line_number, std::string line) noexcept;
	private:
		std::vector<Data> data_;
	};
}

#endif
