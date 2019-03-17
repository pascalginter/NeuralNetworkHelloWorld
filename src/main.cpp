#include <iostream>
#include "matrix.cpp"
#include "neuralNetwork.cpp"
#include "neuralNetworkTrainer.cpp"
#include "MNIST.cpp"

using namespace std;

int main(){
	vector<MNIST> trainingData = MNIST::readFile("data/mnist_train.csv");
	vector<MNIST> testData = MNIST::readFile("data/mnist_test.csv");

	cout << "finished reading \n";
	NeuralNetwork n = NeuralNetwork(784, 100, 10, 0.3);
	cout << "created untrained NeuralNetwork \n";
	NeuralNetworkTrainer::train(n, trainingData, 5);

	cout << "finished training \n";
	cout << NeuralNetworkTrainer::test(n, testData) << "\n";
	
	return 0;
}