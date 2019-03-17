#include <vector>
#include <fstream>
#pragma once

class MNIST{
public:
	vector<double> inputs_list, target_list;
	int result;

	MNIST(vector<double> inputs_list, int result){
		this -> inputs_list = inputs_list;
		this -> result = result;
		target_list = vector<double>(10, 0.01);
		target_list[result] = 0.99;
	}

	static vector<MNIST> readFile(string fileName){
		ifstream infile(fileName);
	}
};