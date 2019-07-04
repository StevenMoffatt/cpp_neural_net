# A Basic Neural Network.

A neural network class with a single hidden layer, used in a simple handwriting recognition problem. The program trains a network to recognise single numerical digits (0 - 9), and tests the success rate with a separate test data set.

## Quickstart Guide

N.B. This method was tested on a Windows 10 machine running MinGW  8.2.0., and on Mac OSX (El Capitan) with GCC 4.2.1. You can alternatively use a C++ IDE to build the project.

1. Make sure you have a C++ compiler installed on your computer.
2. Download [*Eigen*](http://eigen.tuxfamily.org/index.php?title=Main_Page) linear algebra library.
3. Modify the variable `EIGEN` in [Makefile](./Makefile) and give the path of your Eigen library.
4. (OPTIONAL) Download the full set of training data and test data, to better train the network, and place each in the folder *mnist_data*. You must then update the variables `training_file` and `test_file` in *main.cpp*.  
4. Open command line in the project directory, and run your compiler's `make` command to run the Makefile (N.B. Actual command is compiler specific.)
5. Upon successful compilation, run the executable file by typing `neuralNet` in the command line.

## Inspiration for the project.

The code is a C++ implementation of the application created in Python by **Tariq Rashid** in **_"Make Your Own Neural Network."_ (2016), CreateSpace Independent Publishing Platform, ISBN: 978-1530826605**.

## Datasets Used for Network Testing and Training.

The application uses the [MNIST database of handwritten digits](http://yann.lecun.com/exdb/mnist/), and the shortened files are **already included in the application package**. These files were downloaded from Tariq Rashid's [Github for his book](https://github.com/makeyourownneuralnetwork/makeyourownneuralnetwork/tree/master/mnist_dataset). The full set is not included due to upload file restrictions. With the shortened training set, the network can only achieve less that 50% accuracy, whereas it can reach around 95% with the full training set. You can download the full training and test sets in the required csv format from site pjreddie.com: [training set](https://pjreddie.com/media/files/mnist_train.csv); [test set](https://pjreddie.com/media/files/mnist_test.csv).

## Dependencies and Compilation Advice.

### Eigen 3.3.7
The class `neural_net` uses the linear algebra library [*Eigen*](http://eigen.tuxfamily.org/index.php?title=Main_Page). The version used in compilation was *Eigen 3.3.7*. A version of *Eigen* must be installed on your machine, and your compiler must link to the location of the library to use this application. See your compiler or IDE documentation for specific information on how to achieve this.

### Compilation for Runtime Efficiency
Make sure that your compiler is set to **optimise** for runtime efficiency, or *Eigen* may become inefficient when dealing with large training sets. For example, if you are using a GNU gcc compiler, set the optimisation flag `-o2` in the command line, or in your IDE's compiler settings. Without this flag, the application took around 15 minutes to run a single epoch, and about 1.5 minutes with it included on a modern laptop Windows PC.

## Author of C++ implementation

- **Steven Moffatt** - Contact: <steven.moffatt@btinternet.com>.
