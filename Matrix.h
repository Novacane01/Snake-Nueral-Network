#pragma once
#include <vector>
#include <cstdlib>

class Matrix {
public:
	Matrix(int, int);
	std::vector<std::vector<double>> matrix;
	Matrix add(Matrix*);
	Matrix add(int);
	Matrix multiply(Matrix*);
	Matrix multiply(int);
	Matrix sigmoid();
	void transpose();
	void randomize();
	~Matrix();
	int rows, columns;
};