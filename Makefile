
CXX = g++
CXXFLAGS = -O2 -std=c++14

INCDIR := include
SRCDIR := src
OBJDIR := obj
OBJSRC := $(OBJDIR)/src

#Edit this variable with the path of your Eigen implementation.
EIGEN = "C:/Program Files/cpp_libs/eigen_3_3_7"

INCLUDES = -I ./$(INCDIR) -I $(EIGEN)

neuralNet: $(OBJDIR)/main.o $(OBJSRC)/neural_net.o $(OBJSRC)/csv_reader.o $(OBJSRC)/split.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o neuralNet $(OBJDIR)/main.o $(OBJSRC)/neural_net.o $(OBJSRC)/csv_reader.o $(OBJSRC)/split.o

$(OBJDIR)/main.o: main.cpp $(INCDIR)/neural_net.hpp $(INCDIR)/csv_reader.hpp $(INCDIR)/split.hpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o $(OBJDIR)/main.o

$(OBJSRC)/neural_net.o: $(INCDIR)/neural_net.hpp | $(OBJSRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c ./$(SRCDIR)/neural_net.cpp -o $(OBJSRC)/neural_net.o

$(OBJSRC)/csv_reader.o: $(INCDIR)/csv_reader.hpp | $(OBJSRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c ./$(SRCDIR)/csv_reader.cpp -o $(OBJSRC)/csv_reader.o

$(OBJSRC)/split.o: $(INCDIR)/split.hpp | $(OBJSRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c ./$(SRCDIR)/split.cpp -o $(OBJSRC)/split.o

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJSRC):
	mkdir -p $(OBJSRC)
