/**
* @class csv_reader
* @author {Steven Moffatt}
* @version {1.0.1}
* @date {2019/06/17}
*
* \brief A function object class to read in CSV files.
*/

#ifndef CSV_READER_HPP
#define CSV_READER_HPP

#include <string>
#include <vector>

class csv_reader
{
public:
    /**
    * Overloaded function call operator to read a file and separate the test cases by newline.
    *
    * @param file_in {A string representing a path and file name.}
    * @return {A vector of test cases, with the data represented as strings.}
    */
    std::vector<std::string> operator()(std::string const& file_in);
};

#endif // CSV_READER_HPP
