#ifndef _relocation_record_h_
#define _relocation_record_h_
#include <string>
#include <istream>
#include "DataType.h"

namespace bnssemulator {
	
	class RelocationRecord {
	public:
		/**
		* \brief Loads the object from stream
		* \param is Input stream
		* \param data Reference to the object that should be loaded
		* \return Input stream
		*/
		friend std::istream &operator>>(std::istream &is, RelocationRecord &data);	
	private:
		size_t offset_ = 0;
		bool absolute_ = false;
		size_t section_index_ = 0;
		std::string symbol_name_;
		bool section_ = false;
		DataType data_type_ = DOUBLE_WORD;
		bool opposite_ = false;
	};
}

#endif
