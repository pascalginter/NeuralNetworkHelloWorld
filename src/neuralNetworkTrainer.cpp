#include <vector>
#include <chrono> 
#include "neuralNetwork.cpp"
#include "MNIST.cpp"
#pragma once

class NeuralNetworkTrainer{
	static int chosenPos(const vector<double> &result){
		int maxPos = -1, size = result.size();
		double maxValue = -1.0;
		for (int i = 0; i < size; i++){
			if (maxValue < result[i]){
				maxValue = result[i];
				maxPos = i;
			}
		}
		return maxPos;
	}

public: 
	static void train(NeuralNetwork &n, const vector<MNIST> &dataset, int epochs){
		auto start = chrono::system_clock::now();
		int size = dataset.size();
		cout << "started training \n";
		for (int i = 0; i < epochs; i++){
			cout << "training " << i << "\n";
			for (int j = 0; j < size; j++){
				n.train(dataset[j].inputs_list, dataset[j].target_list);
			}
		}
		auto end = chrono::system_clock::now();
		auto elapsed = end - start;
		cout << "Time passed: " << elapsed.count()/1000000000 << "seconds." << '\n';
	}

	static double test(NeuralNetwork &n, const vector<MNIST> &dataset){
		cout << "starting queries \n";
		double total = dataset.size(), score = 0.0;
		for (int i = 0; i < total; i++){
			if (chosenPos(n.query(dataset[i].inputs_list).toVector())==dataset[i].result) score += 1.0;
		}
		return score/total;
	}
};