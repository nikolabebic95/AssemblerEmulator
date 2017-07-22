#ifndef _file_reader_h_
#define _file_reader_h_
#include <vector>
#include <string>

namespace bnss {
	
	/**
	 * \brief Utility class providing methods for reading the file
	 */
	class FileReader final {
	public:
		/**
		 * \brief Reads all lines of the file
		 * \param filename Name of the file
		 * \return All lines of the file
		 * \throw Throws if the file does not exist or could not be opened for reading
		 */
		static std::vector<std::string> readAllLines(std::string filename);

	private:
		FileReader() = delete;
		FileReader(FileReader &) = delete;
		void operator=(FileReader &) = delete;
	};
}

#endif
