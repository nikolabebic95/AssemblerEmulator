#ifndef _invalid_data_definition_exception_h_
#define _invalid_data_definition_exception_h_
#include "MessageException.h"

namespace bnssassembler {
	
	/**
	 * \brief Exception representing invalid data definition
	 */
	class InvalidDataDefinitionException : public MessageException {
	public:
		/**
		 * \brief Constructs an InvalidDataDefinitionException object
		 * \param data String containing the invalid data
		 */
		explicit InvalidDataDefinitionException(std::string data) noexcept;
	};
}

#endif
