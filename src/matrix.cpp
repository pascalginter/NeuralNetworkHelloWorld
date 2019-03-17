#include <vector>
#include <stdexcept>
#include <random>
#pragma once

using namespace std;

class Matrix{ 
	int rows, columns;
	vector<vector<double> > values;

public: 

	Matrix(){}

	Matrix(int rows, int columns){
		values = vector<vector<double> >(rows, vector<double>(columns, 0));
		this -> rows = rows;
		this -> columns = columns;
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

	int nRows(){
		return rows;
	}

	int nColumns(){
		return columns;
	}

	double get(int row, int column){
		if ((row<0)||(column<0)||(row>=rows)||(column>=columns)) throw out_of_range("position not in matrix");
		return values[row][column];
	}

	void set(int row, int column, double value){
		if ((row<0)||(column<0)||(row>=rows)||(column>=columns)) throw out_of_range("position not in matrix");
		values[row][column] = value;
	}

	void operator += (Matrix m){
		if ((m.rows!=rows)||(m.columns!=columns)) throw out_of_range("Matrices need to be of the same size in order to be able to be added");
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				values[i][j] += m.values[i][j];
			}
		}
	}

	Matrix operator + (Matrix m){
		if ((m.rows!=rows)||(m.columns!=columns)) throw out_of_range("Matrices need to be of the same size in order to be able to be added");
		Matrix result = Matrix(m.rows, m.columns);
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				result.values[i][j] = values[i][j] + m.values[i][j];
			}
		}
		return result;
	}

	Matrix operator + (double d){
		Matrix result = Matrix(values);
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<columns; j++){
				result.values[i][j] += d;
			}
		}
		return result;
	}

	void operator += (double d) {
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				values[i][j] += d;
			}
		}
	}

	Matrix operator - (Matrix m){
		if ((m.rows!=rows)||(m.columns!=columns)) throw out_of_range("Matrices need to be of the same size in order to be subtracted");
		Matrix result = Matrix(m.rows, m.columns);
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				result.values[i][j] = values[i][j] - m.values[i][j];
			}
		}
		return result;
	}

	Matrix operator - (double d){
		Matrix result = Matrix(values);
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<columns; j++){
				result.values[i][j] -= d;
			}
		}
		return result;
	}

	void operator *= (double d){
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				values[i][j] *= d;
			}
		}
	}

	Matrix operator * (double d){
		Matrix result = Matrix(values);
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				result.values[i][j] *= d;
			}
		}
		return result;
	}

	void operator *= (Matrix m){
		if (columns!=m.rows) {
			cerr << rows << "," << columns << " vs "<< m.rows << ", " << m.columns;
			throw out_of_range("Can't multiply these sizes of matrices");
		}
		auto v = vector<vector<double> >(rows, vector<double>(m.columns, 0));
		for (int i=0; i<rows; i++){
			for (int j=0; j<m.columns; j++){
				for (int k=0; k<columns; k++){
					v[i][j] += values[i][k]*m.values[k][j];
				}
			}
		}
		values = v;
		columns = m.columns;
	}

	Matrix operator * (Matrix m){
		if (columns!=m.rows) {
			cerr << rows << "," << columns << " vs "<< m.rows << ", " << m.columns;
			throw out_of_range("Can't multiply these sizes of matrices");
		}
		auto v = vector<vector<double> >(rows, vector<double>(m.columns, 0));
		for (int i=0; i<rows; i++){
			for (int j=0; j<m.columns; j++){
				for (int k=0; k<columns; k++){
					v[i][j] += values[i][k]*m.values[k][j];
				}
			}
		}
		return Matrix(v);
	}

	//Multiplication by element
	void operator ^= (Matrix m){
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

	Matrix operator ^ (Matrix m){
		if ((m.rows!=rows)||(m.columns!=columns)){
			cerr << rows << "," << columns << " vs "<< m.rows << ", " << m.columns;
			throw out_of_range("Must be of same size, multiplyByElement");
		} 
		Matrix result = Matrix(values);
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				result.values[i][j] *= m.values[i][j];
			}
		}
		return result;
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

	static Matrix transpose(Matrix m){
		Matrix result = Matrix(m.columns, m.rows);
		for (int i=0; i<m.rows; i++){
			for (int j=0; j<m.columns; j++){
				result.values[j][i] = m.values[i][j];
			}
		}
		return result;
	}

	Matrix copy(){
		return Matrix(values);
	}

 
	static Matrix randomMatrix(int rows, int columns){
    	auto v = vector<vector<double> >(rows, vector<double>(columns, 0));
    	for (int i = 0; i<rows; i++){
    		for (int j = 0; j<columns; j++){
    			v[i][j] = double(rand()) / (double(RAND_MAX) + 1.0);
    		}
    	}
    	Matrix rMatrix(v);
    	return rMatrix;
	}

	string toString(){
		string s = "";
		for (int i=0; i<rows; i++){
			for (int j=0; j<columns; j++){
				s += to_string(round(values[i][j]*100.0)/100.0) + " ";
			}
			s += "\n";
		}
		return s;
	}

};