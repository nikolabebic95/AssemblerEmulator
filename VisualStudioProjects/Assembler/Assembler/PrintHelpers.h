#ifndef _print_helpers_h_
#define _print_helpers_h_
#include <string>

namespace bnss {
	const unsigned char UPPER_LEFT = 201;
	const unsigned char UPPER_RIGHT = 187;
	const unsigned char LOWER_LEFT = 200;
	const unsigned char LOWER_RIGHT = 188;
	const unsigned char HORIZONTAL = 205;
	const unsigned char VERTICAL = 186;
	const unsigned char T_LEFT = 185;
	const unsigned char T_RIGHT = 204;
	const unsigned char T_UP = 202;
	const unsigned char T_DOWN = 203;
	const unsigned char ALL_FOUR = 206;

	inline std::string multiple(unsigned char c, size_t times) {
		std::string ret;
		for (size_t i = 0; i < times; i++) {
			ret += c;
		}

		return ret;
	}
}

#endif
