#include <string.h>
#include "../../base/base.h"

#ifndef MATRIX_H
#define MATRIX_H

struct Matrix {
  int64nRow, nCol;
  double *lpdf; // Don't Use It!

  double *operator [](int64nIndex) {
    return lpdf + (nIndex * nCol);
  }

  const double *operator [](int64nIndex) const {
    return lpdf + (nIndex * nCol);
  }

  Matrix(void) {
    lpdf = NULL;
  }

  Matrix(int64nRowLen, int64nColLen) {
    nRow = nRowLen;
    nCol = nColLen;
    lpdf = new double[nRow * nCol];
    memset(lpdf, 0, nRow * nCol * sizeof(double));
  }

  Matrix(const Matrix &matr) {
    nRow = matr.nRow;
    nCol = matr.nCol;
    lpdf = new double[nRow * nCol];
    memcpy(lpdf, matr.lpdf, nRow * nCol * sizeof(double));
  }

  ~Matrix(void) {
    if (lpdf != NULL) {
      delete[] lpdf;
      lpdf = NULL;
    }
  }

  Matrix &operator =(const Matrix &matr) {
    if (lpdf != matr.lpdf) {
      if (lpdf != NULL) {
        delete[] lpdf;
        lpdf = NULL;
      }
      nRow = matr.nRow;
      nCol = matr.nCol;
      lpdf = new double[nRow * nCol];
      memcpy(lpdf, matr.lpdf, nRow * nCol * sizeof(double));
    }
    return *this;
  }

  void Load(int64nDstRow, int64nDstCol, const Matrix &matrSrc, int64nSrcRow, int64nSrcCol, int64nRowLen, int64nColLen) {
    int64i, j;
    for (i = 0; i < nRowLen; i ++) {
      for (j = 0; j < nColLen; j ++) {
        (*this)[nDstRow + i][nDstCol + j] = matrSrc[nSrcRow + i][nSrcCol + j];
      }
    }
  }

  Matrix Merge(const Matrix &matrBottomLeft, const Matrix &matrTopRight, const Matrix &matrBottomRight) const;
  Matrix MergeRow(const Matrix &matrBottom) const;
  Matrix MergeCol(const Matrix &matrRight) const;
  Matrix DelRowCol(int64nRowStart, int64nRowLen, int64nColStart, int64nColLen) const;
  Matrix DelRow(int64nStart, int64nLen) const;
  Matrix DelCol(int64nStart, int64nLen) const;

  const Matrix &operator +(void) const {
    return *this;
  }

  Matrix operator -(void) const;
  Matrix operator +(const Matrix &matr) const;
  Matrix operator -(const Matrix &matr) const;
  Matrix operator *(double dfReal) const;
  Matrix operator /(double dfReal) const;

  Matrix &operator +=(const Matrix &matr) {
    int64i, j;
    for (i = 0; i < nRow; i ++) {
      for (j = 0; j < nCol; j ++) {
        (*this)[i][j] += matr[i][j];
      }
    }
    return *this;
  }

  Matrix &operator -=(const Matrix &matr) {
    int64i, j;
    for (i = 0; i < nRow; i ++) {
      for (j = 0; j < nCol; j ++) {
        (*this)[i][j] -= matr[i][j];
      }
    }
    return *this;
  }

  Matrix &operator *=(double dfReal) {
    int64i, j;
    for (i = 0; i < nRow; i ++) {
      for (j = 0; j < nCol; j ++) {
        (*this)[i][j] *= dfReal;
      }
    }
    return *this;
  }

  Matrix &operator /=(double dfReal) {
    int64i, j;
    for (i = 0; i < nRow; i ++) {
     for (j = 0; j < nCol; j ++) {
        (*this)[i][j] /= dfReal;
      }
    }
    return *this;
  }

  Matrix operator *(const Matrix &matr) const;

  void RowSwap(int64nDstRow, int64nSrcRow, int64nStart = 0) {
    int64i;
    if (nDstRow != nSrcRow) {
      for (i = nStart; i < nCol; i ++) {
        SWAP((*this)[nDstRow][i], (*this)[nSrcRow][i]);
      }
    }
  }

  void RowMul(int64nDstRow, double dfReal, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nCol; i ++) {
      (*this)[nDstRow][i] *= dfReal;
    }
  }

  void RowAdd(int64nDstRow, int64nSrcRow, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nCol; i ++) {
      (*this)[nDstRow][i] += (*this)[nSrcRow][i];
    }
  }

  void RowAddMul(int64nDstRow, int64nSrcRow, double dfReal, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nCol; i ++) {
      (*this)[nDstRow][i] += (*this)[nSrcRow][i] * dfReal;
    }
  }

  void RowSub(int64nDstRow, int64nSrcRow, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nCol; i ++) {
      (*this)[nDstRow][i] -= (*this)[nSrcRow][i];
    }
  }

  void RowSubMul(int64nDstRow, int64nSrcRow, double dfReal, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nCol; i ++) {
      (*this)[nDstRow][i] -= (*this)[nSrcRow][i] * dfReal;
    }
  }

  void ColSwap(int64nDstCol, int64nSrcCol, int64nStart = 0) {
    int64i;
    if (nDstCol != nSrcCol) {
      for (i = nStart; i < nRow; i ++) {
        SWAP((*this)[i][nDstCol], (*this)[i][nSrcCol]);
      }
    }
  }

  void ColMul(int64nDstCol, double dfReal, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nRow; i ++) {
      (*this)[i][nDstCol] *= dfReal;
    }
  }

  void ColAdd(int64nDstCol, int64nSrcCol, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nRow; i ++) {
      (*this)[i][nDstCol] += (*this)[i][nSrcCol];
    }
  }

  void ColAddMul(int64nDstCol, int64nSrcCol, double dfReal, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nRow; i ++) {
      (*this)[i][nDstCol] += (*this)[i][nSrcCol] * dfReal;
    }
  }

  void ColSub(int64nDstCol, int64nSrcCol, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nRow; i ++) {
      (*this)[i][nDstCol] -= (*this)[i][nSrcCol];
    }
  }

  void ColSubMul(int64nDstCol, int64nSrcCol, double dfReal, int64nStart = 0) {
    int64i;
    for (i = nStart; i < nRow; i ++) {
      (*this)[i][nDstCol] -= (*this)[i][nSrcCol] * dfReal;
    }
  }

  Matrix Trans(void) const;
  double Det(void) const;
  Matrix LeftDiv(const Matrix &matr) const;
  Matrix RightDiv(const Matrix &matr) const;
  Matrix Inv(void) const;
}; // matr

inline Matrix Trans(const Matrix &matr) {
  return matr.Trans();
}

inline double Det(const Matrix &matr) {
  return matr.Det();
}

inline Matrix Inv(const Matrix &matr) {
  return matr.Inv();
}

Matrix operator *(double dfReal, const Matrix &matr);
Matrix Merge(const Matrix &matrTopLeft, const Matrix &matrBottomLeft,
    const Matrix &matrTopRight, const Matrix &matrBottomRight);
Matrix MergeRow(const Matrix &matrTop, const Matrix &matrBottom);
Matrix MergeCol(const Matrix &matrLeft, const Matrix &matrRight);

#endif
