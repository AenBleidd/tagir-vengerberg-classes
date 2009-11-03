#include "Matrix.h"
// Operators
Matrix & Matrix::operator = (const Matrix& arg) {
  if (this == &arg) return *this;
// return left matrix if there is some error
  if (this->error == true || arg.error == true) return *this;
  this->matrix.line = arg.matrix.line;
  this->matrix.column = arg.matrix.column;
  unsigned j = this->matrix.line * this->matrix.column;
  this->matrix.matrix = new double [j];
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
Matrix & Matrix::operator * (const double number) {
  return *this *= number;
}
Matrix & Matrix::operator / (const double number) {
  return *this /= number;
}
Matrix & Matrix::operator *= (const double number) {
// return left matrix if there is some error
  if (this->error == true) return *this;
  int j = this->matrix.line*this->matrix.column;
  for (int i = 0; i < j; i++)
    this->matrix.matrix[i] *= number;
  return *this;
}
Matrix & Matrix::operator /= (const double number) {
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
  res.matrix.matrix = new double [res.matrix.line * res.matrix.column];
  res.error = false;
  double sum;
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
  res.matrix.matrix = new double [res.matrix.line * res.matrix.column];
  res.error = false;
  double sum;
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
  ret->error = false;
  ret->matrix.line = matrix.column;
  ret->matrix.column = matrix.line;
  ret->matrix.matrix = new double [ret->matrix.line * ret->matrix.column];
  for (int i = 0; i < ret->matrix.line; i++) {
    for (int j = 0; j < ret->matrix.column; j++) {
      ret->matrix.matrix[i*ret->matrix.column+j] = matrix.matrix[j*ret->matrix.line+i];
    }
  }
  return ret;
}