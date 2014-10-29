/**************************************************************************************************
// file:	Engine\Math\CVector3D.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the vector 3 d class
 **************************************************************************************************/
#include "CVector3D.h"

#include <cassert>
#include <cmath>

#include "../a2de_exceptions.h"
#include "MiscMath.h"


#include "CVector2D.h"
#include "CVector4D.h"

A2DE_BEGIN

Vector3D::Vector3D() : _x(0.0), _y(0.0), _z(0.0), _angle(0.0) {
    CalculateAngle();
}

Vector3D::Vector3D(double x, double y) : _x(x), _y(y), _z(0.0), _angle(0.0) {
    CalculateAngle();
}

Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z), _angle(0.0) {
    CalculateAngle();
}

Vector3D::Vector3D(const Vector3D& v3d) : _x(v3d.GetX()), _y(v3d.GetY()), _z(v3d.GetZ()), _angle(0.0) {
    CalculateAngle();
}

Vector3D::Vector3D(const Vector2D& v2d) : _x(v2d.GetX()), _y(v2d.GetY()), _z(0.0), _angle(0.0)  {
    CalculateAngle();
}

Vector3D::~Vector3D() {
    /* DO NOTHING */
}

double Vector3D::GetX() const {
    return _x;
}

double Vector3D::GetY() const {
    return _y;
}

double Vector3D::GetZ() const {
    return _z;
}


double Vector3D::GetX() {
    return static_cast<const Vector3D&>(*this).GetX();
}

double Vector3D::GetY() {
    return static_cast<const Vector3D&>(*this).GetY();
}

double Vector3D::GetZ() {
    return static_cast<const Vector3D&>(*this).GetZ();
}


double Vector3D::GetLength() const {
    return std::sqrt(GetLengthSquared());
}

double Vector3D::GetLength() {
    return static_cast<const Vector3D&>(*this).GetLength();
}

double Vector3D::GetLengthSquared() const {
    double a1 = GetX();
    double a2 = GetY();
    double a3 = GetZ();
    if(Math::IsEqual(a1, 0.0) && Math::IsEqual(a2, 0.0) && Math::IsEqual(a3, 0.0)) return 0.0;
    return (a1 * a1 + a2 * a2 + a3 * a3);
}

double Vector3D::GetLengthSquared() {
    return static_cast<const Vector3D&>(*this).GetLengthSquared();
}


Vector3D Vector3D::CrossProduct(const Vector3D& b) {
    return CrossProduct(*this, b);
}

Vector3D Vector3D::CrossProduct(const Vector3D& a, const Vector3D& b) {
    double a1 = a.GetX();
    double a2 = a.GetY();
    double a3 = a.GetZ();

    double b1 = b.GetX();
    double b2 = b.GetY();
    double b3 = b.GetZ();

    //Gross, but fast.
    return Vector3D(a2 * b3 - a3 * b2, a3 * b1 - a1 * b3, a1 * b2 - a2 * b1);
}


double Vector3D::GetAngleFrom(const Vector3D& b) {
    return GetAngleFrom(b, *this);
}

double Vector3D::GetAngleFrom(const Vector3D& b, const Vector3D& a) {
    double b_length = b.GetLength();
    double a_length = a.GetLength();
    assert(Math::IsEqual(a_length, 0.0) == false && Math::IsEqual(b_length, 0.0) == false);
    if(Math::IsEqual(a_length, 0.0) || Math::IsEqual(b_length, 0.0)) {
        throw Exception("Can not get the angle of a Null Vector.");
    }
    double dot_product = DotProduct(b, a);
    double length_product = a_length * b_length;
    double dot_product_over_length_product = dot_product / length_product;
    double arc_cosine = std::acos(dot_product_over_length_product);

    return arc_cosine;
}

double Vector3D::GetAngle() const {
    return _angle;
}

double Vector3D::GetAngle() {
    return static_cast<const Vector3D&>(*this).GetAngle();
}

double Vector3D::DotProduct(const Vector3D& b) {
    return DotProduct(*this, b);
}

double Vector3D::DotProduct(const Vector3D& a, const Vector3D& b) {
    double a1 = a.GetX();
    double a2 = a.GetY();
    double a3 = a.GetZ();

    double b1 = b.GetX();
    double b2 = b.GetY();
    double b3 = b.GetZ();

    return a1 * b1 + a2 * b2 + a3 * b3;
}

Vector3D Vector3D::Normalize() const {
    double a1 = GetX();
    double a2 = GetY();
    double a3 = GetZ();
    double length = GetLength();
    if(Math::IsEqual(length, 0.0)) {
        return Vector3D(0.0, 0.0, 0.0);
    }
    return Vector3D(a1 / length, a2 / length, a3 / length);
}

void Vector3D::Normalize(Vector3D& v) {
    double a1 = v.GetX();
    double a2 = v.GetY();
    double a3 = v.GetZ();
    double length = v.GetLength();
    if(Math::IsEqual(length, 0.0)) {
        return;
    }
    v.SetTerminal(a1 / length, a2 / length, a3 / length);
}

Vector4D Vector3D::GetHomogeneous() const {
    return Vector4D(_x, _y, _z, 1.0);
}

Vector4D Vector3D::GetHomogeneous() {
    return static_cast<const Vector3D&>(*this).GetHomogeneous();
}

Vector4D Vector3D::GetHomogeneous(double w) const {
    return Vector4D(_x / w, _y / w, _z / w, 1.0);
}

Vector4D Vector3D::GetHomogeneous(double w) {
    return static_cast<const Vector3D&>(*this).GetHomogeneous(w);
}

Vector3D Vector3D::GetProjection(const Vector3D& a, const Vector3D& b) {

    //See http://www.metanetsoftware.com/technique/tutorialA.html#appendixA
    //--= projection =--
    //
    // The formula for projecting vector a onto vector b is:
    //
    // proj.x = ( dp / (b.x*b.x + b.y*b.y) ) * b.x;
    // proj.y = ( dp / (b.x*b.x + b.y*b.y) ) * b.y;
    //
    // where dp is the dotprod of a and b: dp = (a.x*b.x + a.y*b.y)
    //
    // Note that the result is a vector; also, (b.x*b.x + b.y*b.y) is simply the length of b squared.
    //
    // If b is a unit vector, (b.x*b.x + b.y*b.y) = 1, and thus a projected onto b reduces to:
    //
    // proj.x = dp*b.x;
    // proj.y = dp*b.y;

    double dp = Vector3D::DotProduct(a, b);
    double b_length_squared = b.GetLengthSquared();
    double b_x = b.GetX();
    double b_y = b.GetY();
    double b_z = b.GetZ();
    double dp_over_b_length_squared = dp / b_length_squared;

    double x = dp_over_b_length_squared * b_x;
    double y = dp_over_b_length_squared * b_y;
    double z = dp_over_b_length_squared * b_z;

    if(a2de::Math::IsEqual(x, 0.0)) x = 0.0;
    if(a2de::Math::IsEqual(y, 0.0)) y = 0.0;
    if(a2de::Math::IsEqual(z, 0.0)) z = 0.0;

    return Vector3D(x, y, z);
}

Vector3D Vector3D::GetProjection(const Vector3D& b) {
    return Vector3D::GetProjection(*this, b);
}

Vector3D Vector3D::GetProjectionOnXAxis() {
    return Vector3D::GetProjection(Vector3D(1.0, 0.0, 0.0));
}

Vector3D Vector3D::GetProjectionOnYAxis() {
    return Vector3D::GetProjection(Vector3D(0.0, 1.0, 0.0));
}

Vector3D Vector3D::GetProjectionOnZAxis() {
    return Vector3D::GetProjection(Vector3D(0.0, 0.0, 1.0));
}

double Vector3D::GetFacingAngle(const Vector3D& target, const Vector3D& source) {
    return GetFacingVector(target, source).GetAngle();
}

Vector3D Vector3D::GetFacingVector(const Vector3D& target, const Vector3D& source) {
    return target - source;
}

Vector3D& Vector3D::operator=(const Vector3D& rhs) {
    if(this == &rhs) return *this;
    this->SetTerminal(rhs.GetX(), rhs.GetY(), rhs.GetZ());
    return *this;
}

Vector3D& Vector3D::operator=(const Vector2D& rhs) {
    this->SetTerminal(rhs.GetX(), rhs.GetY(), 0.0);
    return *this;
}

Vector3D& Vector3D::operator=(const Vector4D& rhs) {
    this->SetTerminal(rhs.GetX(), rhs.GetY(), rhs.GetZ());
    return *this;
}

bool Vector3D::operator==(const Vector3D& rhs) {
    return ( (Math::IsEqual(this->GetX(), rhs.GetX())) && (Math::IsEqual(this->GetY(), rhs.GetY())) && (Math::IsEqual(this->GetZ(), rhs.GetZ())) );
}

bool Vector3D::operator!=(const Vector3D& rhs) {
    return !(*this == rhs);
}

Vector3D operator-(const Vector3D& lhs) {
    return Vector3D(-lhs.GetX(), -lhs.GetY(), -lhs.GetZ());
}

Vector3D operator+(double scalar_lhs, const Vector3D& v_rhs) {
    return (v_rhs + scalar_lhs);
}
Vector3D operator+(const Vector3D& v_lhs, double scalar_rhs) {
    return Vector3D(v_lhs.GetX() + scalar_rhs, v_lhs.GetY() + scalar_rhs, v_lhs.GetZ() + scalar_rhs);
}

Vector3D operator-(double scalar_lhs, const Vector3D& v_rhs) {
    return v_rhs + scalar_lhs;
}
Vector3D operator-(const Vector3D& v_lhs, double scalar_rhs) {
    return Vector3D(v_lhs.GetX() - scalar_rhs, v_lhs.GetY() + scalar_rhs, v_lhs.GetZ() - scalar_rhs);
}

Vector3D operator*(const Vector3D& v_lhs, double scalar_rhs) {
    return Vector3D(v_lhs.GetX() * scalar_rhs, v_lhs.GetY() * scalar_rhs, v_lhs.GetZ() * scalar_rhs);
}
Vector3D operator*(double scalar_lhs, const Vector3D& v_rhs) {
    return v_rhs + scalar_lhs;
}

Vector3D operator/(const Vector3D& v_lhs, double scalar_rhs) {
    assert(Math::IsEqual(scalar_rhs, 0.0) == false);
    return Vector3D(v_lhs.GetX() / scalar_rhs, v_lhs.GetY() / scalar_rhs, v_lhs.GetZ() / scalar_rhs);
}
Vector3D operator/(double scalar_lhs, const Vector3D& v_rhs) {
    return v_rhs / scalar_lhs;
}

Vector3D& Vector3D::operator+=(double scalar) {
    SetTerminal(GetX() + scalar, GetY() + scalar, GetZ() + scalar);
    return *this;
}
Vector3D& Vector3D::operator-=(double scalar) {
    SetTerminal(GetX() - scalar, GetY() - scalar, GetZ() - scalar);
    return *this;
}
Vector3D& Vector3D::operator*=(double scalar) {
    SetTerminal(GetX() * scalar, GetY() * scalar, GetZ() * scalar);
    return *this;
}
Vector3D& Vector3D::operator/=(double scalar) {
    assert(Math::IsEqual(scalar, 0.0) == false);
    SetTerminal(GetX() / scalar, GetY() / scalar, GetZ() / scalar);
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const {
    return Vector3D(this->GetX() + rhs.GetX(), this->GetY() + rhs.GetY(), this->GetZ() + rhs.GetZ());
}
Vector3D Vector3D::operator+(const Vector3D& rhs) {
    return static_cast<const Vector3D&>(*this).operator+(rhs);
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const {
    return Vector3D(this->GetX() - rhs.GetX(), this->GetY() - rhs.GetY(), this->GetZ() - rhs.GetZ());
}
Vector3D Vector3D::operator-(const Vector3D& rhs) {
    return static_cast<const Vector3D&>(*this).operator-(rhs);
}
Vector3D Vector3D::operator-() {
    return Vector3D(-GetX(), -GetY(), -GetZ());
}

Vector3D Vector3D::operator*(const Vector3D& rhs) const {
    return Vector3D(this->GetX() * rhs.GetX(), this->GetY() * rhs.GetY(), this->GetZ() * rhs.GetZ());
}
Vector3D Vector3D::operator*(const Vector3D& rhs) {
    return static_cast<const Vector3D&>(*this).operator*(rhs);
}

Vector3D Vector3D::operator/(const Vector3D& rhs) const {
    return Vector3D(this->GetX() / rhs.GetX(), this->GetY() / rhs.GetY(), this->GetZ() / rhs.GetZ());
}
Vector3D Vector3D::operator/(const Vector3D& rhs) {
    return static_cast<const Vector3D&>(*this).operator/(rhs);
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
    this->SetTerminal(this->GetX() + rhs.GetX(), this->GetY() + rhs.GetY(), this->GetZ() + rhs.GetZ());
    return *this;
}
Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
    this->SetTerminal(this->GetX() - rhs.GetX(), this->GetY() - rhs.GetY(), this->GetZ() - rhs.GetZ());
    return *this;
}
Vector3D& Vector3D::operator*=(const Vector3D& rhs) {
    this->SetTerminal(this->GetX() * rhs.GetX(), this->GetY() * rhs.GetY(), this->GetZ() * rhs.GetZ());
    return *this;
}
Vector3D& Vector3D::operator/=(const Vector3D& rhs) {
    this->SetTerminal(this->GetX() / rhs.GetX(), this->GetY() / rhs.GetY(), this->GetZ() / rhs.GetZ());
    return *this;
}


/************************************************************************/
/*  PROTECTED                                                           */
/************************************************************************/


void Vector3D::SetX(double x) {
    SetTerminal(x, GetY(), GetZ());
}

void Vector3D::SetY(double y) {
    SetTerminal(GetX(), y, GetZ());
}

void Vector3D::SetZ(double z) {
    SetTerminal(GetX(), GetY(), z);
}

void Vector3D::SetTerminal(double x, double y, double z) {
    _x = x;
    _y = y;
    _z = z;
    CalculateAngle();
}

void Vector3D::CalculateAngle() {
    double xn = GetX() / GetLength();
    double yn = GetY() / GetLength();
    double zn = GetZ() / GetLength();

    _angle = acos(xn * 1.0 + yn * 0.0 + zn * 0.0);
}


A2DE_END