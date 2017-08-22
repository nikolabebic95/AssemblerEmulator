#ifndef _register_h_
#define _register_h_
#include <cstdint>

namespace bnssemulator {
	
	/**
	 * \brief Class representing the register
	 */
	class Register {
	public:
		/**
		 * \brief Constructs a Register object
		 */
		Register() = default;

		/**
		 * \brief Gets the value of the register
		 * \return Value of the register
		 */
		int32_t value() const noexcept;

		/**
		 * \brief Sets the value of the register
		 * \param value Value of the register
		 */
		void value(int32_t value) noexcept;

		/**
		 * \brief Gets the negative flag of the register
		 * \return Negative flag
		 */
		bool negativeFlag() const noexcept;

		/**
		* \brief Gets the zero flag of the register
		* \return Zero flag
		*/
		bool zeroFlag() const noexcept;

		/**
		* \brief Gets the Carry flag of the register
		* \return Carry flag
		*/
		bool carryFlag() const noexcept;

		/**
		* \brief Gets the overflow flag of the register
		* \return Overflow flag
		*/
		bool overflowFlag() const noexcept;

		// ReSharper disable once CppNonExplicitConvertingConstructor
		/**
		 * \brief Constructs a Register object
		 * \param value Starting value of the register
		 */
		Register(int32_t value) noexcept;

		/**
		 * \brief Constructs a Register object
		 * \param value Starting value of the register
		 * \param carry_flag Starting carry flag of the register
		 * \param overflow_flag Starting overflow flag of the register
		 */
		Register(int32_t value, bool carry_flag, bool overflow_flag) noexcept;

		// Overloaded operators:

		// ReSharper disable once CppNonExplicitConversionOperator
		operator int32_t() const noexcept;

		Register operator-() const noexcept;
		Register operator~() const noexcept;

		Register &operator+=(const Register &reg) noexcept;
		Register &operator-=(const Register &reg) noexcept;
		Register &operator*=(const Register &reg) noexcept;
		Register &operator/=(const Register &reg) noexcept;
		Register &operator%=(const Register &reg) noexcept;

		Register &operator&=(const Register &reg) noexcept;
		Register &operator|=(const Register &reg) noexcept;
		Register &operator^=(const Register &reg) noexcept;

		Register &operator<<=(const Register &reg) noexcept;
		Register &operator>>=(const Register &reg) noexcept;

		friend Register operator+(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator-(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator*(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator/(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator%(const Register &lhs, const Register &rhs) noexcept;

		friend Register operator&(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator|(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator^(const Register &lhs, const Register &rhs) noexcept;		

		friend Register operator<<(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator>>(const Register &lhs, const Register &rhs) noexcept;
	private:
		int32_t value_ = 0;

		bool carry_flag_ = false;
		bool overflow_flag_ = false;
	};
}

#endif
