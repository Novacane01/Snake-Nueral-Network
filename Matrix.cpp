#include "stdafx.h"
#include "Matrix.h"

Matrix::Matrix(int rows, int columns):matrix(rows,std::vector<double>(columns,0)) {
	this->rows = rows;
	this->columns = columns;
}

Matrix Matrix::add(Matrix *b) {
	if (rows == b->rows&&columns == b->columns) {
		Matrix temp(rows, columns);
		for (int i = 0;i < rows;i++) {
			for (int j = 0;j < columns;j++) {
				temp.matrix[i][j] = matrix[i][j] + b->matrix[i][j];
			}
		}
		return temp;
	}
	else {
		throw "Matrix dimensions must be equal";
	}
}

Matrix Matrix::add(int b) {
	Matrix temp(rows, columns);
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			temp.matrix[i][j] = matrix[i][j] + b;
		}
	}
	return temp;
}

Matrix Matrix::multiply(Matrix *b) {
	if (columns == b->rows) {
		Matrix temp(rows, b->columns);
		for (int i = 0;i < rows;i++) {
			for (int j = 0;j <columns;j++) {
				for (int k = 0;k < b->columns;k++) {
					temp.matrix[i][k] += matrix[i][j] * b->matrix[j][k];
				}
			}
		}
		return temp;
	}
	else {
		throw "column dimensions of Matrix a, must match row dimensions of Matrix b";
	}
}

Matrix Matrix::multiply(int b) {
	Matrix temp(rows, columns);
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			temp.matrix[i][j] = matrix[i][j] * b;
		}
	}
	return temp;
}

void Matrix::transpose() {
	Matrix temp(rows, columns);
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			temp.matrix[i][j] = matrix[rows-i-1][j];
		}
	}
	this->matrix = temp.matrix;
}

void Matrix::randomize() {
	for (unsigned i = 0;i < rows;i++) {
		for (unsigned j = 0;j < columns;j++) {
			matrix[i][j] = (float)rand() / RAND_MAX;;
		}
	}
}

Matrix Matrix::sigmoid() {
	Matrix newMatrix(rows, columns);
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			newMatrix.matrix[i][j] = exp(matrix[i][j]) / (1 + exp(matrix[i][j]));
		}
	}
	return newMatrix;
}

Matrix::~Matrix() {

}