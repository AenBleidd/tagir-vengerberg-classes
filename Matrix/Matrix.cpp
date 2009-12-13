#include "Matrix.h"
Matrix::Matrix() {
  error = false;
  errorcode.operr = 0;
  errorcode.ferr = 0;
  errorcode.reserved0 = 0;
  errorcode.reserved1= 0;
}
unsigned long int Matrix::GetLastError() {
  if (error == false) return 0;
  unsigned long int err = 0;
  err += errorcode.ferr;
  err = err << 16;
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
  if (this->error == true || arg.error == true) {
    errorcode.operr |= 2; return false;
  }
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
  if (this->error == true || arg.error == true) {
    errorcode.operr |= 2; return false;
  }
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
// return left matrix if there is some error
  if (this->error == true || arg.error == true) return *this;
  if ((this->matrix.line != arg.matrix.line) ||
     (this->matrix.column != arg.matrix.column)) {
    this->error = true;
    this->errorcode.operr |= 16;
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
// return left matrix if there is some error
  if (this->error == true || arg.error == true) return *this;
  if ((this->matrix.line != arg.matrix.line) ||
     (this->matrix.column != arg.matrix.column)) {
    this->error = true;
    this->errorcode.operr |= 32;
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
// return left matrix if there is some error
  if (this->error == true || arg.error == true) return *this;
  if (this->matrix.column != arg.matrix.line) {
  this->error = true;
  this->errorcode.operr |= 64;
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
// return left matrix if there is some error
  if (this->error == true || arg.error == true) return *this;
  if (this->matrix.column != arg.matrix.line) {
  this->error = true;
  this->errorcode.operr |= 128;
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
// return left matrix if there is some error
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
// return left matrix if there is some error
  if (error == true) return this;
  if (matrix.line != matrix.column) {
    error = true; errorcode.ferr |= 2; return this;
  }
  Matrix *ret = new Matrix;
  ret->matrix.line = matrix.line;
  ret->matrix.column = matrix.column;
  ret->matrix.matrix = new long double [ret->matrix.line * ret->matrix.column];
  for (unsigned int n = 0; n < matrix.line; n++)
    for (unsigned int k = 0; k < matrix.column; k++)
      if (error == true) { delete ret; return this; }
      else
        ret->matrix.matrix[n*ret->matrix.column+k] = MinorAux(n,k);
  return ret;
}
long double Matrix::MinorAux (unsigned int line, unsigned int column) {
// return 0 if there is some error
  if (error == true) return 0;
  if (matrix.line != matrix.column) {
    error = true; errorcode.ferr |= 8; return 0;
  }
  if (matrix.line == 2) {
    for (unsigned char i = 0; i < 2; i++)
      for (unsigned char j = 0; j < 2; j++)
        if (i != line && j != column)
          return matrix.matrix[i*2+j];
  }
  else {
    Matrix temp = *Minor(line,column);
    long double ret = temp.Det();
    if (temp.error == true) {
      error = true; errorcode.ferr |= temp.errorcode.ferr; return 0;
    }
    else return ret;
  }
}
Matrix* Matrix::Minor (unsigned int line, unsigned int column) {
// return left matrix if there is some error
  if (error == true) return this;
  if (matrix.line != matrix.column) {
    error = true; errorcode.ferr |= 4; return this;
  }
  Matrix *temp = new Matrix;
  temp->matrix.line = matrix.line - 1;
  temp->matrix.column = matrix.column - 1;
  temp->matrix.matrix = new long double [temp->matrix.line*temp->matrix.column];
  unsigned int n = 0;
  for (unsigned int i = 0; i < matrix.line; i++)
    for (unsigned int j = 0; j < matrix.column; j++)
      if (i != line && j != column)
         temp->matrix.matrix[n++] = matrix.matrix[i*matrix.column+j];
  return temp;
}
long double Matrix::Det () {
// return 0 if there is some error
  if (error == true) return 0;
  if (matrix.line != matrix.column) {
    error = true; errorcode.ferr |= 16; return 0;
  }
  long double ret = 0;
  for (unsigned int j = 0; j < matrix.column; j++)
    if (error == true) return 0;
    else
      ret += pow((-1),2+j)*matrix.matrix[j]*MinorAux(0,j);
  if (error == true) return 0;
  return ret;
}
long double Matrix::Cofactor (unsigned int line, unsigned int column) {
// return 0 if there is some error
  if (error == true) return 0;
  if (matrix.line != matrix.column) {
    error = true; errorcode.ferr |= 64; return 0;
  }
  long double ret;
  ret = pow((-1),line+column)*MinorAux(line,column);
  if (error == true) return 0;
  return ret;
}
Matrix* Matrix::Cofactor () {
// return left matrix if there is some error
  if (error == true) return this;
  if (matrix.line != matrix.column) {
   error = true; errorcode.ferr |= 32; return this;
  }
  Matrix *ret = new Matrix;
  ret = Minor();
  if (ret->error == true) {
    error = true; errorcode.ferr |= ret->errorcode.ferr;
    delete ret; return this;
  }
  for (unsigned int i = 0; i < matrix.line; i++)
    for (unsigned int j = 0; j < matrix.column; j++)
      ret->matrix.matrix[i*matrix.column+j] *= pow((-1), i+j);
  return ret;
}
Matrix* Matrix::Adjugate () {
// return left matrix if there is some error
  if (error == true) return this;
  if (matrix.line != matrix.column) {
    error = true; errorcode.ferr |= 128; return this;
  }
  Matrix* ret = new Matrix;
  ret = Cofactor();
  if (ret->error == true) {
    error = true; errorcode.ferr |= ret->errorcode.ferr;
    delete ret ;return this;
  }
  ret = ret->Trans();
  if (ret->error == true) {
    error = true; errorcode.ferr |= ret->errorcode.ferr;
    delete ret; return this;
  }
  return ret;
}
Matrix* Matrix::Invert() {
// return left matrix if there is some error
  if (error == true) return this;
  if (matrix.line != matrix.column) {
    error = true; errorcode.ferr |= 256; return this;
 };
  long double det = Det();
  if (error == true) return this;
  if (det == 0) { error = true; errorcode.ferr |= 256; return this; };
  Matrix* ret = new Matrix;
  ret = Adjugate();
  if (ret->error == true) {
    error = true; errorcode.ferr |= ret->errorcode.ferr;
    delete ret; return this;
  }
  *ret *= (1/det);
  if (ret->error == true) {
    error = true; errorcode.ferr |= ret->errorcode.ferr;
    delete ret; return this;
  }
  return ret;
}
long double Matrix::Norm (unsigned char type) {
  long double norm = 0;
  long double *temp = 0;
  if (type == 0) {
    temp = new long double[matrix.line];
    for (unsigned int i = 0; i < matrix.line; i++) {
       temp[i] = 0;
       for (unsigned int j = 0; j < matrix.column; j++) {
         temp[i] += fabs(matrix.matrix[i*matrix.column+j]);
       }
    }
    norm = temp[0];
    for (unsigned int i = 1; i < matrix.line; i++)
      if (temp[i] > norm) norm = temp[i];
  delete[] temp;
  return norm;
  }
  else if (type == 1) {
    temp = new long double[matrix.column];
    for (unsigned int i = 0; i < matrix.column; i++) {
       temp[i] = 0;
       for (unsigned int j = 0; j < matrix.line; j++) {
         temp[i] += fabs(matrix.matrix[j*matrix.column+i]);
       }
    }
    norm = temp[0];
    for (unsigned int i = 1; i < matrix.column; i++)
      if (temp[i] > norm) norm = temp[i];
  delete[] temp;
  return norm;
  }
  else if (type == 2) {
    for (unsigned int i = 0; i < matrix.line*matrix.column; i++)  norm += pow(matrix.matrix[i],2);
    norm = sqrt(norm);
    return norm;
  }
  else {
    errorcode.ferr |= 512;
    return 0;
  }
}