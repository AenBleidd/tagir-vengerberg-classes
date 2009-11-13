#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <math.h>
struct MATRIX {
  unsigned int line; // count of lines
  unsigned int column; // count of columns
  long double *matrix; // pointer to matrix array
};
struct ERRORCODE {
  unsigned short int operr;
  unsigned short int ferr;
  unsigned short int reserved0;
  unsigned short int reserved1;
};
class Matrix {
 public:
  Matrix();
  MATRIX matrix; // matrix structure
  bool error;
// functions
  unsigned long int GetLastError();
  Matrix* Trans (void);
  Matrix* Minor (void);
  Matrix* Minor (unsigned int line, unsigned int column);
  long double MinorAux (unsigned int line, unsigned int column);
  long double Det(void);
// overloaded operators
  Matrix & operator = (const Matrix& arg);
  bool operator == (const Matrix& arg);
  bool operator != (const Matrix& arg);
  Matrix & operator * (const long double number);
  Matrix & operator *= (const long double number);
  Matrix & operator / (const long double number);
  Matrix & operator /= (const long double number);
  Matrix & operator + (const Matrix& arg);
  Matrix & operator += (const Matrix& arg);
  Matrix & operator - (const Matrix& arg);
  Matrix & operator -= (const Matrix& arg);
  Matrix & operator * (const Matrix& arg);
  Matrix & operator *= (const Matrix& arg);
  Matrix & operator / (const Matrix& arg);
  Matrix & operator /= (const Matrix& arg);
 private:
  ERRORCODE errorcode;
};
#endif