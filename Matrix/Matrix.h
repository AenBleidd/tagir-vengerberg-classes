#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <math.h>
struct MATRIX {
  unsigned int line; // count of lines
  unsigned int column; // count of columns
  long double *matrix; // pointer to matrix array
};
struct ERRORCODE {
  unsigned short int operr; // operator errorcode
  unsigned short int ferr; // function errorcode
  unsigned short int reserved0; // reserved
  unsigned short int reserved1; // reserved
};
class Matrix {
 public:
  Matrix();
  Matrix(int lines, int columns);
  ~Matrix();
  MATRIX matrix; // matrix structure
  bool error;
// functions
// group 0 (errorcode.ferr)
  unsigned long int GetLastError();
  Matrix* Trans (void); // reserved errorcode 1
  Matrix* Minor (void); // errorcode 2
  Matrix* Minor (unsigned int line, unsigned int column); // errorcode 4
  long double MinorAux (unsigned int line, unsigned int column); // errorcode 8
  long double Det (void); // errorcode 16
  Matrix* Cofactor (void); // errorcode 32
  long double Cofactor(unsigned int line, unsigned int column); // errorcode 64
  Matrix* Adjugate (void); // reserved errorcode 128
  Matrix* Invert (void); // reserved errorcode 256
  long double Norm (unsigned char type); // errorcode 512
// overloaded operators
  Matrix & operator = (const Matrix& arg); // reserved errorcode 1
  bool operator == (const Matrix& arg); // errorcode 2
  bool operator != (const Matrix& arg); // errorcode 2
  Matrix & operator * (const long double number); // reserved errorcode 4
  Matrix & operator *= (const long double number); // reserved errorcode 4
  Matrix & operator / (const long double number); // reserved errorcode 8
  Matrix & operator /= (const long double number); // reserved errorcode 8
  Matrix & operator + (const Matrix& arg); // errorcode 16
  Matrix & operator += (const Matrix& arg); // errorcode 16
  Matrix & operator - (const Matrix& arg); // errorcode 32
  Matrix & operator -= (const Matrix& arg); // errorcode 32
  Matrix & operator * (const Matrix& arg); // errorcode 64
  Matrix & operator *= (const Matrix& arg); // errorcode 64
  Matrix & operator / (const Matrix& arg); // errorcode 128
  Matrix & operator /= (const Matrix& arg); // errorcode 128
 private:
  ERRORCODE errorcode;
};
#endif