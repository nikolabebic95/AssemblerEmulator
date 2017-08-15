#ifndef _address_h_
#define _address_h_
// ReSharper disable once CppUnusedIncludeDirective
#include <cstddef>
#include <cstdint>

namespace bnssemulator {

	const size_t BLOCK_BITS = 16;
	const uint32_t PAGE_MASK = ~0 << BLOCK_BITS;
	const uint32_t OFFSET_MASK = ~PAGE_MASK;
	const size_t BLOCK_SIZE = OFFSET_MASK + 1;
}

#endif
