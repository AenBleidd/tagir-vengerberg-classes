#ifndef _MATRIX_H_
#define _MATRIX_H_
struct MATRIX {
  unsigned int line;
  unsigned int column;
  double *matrix;
};
class Matrix {
 public:
  MATRIX matrix; // matrix structure
// functions
// overloaded operators
  Matrix & operator = (const Matrix& arg);
  bool operator == (const Matrix& arg);
  bool operator != (const Matrix& arg);
  Matrix & operator * (const double number);
  Matrix & operator *= (const double number);
};
#endif