#include<vector>
#include <math.h>
#include "matrix.cpp"
#pragma once

class NeuralNetwork{
	int input_nodes, hidden_nodes, output_nodes;
	Matrix wih, who;
	double learningRate;

	double sigmoid(double input){
		return 1/(1+powf(M_E, -input));
	}

public:
	NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes, double learningRate){
		this->input_nodes = input_nodes;
		this->hidden_nodes = hidden_nodes;
		this->output_nodes = output_nodes;
		this->learningRate = learningRate;

		wih = Matrix::randomMatrix(hidden_nodes, input_nodes, 0.0, sqrt(hidden_nodes));
		who = Matrix::randomMatrix(output_nodes, hidden_nodes, 0.0, sqrt(output_nodes));
	}

	void train(vector<double> inputs_list, vector<double> targets_list){
		//convert inputs list to matrix
		Matrix inputs = Matrix(inputs_list);
		Matrix targets = Matrix(targets_list);

		//calculate signals into hidden layer
		Matrix hidden_inputs = Matrix::multiply(wih, inputs);

		//calculate the signals emerging from hidden layer
		Matrix hidden_outputs = Matrix(hidden_inputs.nRows(), hidden_inputs.nColumns());

		for (u_int i=0; i<hidden_outputs.nRows(); i++){
			for (u_int j=0; j<hidden_outputs.nColumns(); j++){
				hidden_outputs.set(i, j, sigmoid(hidden_inputs.get(i, j)));
			}
		}

		//calculate signals into final output layer
		Matrix final_inputs = Matrix::multiply(who, hidden_outputs);

		//calculate the signals emerging from final output layer
		Matrix final_outputs = Matrix(final_inputs.nRows(), final_inputs.nColumns());
		for (u_int i=0; i<final_outputs.nRows(); i++){
			for (u_int j=0; j<final_outputs.nColumns(); j++){
				final_outputs.set(i, j, sigmoid(final_inputs.get(i, j)));
			}
		}

		//output layer error is the (target-actual)
		Matrix output_errors = Matrix::minus(targets, final_outputs);
		//hidden layer errors is the output_errors, split by weights, recombined at hidden nodes
		who.transpose();
		Matrix hidden_errors = Matrix::multiply(who, output_errors);
		who.transpose();

		//update the weights for the links between the hidden and output layers
		output_errors.multiplyByElement(final_outputs);
		final_outputs += (-1);
		final_outputs.multiply(-1);
		output_errors.multiplyByElement(final_outputs);
		hidden_outputs.transpose();
		output_errors.multiply(hidden_outputs);
		hidden_outputs.transpose();
		output_errors.multiply(learningRate);
		who.add(output_errors);

		//update the weights for the links between the input and hidden layers
		hidden_errors.multiplyByElement(hidden_outputs);
		final_outputs.add(-1);
		final_outputs.multiply(-1);
		hidden_errors.multiplyByElement(hidden_outputs);
		inputs.transpose();
		hidden_errors.multiply(inputs);
		hidden_errors.multiply(learningRate);
		wih.add(hidden_errors);

	}

	Matrix query(vector<double> inputs_list){
		//convert to matrix
		Matrix inputs = Matrix(inputs_list);

		//calculate signals into hidden layer
		Matrix hidden_inputs = Matrix::multiply(wih, inputs);
		//calculate the signals emerging from hidden layer
		Matrix hidden_outputs = hidden_inputs;
		for (u_int i=0; i<hidden_outputs.nRows(); i++){
			for (u_int j=0; j<hidden_outputs.nColumns(); j++){
				hidden_outputs.set(i, j, sigmoid(hidden_outputs.get(i, j)));
			}
		}

		//calculate signals into final output layer
		Matrix final_inputs = Matrix::multiply(who, hidden_outputs);
		//calculate the signals emerging from final output layer
		Matrix final_outputs = final_inputs;
		for (u_int i=0; i<final_outputs.nRows(); i++){
			for (u_int j=0; j<final_outputs.nColumns(); j++){
				final_outputs.set(i, j, sigmoid(final_outputs.get(i, j)));
			}
		}

		return final_outputs;
	}



};