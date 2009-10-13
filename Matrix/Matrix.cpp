#include "Matrix.h"
Matrix & Matrix::operator = (const Matrix& arg) {
  if (this == &arg) return *this;
  this->matrix.line = arg.matrix.line;
  this->matrix.column = arg.matrix.column;
  unsigned j = this->matrix.line * this->matrix.column;
  this->matrix.matrix = new double [j];
  for (int i = 0; i < j; i++)
    this->matrix.matrix[i] = arg.matrix.matrix[i];
  return *this;
}
bool Matrix::operator == (const Matrix& arg) {
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
  return !(*this == arg);
}
Matrix & Matrix::operator * (const double number) {
  return *this *= number;
}
Matrix & Matrix::operator *= (const double number) {
  int j = this->matrix.line*this->matrix.column;
  for (int i = 0; i < j; i++)
    this->matrix.matrix[i] *= number;
  return *this;
}
Matrix & Matrix::operator += (const Matrix& arg) {
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