#include "Matrices.h"

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
		rows = _rows;
		cols = _cols;

		//Resizing vector to n rows
		a.resize(rows);

		//Resizing each row to n columns
		for (int i = 0; i < a.size(); i++)
		{
			a.at(i).resize(cols, 0.0);
		}
	}

	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() && a.getCols() != b.getCols()) throw runtime_error("Error: dimensions must agree");

		Matrix c(a.getRows(), a.getCols());

		for (int i = 0; i < c.getRows(); i++)
		{
			for (int j = 0; j < c.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}
		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getRows()) throw runtime_error("Error: dimensions must agree");

		int rowsC = a.getRows();
		int colsC = b.getCols();

		Matrix c(rowsC, colsC);
		int n = a.getCols();

		for (int i = 0; i < rowsC; i++)
		{
			for (int j = 0; j < colsC; j++)
			{
				for (int k = 0; k < n; k++)
				{
					c(i, j) += a(i, k) * b(k, j);
				}
			}
		}
		return c;
	}

	bool operator==(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() && a.getCols() != b.getCols()) return false;

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j) > 0.001)) return false;
			}
		}
		return true;
	}

	bool operator!=(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) return true;

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j)) < 0.001) return false;
			}
		}
		return true;
	}

	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j) << " ";
			}
			os << endl;
		}
		return os;
	}

	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
	{
		(*this)(0, 0) = cos(theta);
		(*this)(0, 1) = -sin(theta);
		(*this)(1, 0) = sin(theta);
		(*this)(1, 1) = cos(theta);
	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
	{
		(*this)(0, 0) = scale;
		(*this)(0, 1) = 0;
		(*this)(1, 0) = 0;
		(*this)(1, 1) = scale;
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
	{
		for (int i = 0; i < nCols; i++)
		{
			(*this)(0, i) = xShift;
			(*this)(1, i) = yShift;
		}
	}
}
