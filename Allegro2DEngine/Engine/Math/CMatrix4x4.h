#ifndef A2DE_CMATRIX4X4_H
#define A2DE_CMATRIX4X4_H

#include "../a2de_vals.h"
#include <array>

A2DE_BEGIN

class Vector3D;
class Vector4D;

class Matrix4x4 {
public:
    Matrix4x4();
    Matrix4x4(double m00, double m01, double m02, double m03, double m10, double m11, double m12, double m13, double m20, double m21, double m22, double m23, double m30, double m31, double m32, double m33);
    Matrix4x4(const Vector4D& row_one, const Vector4D& row_two, const Vector4D& row_three, const Vector4D& row_four);
    Matrix4x4(const Matrix4x4& other);
    ~Matrix4x4();

    static Matrix4x4 GetIdentity();
    static Matrix4x4 GetTranslationMatrix(const a2de::Vector3D& position);
    static Matrix4x4 GetTranslationMatrix(double x, double y, double z);

    static Matrix4x4 GetRotationMatrix(const a2de::Vector3D& rotations);
    static Matrix4x4 Get2DRotationMatrix(double angle);
    static Matrix4x4 Get3DXRotationMatrix(double angle);
    static Matrix4x4 Get3DYRotationMatrix(double angle);
    static Matrix4x4 Get3DZRotationMatrix(double angle);
    static Matrix4x4 GetRotationMatrix(double Xangle, double Yangle, double Zangle);
    
    static Matrix4x4 GetScaleMatrix(const a2de::Vector3D& scale);
    static Matrix4x4 GetScaleMatrix(double scale_x, double scale_y, double scale_z);

    void SetRowOne(const Vector4D& row);
    void SetRowTwo(const Vector4D& row);
    void SetRowThree(const Vector4D& row);
    void SetRowFour(const Vector4D& row);

    Vector4D GetRowOne() const;
    Vector4D GetRowOne();

    Vector4D GetRowTwo() const;
    Vector4D GetRowTwo();

    Vector4D GetRowThree() const;
    Vector4D GetRowThree();

    Vector4D GetRowFour() const;
    Vector4D GetRowFour();

    Vector4D GetColumnOne() const;
    Vector4D GetColumnOne();

    Vector4D GetColumnTwo() const;
    Vector4D GetColumnTwo();

    Vector4D GetColumnThree() const;
    Vector4D GetColumnThree();

    Vector4D GetColumnFour() const;
    Vector4D GetColumnFour();

    void SetIndex(unsigned int index, double value);

    double GetIndex(unsigned int index) const;
    double GetIndex(unsigned int index);

    Matrix4x4& operator=(const Matrix4x4& rhs);

    void Transpose();
    void Inverse();

    static double CalculateDeterminant(const Matrix4x4& mat);
    double CalculateDeterminant() const;
    double CalculateDeterminant();

    double CalculateTrace() const;
    double CalculateTrace();

    static Matrix4x4 Transpose(const Matrix4x4& mat);
    static Matrix4x4 Inverse(const Matrix4x4& mat);

    const double * const operator*() const;

    bool operator==(const Matrix4x4& rhs) const;
    bool operator==(const Matrix4x4& rhs);

    bool operator!=(const Matrix4x4& rhs) const;
    bool operator!=(const Matrix4x4& rhs);

    Matrix4x4 operator*(const Matrix4x4& rhs);
    Matrix4x4 operator*(double scalar);
    Vector4D operator*(const Vector4D& rhs);

    Matrix4x4& operator*=(const Matrix4x4& rhs);
    Matrix4x4& operator*=(double scalar);

    Matrix4x4 operator+(const Matrix4x4& rhs);
    Matrix4x4& operator+=(const Matrix4x4& rhs);

    Matrix4x4 operator-(const Matrix4x4& rhs);
    Matrix4x4& operator-=(const Matrix4x4& rhs);

    Matrix4x4 operator/(const Matrix4x4& rhs);
    Matrix4x4& operator/=(const Matrix4x4& rhs);

    Matrix4x4 operator-();

    friend Matrix4x4 operator*(double scalar, const Matrix4x4& rhs);
    friend Vector4D operator*(const Matrix4x4& lhs, const Vector4D& rhs);

protected:
private:
    //[00 01 02 03]
    //[10 11 12 13]
    //[20 21 22 23]
    //[30 31 32 33]
    std::array<double, 16> _indicies;
};

A2DE_END

#endif