#include <vector>
#include <fstream>
#include <sstream>
#pragma once

class MNIST{
public:
	vector<double> inputs_list, target_list;
	int result;

	MNIST(vector<double> &inputs_list, int result){
		this -> inputs_list = inputs_list;
		this -> result = result;
		target_list = vector<double>(10, 0.01);
		target_list[result] = 0.99;
	}

	static vector<MNIST> readFile(string fileName){
		ifstream infile = ifstream(fileName);
		string line;
		vector<MNIST> result = vector<MNIST>();

		while (getline(infile, line)){
			stringstream ss(line);
			vector<int> lineNumbers = vector<int>(785, 0);
			vector<double> inputs_list;
			int i = 0;
    		while (ss >> lineNumbers[i++]){
        		if (ss.peek() == ',') ss.ignore();
        	}
        	for (int i = 1; i < lineNumbers.size(); i++) inputs_list.push_back(((double)lineNumbers[i]/255.0)*0.98+0.01);
        	result.push_back(MNIST(inputs_list, lineNumbers[0]));
   		}
   		return result;
	}
};