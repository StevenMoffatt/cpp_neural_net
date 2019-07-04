/**
* @class split
* @author {Steven Moffatt}
* @version {1.0.1}
* @date {2019/06/17}
*
* \brief A function object class to extract numbers from
* a string vector.
*/

#ifndef SPLIT_HPP
#define SPLIT_HPP

#include <string>
#include <vector>
class split
{
public:
    /**
    * Overloaded function call operator to extract each data point as doubles, split by
    * a char delimiter.
    *
    * @param str {A string representing a single test case to divide up.}
    * @param delim {A char to identify the boundary between data points.}
    * @return {A vector representing a single test case, with data as doubles.}
    */
    std::vector<double> operator()(std::string const& str, char const delim);
};

#endif // SPLIT_HPP
