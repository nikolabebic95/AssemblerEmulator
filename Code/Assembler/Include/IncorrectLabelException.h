#ifndef _incorrect_label_exception_h_
#define _incorrect_label_exception_h_
#include <string>
#include "MessageException.h"

namespace bnssassembler {
	
	/**
	 * \brief Exception representing the incorrect label
	 */
	class IncorrectLabelException : public MessageException {
	public:
		/**
		 * \brief Constructs an IncorrectLabelException object
		 * \param label Label that was incorrect
		 */
		explicit IncorrectLabelException(std::string label) noexcept;
	};
}

#endif
