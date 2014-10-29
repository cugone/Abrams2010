/**************************************************************************************************
// file:	Engine\Math\CEllipse.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the ellipse class
 **************************************************************************************************/
#include "CEllipse.h"

#include <cassert>
#include <allegro/gfx.h>
#include "MathConstants.h"
#include "MiscMath.h"

#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"


A2DE_BEGIN

Ellipse::Ellipse(const Point& center, double width, double height, const a2de::Color& color, bool filled)
: Shape(center.GetX(), center.GetY(), ((width < 0) ? 0 : width), ((height < 0) ? 0 : height), color, filled) {
    _type = Shape::SHAPETYPE_ELLIPSE;
    _radii = Vector2D(_half_extents.GetX(), _half_extents.GetY());
    CalculateFoci();
    CalculateArea();
    CalculateCircumference();
}
Ellipse::Ellipse(int x, int y, double width, double height, const a2de::Color& color, bool filled)
: Shape(x, y, ((width < 0) ? 0 : width), ((height < 0) ? 0 : height), color, filled) {
    _type = Shape::SHAPETYPE_ELLIPSE;
    _radii = Vector2D(width, height);
    CalculateFoci();
    CalculateArea();
    CalculateCircumference();
}
Ellipse::Ellipse(const Ellipse& ellipse) : Shape(ellipse) {
    _type = Shape::SHAPETYPE_ELLIPSE;
    _radii = ellipse._half_extents;
    CalculateFoci();
    CalculateArea();
    CalculateCircumference();
}
Ellipse::~Ellipse() {

}

void Ellipse::SetDimensions(double width, double height) {
    SetDimensions(Vector2D(width, height));
}

void Ellipse::SetDimensions(const Vector2D& dimensions) {
    Shape::SetDimensions(dimensions);
    _radii = Vector2D(dimensions.GetX(), dimensions.GetY());
    CalculateFoci();
    CalculateArea();
    CalculateCircumference();
}

double Ellipse::GetCircumference() const {
    return _circumference;
}
void Ellipse::SetWidth(double width) {
    SetDimensions(width, _half_extents.GetY());
}
void Ellipse::SetHeight(double height) {
    SetDimensions(_half_extents.GetX(), height);
}
void Ellipse::SetX(double x) {
    SetPosition(x, GetY());
}
void Ellipse::SetY(double y) {
    SetPosition(GetX(), y);
}

void Ellipse::SetPosition(double x, double y) {
    SetPosition(Vector2D(x, y));
}

void Ellipse::SetPosition(const Vector2D& position) {
    Shape::SetPosition(position);
}

bool Ellipse::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Ellipse::Intersects(const Triangle& /*triangle*/) const {
    return false;
    //Line tlAB(triangle.GetLineAB());
    //Line tlBC(triangle.GetLineBC());
    //Line tlCA(triangle.GetLineCA());
    //bool resultAB = tlAB.Intersects(*this);
    //bool resultBC = tlBC.Intersects(*this);
    //bool resultCA = tlCA.Intersects(*this);
    //bool isInside = Intersects(Point(triangle.GetCenter()));
    //return (isInside || resultAB || resultBC || resultCA);
}
bool Ellipse::Intersects(const Ellipse& /*ellipse*/) const {
    return false;
    //return Point(this->GetCenter().GetX(), this->GetCenter().GetY()).GetDistance(Point(ellipse.GetCenter().GetX(), ellipse.GetCenter().GetY())) <= this->_radii.GetX() + ellipse._radii.GetX() &&
    //       Point(this->GetCenter().GetX(), this->GetCenter().GetY()).GetDistance(Point(ellipse.GetCenter().GetX(), ellipse.GetCenter().GetY())) <= this->_radii.GetY() + ellipse._radii.GetY();
}
bool Ellipse::Intersects(const Circle& /*circle*/) const {
    return false;
    //return Point(this->GetCenter().GetX(), this->GetCenter().GetY()).GetDistance(Point(circle.GetCenter().GetX(), circle.GetCenter().GetY())) <= this->_radii.GetX() + circle.GetRadius() &&
    //       Point(this->GetCenter().GetX(), this->GetCenter().GetY()).GetDistance(Point(circle.GetCenter().GetX(), circle.GetCenter().GetY())) <= this->_radii.GetY() + circle.GetRadius();
}
bool Ellipse::Intersects(const Rectangle& /*rectangle*/) const {
    return false;
    //double distTop = Point(GetCenter().GetX(),GetCenter().GetY()).GetDistance(rectangle.GetTop());
    //double distLeft = Point(GetCenter().GetX(),GetCenter().GetY()).GetDistance(rectangle.GetLeft());
    //double distRight = Point(GetCenter().GetX(),GetCenter().GetY()).GetDistance(rectangle.GetRight());
    //double distBottom = Point(GetCenter().GetX(),GetCenter().GetY()).GetDistance(rectangle.GetBottom());
    //double radiusWidth = GetRadiusWidth();
    //double radiusHeight = GetRadiusHeight();

    //bool resultTop = (distTop < radiusWidth && distTop < radiusHeight);
    //bool resultBottom = (distBottom < radiusWidth && distBottom < radiusHeight);
    //bool resultLeft = (distLeft < radiusWidth && distLeft < radiusHeight);
    //bool resultRight = (distRight < radiusWidth && distRight < radiusHeight);
    //bool isInside = Point(GetCenter().GetX(),GetCenter().GetY()).Intersects(rectangle);
    //return (isInside || resultTop || resultBottom || resultLeft || resultRight);
}
bool Ellipse::Intersects(const Point& /*point*/) const {
    return false;
    //return (Point(GetCenter().GetX(),GetCenter().GetY()).GetDistance(point) <= _radii.GetX() &&
    //        Point(GetCenter().GetX(),GetCenter().GetY()).GetDistance(point) <= _radii.GetY());
}
bool Ellipse::Intersects(const Line& line) const {
    return line.Intersects(*this);
}

bool Ellipse::Intersects(const Arc& /*arc*/) const {
    return false;
}

bool Ellipse::Intersects(const Polygon& /*polygon*/) const {
    return false;
}

bool Ellipse::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Ellipse::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Ellipse::Intersects(const Vector2D& position) const {

    double x = this->GetPosition().GetX();
    double y = this->GetPosition().GetY();
    double distance_squared = a2de::Point::GetDistanceSquared(x, y, position.GetX(), position.GetY());
    double rX_squared = _radii.GetX();
    rX_squared *= rX_squared;
    double rY_squared = _radii.GetY();
    rY_squared *= rY_squared;

    return (distance_squared <= rX_squared && distance_squared <= rY_squared);

}

bool Ellipse::IsTangent(const Line& /*line*/) {
    return false;
    //return (Math::IsEqual(Point(GetCenter().GetX(),GetCenter().GetY()).GetDistance(line), _radii.GetX()) ||
    //        Math::IsEqual(Point(GetCenter().GetX(),GetCenter().GetY()).GetDistance(line), _radii.GetY()));
}

const Vector2D& Ellipse::GetFocusA() const {
    return _focusA;
}
Vector2D& Ellipse::GetFocusA() {
    return const_cast<Vector2D&>(static_cast<const Ellipse&>(*this).GetFocusA());
}

const Vector2D& Ellipse::GetFocusB() const {
    return _focusB;
}

Vector2D& Ellipse::GetFocusB() {
    return const_cast<Vector2D&>(static_cast<const Ellipse&>(*this).GetFocusB());
}

void Ellipse::CalculateArea() {
    _area = Math::A2DE_PI * _radii.GetX() * _radii.GetY();
}

void Ellipse::CalculateCircumference() {

    //C = 2 * pi * (sqrt(0.5 * (a^2 + b^2)) / 2.0 )
    double a = _half_extents.GetX();
    double b = _half_extents.GetY();
    _circumference = 2 * Math::A2DE_PI * (std::sqrt(0.5 * ((a * a) + (b * b))) / 2.0);

}

void Ellipse::CalculateFoci() {
    if(IsVertical()) {
        _focusA = Vector2D(GetPosition().GetX(), GetPosition().GetY() + (_radii.GetY() / 2));
        _focusB = Vector2D(GetPosition().GetX(), GetPosition().GetY() - (_radii.GetY() / 2));
    } else if(IsHorizontal()) {
        _focusA = Vector2D(GetPosition().GetX() - (_radii.GetX() / 2), GetPosition().GetY());
        _focusB = Vector2D(GetPosition().GetX() + (_radii.GetX() / 2), GetPosition().GetY());
    }
}

void Ellipse::Draw(BITMAP* dest, const a2de::Color& color, bool filled) {
    if(filled) {
        ellipsefill(dest, a2de::Math::ToScreenScale(GetX()), a2de::Math::ToScreenScale(GetY()), a2de::Math::ToScreenScale(GetWidth()), a2de::Math::ToScreenScale(GetHeight()), color);
    } else {
        ellipse(dest, a2de::Math::ToScreenScale(GetX()), a2de::Math::ToScreenScale(GetY()), a2de::Math::ToScreenScale(GetWidth()), a2de::Math::ToScreenScale(GetHeight()), color);
    }
}

double Ellipse::GetRadiusWidth() const {
    return _radii.GetX();
}

double Ellipse::GetRadiusWidth() {
    return static_cast<const Ellipse&>(*this).GetRadiusWidth();
}

double Ellipse::GetRadiusHeight() const {
    return _radii.GetY();
}

double Ellipse::GetRadiusHeight() {
    return static_cast<const Ellipse&>(*this).GetRadiusHeight();
}

bool Ellipse::IsHorizontal() const {
    return (_radii.GetX() > _radii.GetY());
}

bool Ellipse::IsHorizontal() {
    return static_cast<const Ellipse&>(*this).IsHorizontal();
}

bool Ellipse::IsVertical() const {
    return (_radii.GetX() < _radii.GetY());
}

bool Ellipse::IsVertical() {
    return static_cast<const Ellipse&>(*this).IsVertical();
}

Ellipse& Ellipse::operator=(const Ellipse& rhs) {
    if(this == &rhs) return *this;
    Shape::operator=(rhs);
    this->_radii = Vector2D(rhs._half_extents.GetX() / 2, rhs._half_extents.GetY() / 2);
    this->_color = rhs._color;
    this->_filled = rhs._filled;
    CalculateFoci();
    CalculateArea();
    CalculateCircumference();
    return *this;
}


A2DE_END