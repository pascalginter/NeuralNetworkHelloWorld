#include <iostream>
#include "matrix.cpp"
#include "neuralNetwork.cpp"
#include "neuralNetworkTrainer.cpp"
#include "MNIST.cpp"

using namespace std;

int main(){
	vector<MNIST> trainingData = MNIST::readFile("Data/mnist_train.csv");
	vector<MNIST> testData = MNIST::readFile("Data/mnist_test.csv");

	cout << "Size of trainign data: " << trainingData.size() << ", size of testData: " << testData.size() << "\n";

	cout << "finished reading \n";
	NeuralNetwork n = NeuralNetwork(784, 100, 10, 0.3);
	cout << "created untrained NeuralNetwork \n";
	NeuralNetworkTrainer::train(n, trainingData, 5);

	cout << "finished training \n";
	cout << NeuralNetworkTrainer::test(n, testData) << "\n";
	
	return 0;
}