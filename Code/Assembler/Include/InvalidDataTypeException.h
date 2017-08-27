#ifndef _invalid_data_type_exception_h_
#define _invalid_data_type_exception_h_
#include "MessageException.h"

namespace bnssassembler {
	
	/**
	 * \brief Exception representing the invalid data type
	 */
	class InvalidDataTypeException : public MessageException {
	public:
		/**
		 * \brief Constructs an InvalidDataTypeException
		 * \param data_type String containing the invalid DataType
		 */
		explicit InvalidDataTypeException(std::string data_type) noexcept;
	};
}

#endif
