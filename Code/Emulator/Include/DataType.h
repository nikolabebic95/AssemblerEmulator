#ifndef _data_type_h_
#define _data_type_h_

namespace bnssemulator {

	/**
	* \brief Enum representing a data type
	*/
	enum DataType : int8_t {
		DOUBLE_WORD = 0,	/**< 32bit value */
		WORD,				/**< 16bit value */
		BYTE				/**<  8bit value */
	};
}

#endif
