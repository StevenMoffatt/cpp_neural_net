/**
* @author {Steven Moffatt}
* @version {1.0.1}
* @date {2019/06/17}
*
*/

#include <cmath>
#include <exception>
#include <iostream>
#include <random>

#include "neural_net.hpp"


neural_net::neural_net(value_type i_nodes_in, value_type h_nodes_in, value_type o_nodes_in, double l_rate_in)
    : iNodes_(i_nodes_in),
      hNodes_(h_nodes_in),
      oNodes_(o_nodes_in),
      lRate_(l_rate_in)
{
    wih_ = rand_num_gen(0.0, 1.0, hNodes_, iNodes_);
    who_ = rand_num_gen(0.0, 1.0, oNodes_, hNodes_);
}

/**
* Apply the sigmoid function to all elements in the vector.
* @note {Chosen to use int instead of size_t as Eigen::Index is an int by default.}
*/

Eigen::VectorXd neural_net::activation_func(Eigen::VectorXd& vector_in)
{
    for(int i{0}; i < vector_in.rows(); ++i)
    {
        double x{vector_in(i)};
        vector_in(i) = (1 / (1 + exp(-x)));
    }
    return vector_in;

}

/**
* Sample random numbers from a normal distribution.
* Uses the Mersenne Pseudo-random number generator (32-bit numbers).
*/
Eigen::MatrixXd neural_net::rand_num_gen(double mean_in, double sd_in, std::size_t rows_in, std::size_t cols_in)
{
    Eigen::MatrixXd result(rows_in, cols_in);
    try
    {
        std::random_device rd; /**< May not be supported: throws std::exception derived object.*/
        std::mt19937 generator{ rd() };
        std::normal_distribution<double> nd(mean_in, sd_in);

        for(std::size_t i{0}; i < rows_in; ++i)
        {
            for(std::size_t j{0}; j < cols_in; ++j)
            {
                result(i, j) = nd(generator);
            }
        }
    }
    catch(std::exception const& ex)
    {
        std::cerr << "Random number generation using the standard library failed.\n"
                  << "Implementing Eigen Random function...\n";
        try
        {
            result.setRandom(rows_in, cols_in);

        }
        catch(...)
        {
            std::cerr << "Eigen random number generation failed. Terminating program.\n";
            std::terminate();
        }
    }
    catch(...)
    {
        std::cout << "Unknown exception. Terminating program.\n";
        std::terminate();
    }


    return result;
}
/**
* @note {Could refactor to store each layer's output as data members of the neural_net class.
         This function can then be called by train(), eliminating duplicate code.
         However, this may not scale well to very large matrices. }
*/
std::vector<double> neural_net::query(std::vector<double>& inputs_in, double range_in)
{
    /// Create Eigen Vector from STL vector.
    Eigen::Map<Eigen::VectorXd> newvec(inputs_in.data(), inputs_in.size());

    /// Feature scaling to between 0.01 and one.
    /// Each feature expected to be between zero and 255 inclusive (pixel values).
    /// Offset of 0.01 to avoid zero.
    newvec = (newvec.array() / range_in * 0.99) + 0.01;

    /// Perform a feed-forward pass through the network.
    Eigen::VectorXd hidden_inputs {wih_ * newvec};
    Eigen::VectorXd hidden_outputs {activation_func(hidden_inputs)};
    Eigen::VectorXd final_inputs {who_ * hidden_outputs};
    Eigen::VectorXd final_outputs {activation_func(final_inputs)};

    std::vector<double> outputs(final_outputs.data(), final_outputs.data() + final_outputs.size());

    return outputs;
}

/**
* @note {Feature scaling expects each feature to be pixels, and therefore between 0 and 255.
         It also expects the activation function to produce values between 0 and 1.}
* @todo {Perhaps pass a value representing the range of each input feature to allow
         a more generalised network.}
*/
void neural_net::train(std::vector<double>& inputs_in, std::vector<double>& training_data_in, double range_in)
{
    /// Create Eigen Vectors from STL vectors.
    Eigen::Map<Eigen::VectorXd> input_vec(inputs_in.data(), inputs_in.size());
    Eigen::Map<Eigen::VectorXd> target_vec(training_data_in.data(), training_data_in.size());

    /// Feature scaling between zero and one.
    /// Offset of 0.01 to avoid zero and one values, unobtainable by a sigmoid function.
    input_vec = (input_vec.array() / range_in * 0.99) + 0.01;

    /// Perform a feed-forward pass through the network.
    Eigen::VectorXd hidden_inputs {wih_ * input_vec};
    Eigen::VectorXd hidden_outputs {activation_func(hidden_inputs)};
    Eigen::VectorXd final_inputs {who_ * hidden_outputs};
    Eigen::VectorXd final_outputs {activation_func(final_inputs)};

    /// Calculate error.
    Eigen::VectorXd output_errors {target_vec - final_outputs};
    Eigen::VectorXd hidden_errors {who_.transpose() * output_errors};

    /// Update weights using gradient descent.
    /// Use Eigen Arrays for element-wise multiplication;
    /// Convert to Eigen Matrices for dot-product multiplication.

    who_ += (lRate_ * output_errors.array() * final_outputs.array() * (1.0 - final_outputs.array()) ).matrix() * hidden_outputs.transpose();
    wih_ += (lRate_ * hidden_errors.array() * hidden_outputs.array() * (1.0 - hidden_outputs.array()) ).matrix() * input_vec.transpose();
}
