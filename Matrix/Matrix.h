#ifndef _MATRIX_H_
#define _MATRIX_H_
struct MATRIX {
  unsigned int line; // count of lines
  unsigned int column; // count of columns
  double *matrix; // pointer to matrix array
};
class Matrix {
 public:
  MATRIX matrix; // matrix structure
  bool error;
// functions
// overloaded operators
  Matrix & operator = (const Matrix& arg);
  bool operator == (const Matrix& arg);
  bool operator != (const Matrix& arg);
  Matrix & operator * (const double number);
  Matrix & operator *= (const double number);
  Matrix & operator / (const double number);
  Matrix & operator /= (const double number);
  Matrix & operator + (const Matrix& arg);
  Matrix & operator += (const Matrix& arg);
  Matrix & operator - (const Matrix& arg);
  Matrix & operator -= (const Matrix& arg);
  Matrix & operator * (const Matrix& arg);
  Matrix & operator *= (const Matrix& arg);
  Matrix & operator / (const Matrix& arg);
  Matrix & operator /= (const Matrix& arg);
};
#endif