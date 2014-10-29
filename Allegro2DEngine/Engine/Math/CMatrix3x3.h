#ifndef A2DE_CMATRIX3X3_H
#define A2DE_CMATRIX3X3_H

#include "../a2de_vals.h"
#include "CVector3D.h"
#include <array>

A2DE_BEGIN

class Matrix3x3 {
public:
    Matrix3x3();
    Matrix3x3(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22);
    Matrix3x3(const Vector3D& row_one, const Vector3D& row_two, const Vector3D& row_three);
    Matrix3x3(const Matrix3x3& other);
    ~Matrix3x3();

    static Matrix3x3 GetIdentity();
    static Matrix3x3 GetTranslationMatrix(double x, double y);
    static Matrix3x3 GetTranslationMatrix(const a2de::Vector2D& pos);
    static Matrix3x3 GetRotationMatrix(double angle);
    static Matrix3x3 GetScaleMatrix(double scale_x, double scale_y);
    static Matrix3x3 GetScaleMatrix(const a2de::Vector2D& scale);

    void SetRowOne(const Vector3D& row);
    void SetRowTwo(const Vector3D& row);
    void SetRowThree(const Vector3D& row);

    Vector3D GetRowOne() const;
    Vector3D GetRowOne();

    Vector3D GetRowTwo() const;
    Vector3D GetRowTwo();

    Vector3D GetRowThree() const;
    Vector3D GetRowThree();

    Vector3D GetColumnOne() const;
    Vector3D GetColumnOne();

    Vector3D GetColumnTwo() const;
    Vector3D GetColumnTwo();

    Vector3D GetColumnThree() const;
    Vector3D GetColumnThree();

    void SetIndex(unsigned int index, double value);

    double GetIndex(unsigned int index) const;
    double GetIndex(unsigned int index);

    Matrix3x3& operator=(const Matrix3x3& rhs);

    void Transpose();
    void Inverse();

    static double CalculateDeterminant(const Matrix3x3& mat);
    double CalculateDeterminant() const;
    double CalculateDeterminant();

    double CalculateTrace() const;
    double CalculateTrace();

    static Matrix3x3 Transpose(const Matrix3x3& mat);
    static Matrix3x3 Inverse(const Matrix3x3& mat);

    const double * const operator*() const;

    bool operator==(const Matrix3x3& rhs) const;
    bool operator==(const Matrix3x3& rhs);

    bool operator!=(const Matrix3x3& rhs) const;
    bool operator!=(const Matrix3x3& rhs);

    Matrix3x3 operator*(const Matrix3x3& rhs);
    Matrix3x3 operator*(double scalar);
    Vector3D operator*(const Vector3D& rhs) const;
    Vector3D operator*(const Vector3D& rhs);

    Matrix3x3& operator*=(const Matrix3x3& rhs);
    Matrix3x3& operator*=(double scalar);

    Matrix3x3 operator+(const Matrix3x3& rhs) const;
    Matrix3x3 operator+(const Matrix3x3& rhs);
    Matrix3x3& operator+=(const Matrix3x3& rhs);

    Matrix3x3 operator-(const Matrix3x3& rhs) const;
    Matrix3x3 operator-(const Matrix3x3& rhs);
    Matrix3x3& operator-=(const Matrix3x3& rhs);

    Matrix3x3 operator/(const Matrix3x3& rhs) const;
    Matrix3x3 operator/(const Matrix3x3& rhs);
    Matrix3x3& operator/=(const Matrix3x3& rhs);

    Matrix3x3 operator-();

    friend Matrix3x3 operator*(double scalar, const Matrix3x3& rhs);
    friend Vector3D operator*(const Matrix3x3& lhs, const Vector3D& rhs);

protected:
private:
    //[00 01 02]
    //[10 11 12]
    //[20 21 22]
    std::array<double, 9> _indicies;
};

A2DE_END

#endif