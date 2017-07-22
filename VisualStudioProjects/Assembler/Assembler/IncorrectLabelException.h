#ifndef _incorrect_label_exception_h_
#define _incorrect_label_exception_h_
#include <string>
#include "MessageException.h"

namespace bnss {
	
	/**
	 * \brief Exception representing the incorrect label
	 */
	class IncorrectLabelException : public MessageException {
	public:
		explicit IncorrectLabelException(std::string label) noexcept;
	};
}

#endif
