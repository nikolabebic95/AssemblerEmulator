#ifndef _assembler_output_h_
#define _assembler_output_h_
#include <istream>

namespace bnssemulator {
	
	class AssemblerOutput {
	public:
		friend std::istream &operator>>(std::istream &is, const AssemblerOutput &data);
		// TODO: Implementation
	};
}

#endif
