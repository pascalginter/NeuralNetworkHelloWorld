#include <vector>
#include "neuralNetwork.cpp"
#pragma once

class NeuralNetworkTrainer{
	int chosenPos(vector<double> result){
		int maxPos = -1;
		double maxValue = -1.0;
		for (int i = 0; i < result.size; i++){
			if (maxValue < result[i]){
				maxValue = result[i];
				maxPos = i;
			}
		}
		return maxPos;
	}

public: 
	static void train(NeuralNetwork n, vector<MNIST> dataset, int epochs){
		for (int i = 0; i < epochs; i++){
			for (int j = 0; j < dataset.size(); j++){
				n.train(dataset[j].input, dataset[j].target);
			}
		}
	}

	static double test(NeuralNetwork n, vector<MNIST> dataset){
		double total = dataset.size(), score = 0.0;
		for (int i = 0; i<dataset.size(); i++){
			if (chosenPos(n.query(dataset[i].input))==dataset[i].result) score += 1.0;
		}
		return score;
	}
};