#include <vector>
#include <stdexcept>
#include <random>
#pragma once

using namespace std;

class Matrix{ 
	unsigned int rows, columns;
	vector<vector<double> > values;

public: 
	Matrix(){

	}

	Matrix(int rows, int columns){
		values = vector<vector<double> >(rows, vector<double>(columns, 0));
		this->rows=rows;
		this->columns=columns;
	}

	Matrix(vector<double> v){
		auto a = vector<vector<double> > (v.size(), vector<double>(1, 0));
		values = a;
		rows = v.size();
		for (int i=0; i<rows; i++) values[i][0] = v[i];
		columns = 1;
	}

	Matrix(vector<vector<double> > v){
		values = v;
		rows = v.size();
		columns = v[0].size();
	}

	unsigned int nRows(){
		return rows;
	}

	unsigned int nColumns(){
		return columns;
	}

	double get(int row, int column){
		if ((row<0)||(column<0)||(row>=rows)||(column>=columns)) throw out_of_range("position not in matrix");
		return values[row][column];
	}

	void set(unsigned int row, unsigned int column, double value){
		if ((row>=rows)||(column>=columns)) throw out_of_range("position not in matrix");
		values[row][column] = value;
	}

	void add(Matrix m){
		if ((m.rows!=rows)||(m.columns!=columns)) throw out_of_range("Matrices need to be of the same size in order to be able to be added");
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<columns; j++){
				values[i][j] += m.values[i][j];
			}
		}
	}

	void operator += (double d) {
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<columns; j++){
				values[i][j] += d;
			}
		}
	}

	Matrix operator ^ () {
		
	}

	void add(double d){
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<columns; j++){
				values[i][j] += d;
			}
		}
	}

	void multiply(double d){
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<columns; j++){
				values[i][j] *= d;
			}
		}
	}

	void multiply(Matrix m){
		if (columns!=m.rows) {
			cerr << rows << "," << columns << " vs "<< m.rows << ", " << m.columns;
			throw out_of_range("Can't multiply these sizes of matrices");
		}
		auto v = vector<vector<double> >(rows, vector<double>(m.columns, 0));
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<m.columns; j++){
				for (unsigned int k=0; k<columns; k++){
					v[i][j] += values[i][k]*m.values[k][j];
				}
			}
		}
		values = v;
		columns = m.columns;
	}

	void multiplyByElement(Matrix m){
		if ((m.rows!=rows)||(m.columns!=columns)){
			cerr << rows << "," << columns << " vs "<< m.rows << ", " << m.columns;
			throw out_of_range("Must be of same size, multiplyByElement");
		} 
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				values[i][j] *= m.values[i][j];
			}
		}
	}

	void transpose(){
		auto v = vector<vector<double> >(columns, vector<double>(rows, 0));
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<columns; j++){
				v[j][i] = values[i][j];
			}
		}
		values = v;
		rows = columns;
		columns = v[0].size();
	}

	Matrix copy(){
		return Matrix(values);
	}

 
	static Matrix randomMatrix(unsigned int rows, unsigned int columns, double mean, double standardDeviation){
		random_device rd;
    	mt19937 e2(rd());
    	normal_distribution<> dist(mean, standardDeviation);

    	auto v = vector<vector<double> >(rows, vector<double>(columns, 0));
    	for (unsigned int i = 0; i<rows; i++){
    		for (unsigned int j = 0; j<columns; j++){
    			v[i][j] = dist(e2);
    		}
    	}
    	Matrix rMatrix(v);
    	return rMatrix;
	}

	static Matrix multiply(Matrix a, Matrix b){
		Matrix temp = a.copy(); 
		temp.multiply(b);
		return temp;
	}

	static Matrix minus(Matrix a, Matrix b){
		Matrix temp = b; 
		temp.multiply(-1);
		temp.add(a);
		return temp;
	}



};

