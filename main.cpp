#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#include "neural_net.hpp"
#include "csv_reader.hpp"
#include "split.hpp"

int main()
{
    typedef std::vector<std::string>::const_iterator data_iterator;

    std::string training_file {"mnist_data/mnist_train_100.csv"};
    std::string test_file {"mnist_data/mnist_test_10.csv"};

    /// Initialise network with number of nodes and learning rate.
    neural_net::value_type const inputNodes {784};
    neural_net::value_type const hiddenNodes {200};
    neural_net::value_type const outputNodes {10};
    double learningRate {0.1};

    neural_net net(inputNodes, hiddenNodes, outputNodes, learningRate);

    /// Initialise function objects for file parsing and data handling.
    csv_reader parser;
    split splitter;

/******************************* Train the Network ******************************************************/
    std::cout << "Training the network... \n";
    /// Read in training data.
    std::vector<std::string> const str_training_data {parser(training_file))};

    /// Range of possible values for each feature, used for scaling.
    /// Each feature expected to be between zero and 255 inclusive (pixel values).
    double const value_range {255.0};

    /// epochs specifies how many times training repeated over whole dataset
    std::size_t const epochs {4};
    for(std::size_t epoch{0}; epoch < epochs; ++epoch)
    {
        for(data_iterator iter{str_training_data.begin()}; iter < str_training_data.end(); ++iter)
        {
            /// Extract values as numbers, and ignore the first item, representing the character
            /// the data represents.
            std::vector<double> pixel_values {splitter(*iter, ',')};
            std::vector<double> unscaled_input {pixel_values.begin()+1, pixel_values.end()};

            /// Vector of targets to inform learning.
            std::vector<double> targets(outputNodes, 0.01);
            targets.at(pixel_values.at(0)) = 0.99;

            net.train(unscaled_input, targets, value_range);
        }
    }

/********************************* Test the Network **************************************************/

    std::cout << "Testing the network... \n";

    /// Read in the test data.
    std::vector<std::string> const str_test_data {parser(test_file)};

    std::vector<int> scorecard;

    for(data_iterator iter{str_test_data.begin()}; iter < str_test_data.end(); ++iter)
    {
        std::vector<double> pixel_values {splitter(*iter, ',')};
        std::vector<double> unscaled_input {pixel_values.begin()+1, pixel_values.end()};

        int correct_label { static_cast<int>(pixel_values[0]) };

        std::vector<double> outputs {net.query(unscaled_input, value_range)};

        int answer_label {static_cast<int>(std::distance( outputs.begin(), std::max_element(outputs.begin(), outputs.end()) ))};

        if(answer_label == correct_label)
        {
            scorecard.push_back(1);
        }
        else
        {
            scorecard.push_back(0);
        }
    }

    int sum {std::accumulate(scorecard.begin(), scorecard.end(), 0)};
    std::cout << "Network performance: " << static_cast<double>(sum) / scorecard.size() * 100 << "%" << '\n';

    return 0;
}
