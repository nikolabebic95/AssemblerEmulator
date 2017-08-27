#ifndef _print_helpers_h_
#define _print_helpers_h_
#include <string>

namespace bnssassembler {
#ifdef _MSC_VER
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
#else
	const std::string UPPER_LEFT = "\u2554";
	const std::string UPPER_RIGHT = "\u2557";
	const std::string LOWER_LEFT = "\u255a";
	const std::string LOWER_RIGHT = "\u255d";
	const std::string HORIZONTAL = "\u2550";
	const std::string VERTICAL = "\u2551";
	const std::string T_LEFT = "\u2563";
	const std::string T_RIGHT = "\u2560";
	const std::string T_UP = "\u2569";
	const std::string T_DOWN = "\u2566";
	const std::string ALL_FOUR = "\u256c";
#endif
	/**
	 * \brief Returns a string containing multiple of the same characters
	 * \param c Character
	 * \param times Number of times this character should be in the string
	 * \return String containing all the characters
	 */
	inline std::string multiple(unsigned char c, size_t times) {
		std::string ret;
		for (size_t i = 0; i < times; i++) {
			ret += c;
		}

		return ret;
	}

	/**
	* \brief Returns a string containing multiple of the same strings
	* \param s String
	* \param times Number of times this string should be in the returning string
	* \return String containing all the strings
	*/
	inline std::string multiple(std::string s, size_t times) {
		std::string ret;
		for (size_t i = 0; i < times; i++) {
			ret += s;
		}

		return ret;
	}
}

#endif
