/**
* @author {Steven Moffatt}
* @version {1.0.1}
* @date {2019/06/17}
*
*/

#include <exception>
#include <iostream>
#include <fstream>

#include "csv_reader.hpp"

//TODO: Use bit masks to distinguish exact type of failure.
std::vector<std::string> csv_reader::operator()(std::string const& file_in)
{
    std::ifstream input;
    input.exceptions(std::ifstream::badbit);
    std::vector<std::string> data;
    std::string item;

    try
    {
        input.open(file_in);
        if(not input.good())
        {
            throw std::invalid_argument("Problem reading file at location specified by path: ");
        }

        while(std::getline(input, item))
            data.push_back(item);
    }

    catch(std::invalid_argument const& ex)
    {
        std::cerr << ex.what() << file_in << "\n\n";
    }

    catch(std::ifstream::failure const& fail)
    {
        std::cerr << "Problem in I/O or hardware error. Terminating program.\n";
        input.close();
        std::terminate();
    }

    catch(...)
    {
        std::cout << "Unknown exception. Terminating program.\n";
        std::terminate();
    }


    input.close();
    return data;
}
