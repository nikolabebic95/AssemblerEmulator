#ifndef _string_helper_h_
#define _string_helper_h_

#include <vector>
#include "CommonRegexes.h"
#include <regex>
#include "MessageException.h"
#include <iomanip>
#include <sstream>

namespace bnss {

	/**
	 * \brief Utility class providing helper methods for std::string class
	 */
	class StringHelper final {
	public:
		/**
		 * \brief Reads the whole file into a string
		 * \param file_name Name of the file
		 * \return String containing the content of the file
		 * \throw Throws if the file does not exist or could not be opened for reading
		 */
		static std::string fileToString(std::string file_name);

		/**
		 * \brief Splits the string using the specified delimiters
		 * \param string String to be split
		 * \param delimiters Delimiter characters in the string
		 */
		static std::vector<std::string> split(std::string string, std::string delimiters) noexcept;

		/**
		 * \brief Joins the strings from a vector using the specified delimiter
		 * \param strings Vector of strings to be joined
		 * \param delimiter Delimiter to be joined
		 */
		static std::string join(std::vector<std::string> strings, std::string delimiter) noexcept;

		/**
		 * \brief Converts the number to its string representation
		 * \tparam Num Type of the number
		 * \param number Number to be converted
		 * \return String representation of the number
		 */
		template <typename Num>
		static std::string numberFormat(Num number) noexcept;

		/**
		 * \brief Converts the number to its hex string representation
		 * \tparam Num Type of the number
		 * \param number Number to be converted
		 * \return Hex string representation of the number
		 */
		template <typename Num>
		static std::string toHexString(Num number) noexcept;

		/**
		* \brief Converts the number to its hex string representation
		* \tparam Num Type of the number
		* \param number Number to be converted
		* \return Hex string representation of the number
		*/
		static std::string toHexString(unsigned char number) noexcept;

		/**
		* \brief Converts the number to its hex string representation
		* \tparam Num Type of the number
		* \param number Number to be converted
		* \return Hex string representation of the number
		*/
		static std::string toHexString(signed char number) noexcept;

		/**
		 * \brief Parses the number from its string representation
		 * \tparam Num Type of the number
		 * \param number String representation of the number to be parsed
		 * \return Parsed number
		 */
		template <typename Num>
		static Num parseNumber(std::string number);

		/**
		 * \brief Checks if the string contains only whitespace characters
		 * \param string String to be checked
		 * \return Boolean value indicating whether the string contains only whitespace characters
		 */
		static bool isAllWhiteSpace(const std::string &string) noexcept;

	private:
		StringHelper() = delete;
		StringHelper(StringHelper &) = delete;
		void operator=(StringHelper &) = delete;
	};

	template <typename Num>
	std::string StringHelper::numberFormat(Num number) noexcept {
		return std::to_string(number);
	}

	template <typename Num>
	std::string StringHelper::toHexString(Num number) noexcept {
		std::stringstream stream;
		stream << "0x"
			<< std::setfill('0') << std::setw(sizeof(Num) * 2)
			<< std::hex << number;
		return stream.str();
	}

	template<typename Num>
	Num StringHelper::parseNumber(std::string number) {
		long long long_long;

		try {
			if (regex_match(number, ZERO_REGEX)) {
				long_long = 0;
			}
			else if (regex_match(number, DECIMAL_REGEX)) {
				long_long = stoll(number);
			}
			else if (regex_match(number, HEX_REGEX)) {
				long_long = stoll(number.substr(2), nullptr, 16);
			}
			else if (regex_match(number, OCT_REGEX)) {
				long_long = stoll(number, nullptr, 8);
			}
			else if (regex_match(number, BINARY_REGEX)) {
				long_long = stoll(number.substr(2), nullptr, 2);
			}
			else if (regex_match(number, CHARACTER_REGEX)) {
				long_long = static_cast<long long>(number[1]);
			}
			else {
				throw MessageException("The number " + number + " could not be parsed");
			}
		}
		catch (std::invalid_argument&) {
			throw MessageException("The number " + number + " could not be parsed");
		}
		catch (std::out_of_range&) {
			throw MessageException("The number " + number + " is out of range");
		}

		auto ret = static_cast<Num>(long_long);

		if (ret != long_long) {
			throw MessageException("The number + " + number + " is out of range");
		}

		return ret;
	}
}

#endif
