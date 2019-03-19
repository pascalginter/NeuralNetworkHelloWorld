#include <vector>
#include "neuralNetwork.cpp"
#include "MNIST.cpp"
#pragma once

class NeuralNetworkTrainer{
	static int chosenPos(vector<double> result){
		int maxPos = -1;
		double maxValue = -1.0;
		for (int i = 0; i < result.size(); i++){
			if (maxValue < result[i]){
				maxValue = result[i];
				maxPos = i;
			}
		}
		return maxPos;
	}

public: 
	static void train(NeuralNetwork &n, vector<MNIST> &dataset, int epochs){
		int size = dataset.size();
		cout << "started training \n";
		for (int i = 0; i < epochs; i++){
			cout << "training " << i << "\n";
			for (int j = 0; j < size; j++){
				n.train(dataset[j].inputs_list, dataset[j].target_list);
			}
		}
	}

	static double test(NeuralNetwork &n, vector<MNIST> &dataset){
		cout << "starting queries \n";
		double total = dataset.size(), score = 0.0;
		for (int i = 0; i<dataset.size(); i++){
			if (chosenPos(n.query(dataset[i].inputs_list).toVector())==dataset[i].result) score += 1.0;
		}
		return score/total;
	}
};