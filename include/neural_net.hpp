/**
* @class neural_net
* @author {Steven Moffatt}
* @version {1.0.1}
* @date {2019/06/17}
*
* \brief A neural network class with one hidden layer.
*
* Constructs a neural network with a single hidden layer with the
* number of nodes in each layer and learning rate specified by the
* user. Originally designed for use with numeric character
* handwriting recognition.
*
* The class is a C++ implementation of the Python-designed neural network
* created by Tariq Rashid in "Make Your Own Neural Network." (2016),
* CreateSpace Independent Publishing Platform,
* ISBN: 978-1530826605
*/

#ifndef NEURAL_NET_HPP
#define NEURAL_NET_HPP

#include <Eigen/Dense>
#include <vector>

class neural_net
{
public:
    typedef int value_type; /**< Typedef for number of nodes. */

    /**
    * Constructor for the class.
    *
    * @param i_nodes_in {Number of nodes in the input layer.}
    * @param h_nodes_in {Number of nodes in the hidden layer.}
    * @param o_nodes_in {Number of nodes in the output layer.}
    * @param l_rate_in {Value of the learning rate, alpha.}
    */
    neural_net(value_type i_nodes_in, value_type h_nodes_in, value_type o_nodes_in, double l_rate_in);

    /**
    * Query the network for a prediction.
    *
    * @param inputs_in {A vector of input features.}
    * @return {An Eigen library Vector, with the highest
    *          value representing the network's prediction.}
    */
    std::vector<double> query(std::vector<double>& inputs_in, double range_in);

    /**
    * Perform a single feed-forward and backprop pass, updating the network weights.
    *
    * @param inputs_in {A vector of input features.}
    * @param training_data_in {A vector of target values corresponding to the input argument
                               for a single piece of training data.}
    */
    void train(std::vector<double>& inputs_in, std::vector<double>& training_data_in, double range_in);

private:
    value_type iNodes_; /**< Input node number */
    value_type hNodes_; /**< Hidden node number */
    value_type oNodes_; /**< Output node number */
    double lRate_;      /**< Learning rate, alpha */

    Eigen::MatrixXd wih_; /**< Matrix of weights between the input and hidden layers. */
    Eigen::MatrixXd who_; /**< Matrix of weights between the hidden and output layers. */

    /**
    * Apply the activation function to the inputs to a node.
    *
    * @param vector_in {The unregulated inputs,
                        calculated from the weights * the previous layer output.}
    * @return {Eigen library Vector, representing the regulated layer output.}
    */
    Eigen::VectorXd activation_func(Eigen::VectorXd& vector_in);

    /**
    * Generates a matrix of random numbers to set as the initial weights.
    *
    * @param mean_in {The mean of the sample distribution.}
    * @param sd_in {The standard deviation of the sample distribution.}
    * @param rows_in {The number of rows of the resulting matrix.}
    * @param cols_in {The number of columns of the resulting matrix.}
    * @return {A matrix of random numbers.}
    */
    Eigen::MatrixXd rand_num_gen(double mean_in, double sd_in, std::size_t rows_in, std::size_t cols_in);

};


#endif // NEURAL_NET_HPP
