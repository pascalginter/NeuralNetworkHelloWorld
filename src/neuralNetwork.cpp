#include<vector>
#include <math.h>
#include "matrix.cpp"
#pragma once

class NeuralNetwork{
	int input_nodes, hidden_nodes, output_nodes;
	double learningRate;

	static double sigmoid(double input){
		return (1.0/(1.0+powf(M_E, -input)))*0.98+0.01;
	}

public:
	Matrix wih, who;

	NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes, double learningRate){
		this->input_nodes = input_nodes;
		this->hidden_nodes = hidden_nodes;
		this->output_nodes = output_nodes;
		this->learningRate = learningRate;

		wih = Matrix::randomMatrix(hidden_nodes, input_nodes);
		who = Matrix::randomMatrix(output_nodes, hidden_nodes);
	}

	void train(vector<double> inputs_list, vector<double> targets_list){
		//convert inputs list to matrix
		Matrix inputs = Matrix(inputs_list);
		Matrix targets = Matrix(targets_list);
		//calculate signals into hidden layer
		Matrix hidden_inputs = wih * inputs;

		//calculate the signals emerging from hidden layer
		Matrix hidden_outputs = Matrix(hidden_inputs.nRows(), hidden_inputs.nColumns());

		for (int i=0; i<hidden_outputs.nRows(); i++){
			for (int j=0; j<hidden_outputs.nColumns(); j++){
				hidden_outputs.set(i, j, sigmoid(hidden_inputs.get(i, j)));
			}
		}

		//calculate signals into final output layer
		Matrix final_inputs = who * hidden_outputs;

		//calculate the signals emerging from final output layer
		Matrix final_outputs = Matrix(final_inputs.nRows(), final_inputs.nColumns());
		for (int i=0; i<final_outputs.nRows(); i++){
			for (int j=0; j<final_outputs.nColumns(); j++){
				final_outputs.set(i, j, sigmoid(final_inputs.get(i, j)));
			}
		}

		//output layer error is the (target-actual)
		Matrix output_errors = targets - final_outputs;
		//hidden layer errors is the output_errors, split by weights, recombined at hidden nodes
		Matrix hidden_errors = Matrix::transpose(who) * output_errors;

		//update the weights for the links between the hidden and output layers
		who += ((output_errors ^ final_outputs ^ ((final_outputs - 1.0) * -1.0)) * Matrix::transpose(hidden_outputs)) * learningRate;

		//update the weights for the links between the input and hidden layers
		wih += ((hidden_errors ^ hidden_outputs ^ ((hidden_outputs - 1.0)* -1.0)) * Matrix::transpose(inputs)) * learningRate;
	}

	Matrix query(vector<double> inputs_list){
		//convert to matrix
		Matrix inputs = Matrix(inputs_list);

		//calculate signals into hidden layer
		Matrix hidden_inputs = wih * inputs;
		//calculate the signals emerging from hidden layer
		Matrix hidden_outputs = Matrix(hidden_inputs.nRows(), hidden_inputs.nColumns());
		for (int i=0; i<hidden_outputs.nRows(); i++){
			for (int j=0; j<hidden_outputs.nColumns(); j++){
				hidden_outputs.set(i, j, sigmoid(hidden_inputs.get(i, j)));
			}
		}

		//calculate signals into final output layer
		Matrix final_inputs = who * hidden_outputs;
		//calculate the signals emerging from final output layer
		Matrix final_outputs = Matrix(final_inputs.nRows(), final_inputs.nColumns());
		for (int i=0; i<final_outputs.nRows(); i++){
			for (int j=0; j<final_outputs.nColumns(); j++){
				final_outputs.set(i, j, sigmoid(final_inputs.get(i, j)));
			}
		}

		return final_outputs;
	}

	void printQuery(vector<double> inputs_list){
		//convert to matrix
		Matrix inputs = Matrix(inputs_list);
		cout << "input Nodes: \n" << inputs.toString() << "\n";

		//calculate signals into hidden layer
		Matrix hidden_inputs = wih * inputs;
		//calculate the signals emerging from hidden layer
		Matrix hidden_outputs = Matrix(hidden_inputs.nRows(), hidden_inputs.nColumns());
		for (int i=0; i<hidden_outputs.nRows(); i++){
			for (int j=0; j<hidden_outputs.nColumns(); j++){
				hidden_outputs.set(i, j, sigmoid(hidden_inputs.get(i, j)));
			}
		}

		cout << "hidden Nodes: \n" << hidden_outputs.toString() << "\n";

		//calculate signals into final output layer
		Matrix final_inputs = who * hidden_outputs;
		//calculate the signals emerging from final output layer
		Matrix final_outputs = Matrix(final_inputs.nRows(), final_inputs.nColumns());
		for (int i=0; i<final_outputs.nRows(); i++){
			for (int j=0; j<final_outputs.nColumns(); j++){
				final_outputs.set(i, j, sigmoid(final_inputs.get(i, j)));
			}
		}

		cout << "output Nodes: \n" << final_outputs.toString() << "\n";
		cout << "_________________________________ \n";

	}

};
