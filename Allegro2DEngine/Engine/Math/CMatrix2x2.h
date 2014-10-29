#ifndef A2DE_CMATRIX2X2_H
#define A2DE_CMATRIX2X2_H

#include "../a2de_vals.h"
#include "CVector2D.h"
#include <array>

A2DE_BEGIN

class Matrix2x2 {
public:
    Matrix2x2();
    Matrix2x2(double m00, double m01, double m10, double m11);
    Matrix2x2(const Vector2D& row_one, const Vector2D& row_two);
    Matrix2x2(const Matrix2x2& other);
    ~Matrix2x2();

    static Matrix2x2 GetIdentity();
    static Vector2D GetTranslationMatrix(double x, double y);
    static Matrix2x2 GetRotationMatrix(double angle);
    static Matrix2x2 GetScaleMatrix(double scale_x, double scale_y);


    void SetRowOne(const Vector2D& row);
    void SetRowTwo(const Vector2D& row);

    Vector2D GetRowOne() const;
    Vector2D GetRowOne();

    Vector2D GetRowTwo() const;
    Vector2D GetRowTwo();

    Vector2D GetColumnOne() const;
    Vector2D GetColumnOne();

    Vector2D GetColumnTwo() const;
    Vector2D GetColumnTwo();

    void SetIndex(unsigned int index, double value);
    
    double GetIndex(unsigned int index) const;
    double GetIndex(unsigned int index);

    Matrix2x2& operator=(const Matrix2x2& rhs);

    void Transpose();
    void Inverse();

    static double CalculateDeterminant(const Matrix2x2& mat);
    double CalculateDeterminant() const;
    double CalculateDeterminant();

    double CalculateTrace() const;
    double CalculateTrace();

    static Matrix2x2 Transpose(const Matrix2x2& mat);
    static Matrix2x2 Inverse(const Matrix2x2& mat);
    
    bool operator==(const Matrix2x2& rhs) const;
    bool operator==(const Matrix2x2& rhs);

    bool operator!=(const Matrix2x2& rhs) const;
    bool operator!=(const Matrix2x2& rhs);

    const double * const operator*() const;

    Matrix2x2 operator*(const Matrix2x2& rhs);
    Matrix2x2 operator*(double scalar);
    //Vector2D operator*(const Vector2D& rhs);

    Matrix2x2& operator*=(const Matrix2x2& rhs);
    Matrix2x2& operator*=(double scalar);

    Matrix2x2 operator+(const Matrix2x2& rhs);
    Matrix2x2& operator+=(const Matrix2x2& rhs);

    Matrix2x2 operator-(const Matrix2x2& rhs);
    Matrix2x2& operator-=(const Matrix2x2& rhs);

    Matrix2x2 operator/(const Matrix2x2& rhs);
    Matrix2x2& operator/=(const Matrix2x2& rhs);

    Matrix2x2 operator-();

    friend Matrix2x2 operator*(double scalar, const Matrix2x2& rhs);
    friend Vector2D operator*(const Matrix2x2& lhs, const Vector2D& rhs);

protected:
private:
    //[00 01]
    //[10 11]
    std::array<double, 4> _indicies;
};

A2DE_END

#endif