#include "Matrix.h"
Matrix::Matrix() {
  error = false;
}
unsigned long int Matrix::GetLastError() {
  if (error == false) return 0;
  unsigned long int err = 0;
  err += errorcode.ferr;
  err = err << 8;
  err += errorcode.operr;
  return err;
}
// Operators
Matrix & Matrix::operator = (const Matrix& arg) {
  if (this == &arg) return *this;
// return left matrix if there is some error
  if (this->error == true || arg.error == true) return *this;
  this->matrix.line = arg.matrix.line;
  this->matrix.column = arg.matrix.column;
  unsigned j = this->matrix.line * this->matrix.column;
  this->matrix.matrix = new long double [j];
  for (int i = 0; i < j; i++)
    this->matrix.matrix[i] = arg.matrix.matrix[i];
  return *this;
}
bool Matrix::operator == (const Matrix& arg) {
// return false if there is some error
  if (this->error == true || arg.error == true) return false;
  if (this->matrix.line != arg.matrix.line &&
  this->matrix.column != arg.matrix.column)
    return false;
  unsigned j = this->matrix.line*this->matrix.column;
 for (int i = 0; i < j; i++)
    if (this->matrix.matrix[i] != arg.matrix.matrix[i])
      return false;
  return true;
}
bool Matrix::operator != (const Matrix& arg) {
// return false if there is some error
  if (this->error == true || arg.error == true) return false;
  return !(*this == arg);
}
Matrix & Matrix::operator * (const long double number) {
  return *this *= number;
}
Matrix & Matrix::operator / (const long double number) {
  return *this /= number;
}
Matrix & Matrix::operator *= (const long double number) {
// return left matrix if there is some error
  if (this->error == true) return *this;
  int j = this->matrix.line*this->matrix.column;
  for (int i = 0; i < j; i++)
    this->matrix.matrix[i] *= number;
  return *this;
}
Matrix & Matrix::operator /= (const long double number) {
  return *this *= (1/number);
}
Matrix & Matrix::operator += (const Matrix& arg) {
// return false if there is some error
  if (this->error == true || arg.error == true) return *this;
  if ((this->matrix.line != arg.matrix.line) ||
     (this->matrix.column != arg.matrix.column)) {
    this->error = true;
    return *this;
  }
  int j = this->matrix.line*this->matrix.column;
  for (int i = 0; i < j; i++)
    this->matrix.matrix[i] += arg.matrix.matrix[i];
  return *this;
}
Matrix & Matrix::operator + (const Matrix& arg) {
  return *this += arg;
}
Matrix & Matrix::operator -= (const Matrix& arg) {
// return false if there is some error
  if (this->error == true || arg.error == true) return *this;
  if ((this->matrix.line != arg.matrix.line) ||
     (this->matrix.column != arg.matrix.column)) {
    this->error = true;
    return *this;
  }
  int j = this->matrix.line*this->matrix.column;
  for (int i = 0; i < j; i++)
    this->matrix.matrix[i] -= arg.matrix.matrix[i];
  return *this;
}
Matrix & Matrix::operator - (const Matrix& arg) {
  return *this -= arg;
}
Matrix & Matrix::operator *= (const Matrix& arg) {
// return false if there is some error
  if (this->error == true || arg.error == true) return *this;
  if (this->matrix.column != arg.matrix.line) {
  this->error = true;
   return *this;
  }
// Create new matrix for result
  Matrix res;
  res.matrix.line = arg.matrix.line;
  res.matrix.column = this->matrix.column;
  res.matrix.matrix = new long double [res.matrix.line * res.matrix.column];
  long double sum;
  for (int i = 0; i < res.matrix.line; i++) {
    for (int j = 0; j < res.matrix.column; j++) {
      sum = 0;
      for (int n = 0; n < arg.matrix.column; n++)
        sum += this->matrix.matrix[i*this->matrix.column+n]*arg.matrix.matrix[n*arg.matrix.column+j];
      res.matrix.matrix[i*res.matrix.column+j] = sum;
    }
  }
  *this = res;
  return *this;
}
Matrix & Matrix::operator * (const Matrix& arg) {
  return *this *= arg;
}
Matrix & Matrix::operator /= (const Matrix& arg) {
// return false if there is some error
  if (this->error == true || arg.error == true) return *this;
  if (this->matrix.column != arg.matrix.line) {
  this->error = true;
   return *this;
  }
// Create new matrix for result
  Matrix res;
  res.matrix.line = arg.matrix.line;
  res.matrix.column = this->matrix.column;
  res.matrix.matrix = new long double [res.matrix.line * res.matrix.column];
  long double sum;
  for (int i = 0; i < res.matrix.line; i++) {
    for (int j = 0; j < res.matrix.column; j++) {
      sum = 0;
      for (int n = 0; n < arg.matrix.column; n++)
        sum += this->matrix.matrix[i*this->matrix.column+n]/arg.matrix.matrix[n*arg.matrix.column+j];
      res.matrix.matrix[i*res.matrix.column+j] = sum;
    }
  }
  *this = res;
  return *this;
}
Matrix & Matrix::operator / (const Matrix& arg) {
  return *this /= arg;
}
// Functions
Matrix* Matrix::Trans () {
// return false if there is some error
  if (error == true) return this;
  Matrix *ret = new Matrix;
  ret->matrix.line = matrix.column;
  ret->matrix.column = matrix.line;
  ret->matrix.matrix = new long double [ret->matrix.line * ret->matrix.column];
  for (int i = 0; i < ret->matrix.line; i++)
    for (int j = 0; j < ret->matrix.column; j++)
      ret->matrix.matrix[i*ret->matrix.column+j] = matrix.matrix[j*ret->matrix.line+i];
  return ret;
}
Matrix* Matrix::Minor () {
// return false if there is some error
  if (error == true) return this;
  if (matrix.line != matrix.column) { error = true; return this;};
  Matrix *ret = new Matrix;
  ret->matrix.line = matrix.line;
  ret->matrix.column = matrix.column;
  ret->matrix.matrix = new long double [ret->matrix.line * ret->matrix.column];
  for (unsigned int n = 0; n < matrix.line; n++)
    for (unsigned int k = 0; k < matrix.column; k++)
      ret->matrix.matrix[n*ret->matrix.column+k] = MinorAux(n,k);
  return ret;
}
long double Matrix::MinorAux (unsigned int line, unsigned int column) {
// return 0 if there is some error
  if ((error == true) || (matrix.line != matrix.column)) { error = true; return 0; };
  if (matrix.line == 2) {
    for (unsigned char i = 0; i < 2; i++)
      for (unsigned char j = 0; j < 2; j++)
        if (i != line && j != column)
          return matrix.matrix[i*2+j];
  }
  else {
    Matrix temp = *Minor(line,column);
    long double ret = temp.Det();
    if (temp.error == true) { error = true; return 0; }
    else return ret;
  }
}
Matrix* Matrix::Minor (unsigned int line, unsigned int column) {
  // return 0 if there is some error
  if ((error == true) || (matrix.line != matrix.column)) { error = true; return this; };
  Matrix *temp = new Matrix;
  temp->matrix.line = matrix.line - 1;
  temp->matrix.column = matrix.column - 1;
  temp->matrix.matrix = new long double [temp->matrix.line * temp->matrix.column];
  unsigned int n = 0;
  for (unsigned int i = 0; i < matrix.line; i++)
    for (unsigned int j = 0; j < matrix.column; j++)
      if (i != line && i != column)
         temp->matrix.matrix[n++];
  return temp;
}
long double Matrix::Det () {
// return 0 if there is some error
  if ((error == true) || (matrix.line != matrix.column)) { error = true; return 0; };
  long double ret = 0;
  for (unsigned int j = 0; j < matrix.column; j++)
    if (error == true) return 0;
    else
      ret += pow((-1),2+j)*matrix.matrix[j]*MinorAux(0,j);
  if (error == true) return 0;
  return ret;
}