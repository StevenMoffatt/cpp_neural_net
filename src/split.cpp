/**
* @author {Steven Moffatt}
* @version {1.0.1}
* @date {2019/06/17}
*
*/

#include <sstream>

#include "split.hpp"

//TODO: exception handling.
std::vector<double> split::operator()(std::string const& str, char const delim)
{
    std::istringstream input {str};
    std::vector<double> numvec;
    std::string tmp;

    while(std::getline(input, tmp, delim))
        numvec.push_back(std::stoi(tmp));

    return numvec;
}
