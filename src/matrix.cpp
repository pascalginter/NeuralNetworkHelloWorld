#include <vector>
#include <stdexcept>

using namespace std;

class Matrix{ 
	unsigned int rows, columns;
	vector<vector<double> > values;

public: 
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

	double get(unsigned int row, unsigned int column){
		if ((row>=rows)||(column>=columns)) throw out_of_range("position not in matrix");
		return values[row][column];
	}

	void add(Matrix m){
		if ((m.rows!=rows)||(m.columns!=columns)) throw out_of_range("Matrices need to be of the same size in order to be able to be added");
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<columns; j++){
				values[i][j] += m.values[i][j];
			}
		}
	}

	void multiply(double d){
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<rows; j++){
				values[i][j] *= d;
			}
		}
	}

	void multiply(Matrix m){
		if (columns!=m.rows) throw out_of_range("Can't multiply these sizes of matrices");
		auto v = vector<vector<double> >(rows, vector<double>(m.columns, 0));
		for (unsigned int i=0; i<rows; i++){
			for (unsigned int j=0; j<rows; j++){
				for (unsigned int k=0; k<columns; k++){
					v[i][j] += values[i][k]*m.values[k][j];
				}
			}
		}
		values = v;
		columns = m.columns;
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
		columns = v.size();
	}

};


this_is_a_intentional_compile_error