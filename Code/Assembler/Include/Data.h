#ifndef _data_h_
#define _data_h_
#include "DataType.h"
#include "MicroRiscExpression.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the MicroRISC data
	 */
	class Data {
	public:
		/**
		 * \brief Constructs a Data object
		 * \param type Type of the data
		 * \param value Value of the data
		 * \param count How many times the data will repeat
		 */
		Data(DataType type, MicroRiscExpression value, MicroRiscExpression count) noexcept;

		/**
		 * \brief Constructs an uninitialized Data object
		 * \param type Type of the data
		 * \param count How many times the data will repeat
		 */
		explicit Data(DataType type, MicroRiscExpression count) noexcept;
		
		/**
		 * \brief Get the type of the data
		 * \return Type of the data
		 */
		DataType type() const noexcept;

		/**
		 * \brief Check whether the data is initialized
		 * \return Whether the data is initialized
		 */
		bool initialized() const noexcept;

		/**
		 * \brief Get the value of the data
		 * \return value of the data
		 */
		MicroRiscExpression value() const noexcept;

		/**
		 * \brief Get how many times the data should repeat
		 * \return How many times should the data repeat
		 */
		MicroRiscExpression count() const noexcept;
	private:
		DataType type_;
		bool initialized_ = true;
		MicroRiscExpression value_;
		MicroRiscExpression count_;
	};
}

#endif
