/**************************************************************************************************
// file:	Engine\Math\CPoint.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the point class
 **************************************************************************************************/
#include "CPoint.h"

#include <cassert>
#include <cmath>
#include "MiscMath.h"

#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"
#include "CVector2D.h"


#include "../a2de_exceptions.h"

A2DE_BEGIN

Point::Point() : Shape(0.0, 0.0) {
    _type = Shape::SHAPETYPE_POINT;
    CalculateArea();
}

Point::Point(double x, double y) : Shape(x, y) {
    _type = Shape::SHAPETYPE_POINT;
    CalculateArea();
}

Point::Point(double x, double y, const a2de::Color& color) : Shape(x, y, 0, 0, color, false) {
    _type = Shape::SHAPETYPE_POINT;
    CalculateArea();
}

Point::Point(const Point& point) : Shape(point) {
    _type = Shape::SHAPETYPE_POINT;
    CalculateArea();
}

Point::Point(const Vector2D& position, const a2de::Color& color) : Shape(position, 0, 0, color, false) {
    _type = Shape::SHAPETYPE_POINT;
    CalculateArea();
}

Point::Point(const Vector2D& position) : Shape(position) {
    _type = Shape::SHAPETYPE_POINT;
    CalculateArea();
}

Point::~Point() { }


void Point::SetX(double x) {
    SetPosition(x, GetY());
}

void Point::SetY(double y) {
    SetPosition(GetX(), y);
}

void Point::SetPosition(double x, double y) {
    SetPosition(Vector2D(x, y));
}

void Point::SetPosition(const Vector2D& position) {
    Shape::SetPosition(position);
}

double Point::GetDistance(const Line& line) const {
    return line.GetDistance(*this);
}

double Point::GetDistance(const Point& point) const {
    return GetDistance(*this, point);
}

double Point::GetDistance(const Point& one, const Point& two) {
    return GetDistance(one.GetPosition(), two.GetPosition());
}

double Point::GetDistance(const Vector2D& one, const Vector2D& two) {
    return GetDistance(one.GetX(), one.GetY(), two.GetX(), two.GetY());
}

double Point::GetDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt(GetDistanceSquared(x1, y1, x2, y2));
}
double Point::GetDistanceSquared(const Point& point) {
    return GetDistanceSquared(*this, point);
}
double Point::GetDistanceSquared(double x1, double y1, double x2, double y2) {
    double xDiff = x2 - x1;
    double yDiff = y2 - y1;
    return (xDiff * xDiff + yDiff * yDiff);
}
double Point::GetDistanceSquared(const Point& one, const Point& two) {
    return GetDistanceSquared(one.GetPosition(), two.GetPosition());
}

double Point::GetDistanceSquared(const Vector2D& one, const Vector2D& two) {
    return GetDistanceSquared(one.GetX(), one.GetY(), two.GetX(), two.GetY());
}

bool Point::IsOnLine(const Line& line) const {
    return (GetDistance(line) <= 0.0001);
}

Point& Point::operator=(const Point& rhs) {
    if(this == &rhs) return *this;
    Shape::operator=(rhs);
    return *this;
}

bool Point::operator==(const Point& rhs) const {
    return (Math::IsEqual(this->GetX(), rhs.GetX()) && Math::IsEqual(this->GetY(), rhs.GetY()));
}

bool Point::operator!=(const Point& rhs) const {
    return !(*this == rhs);
}

Point Point::operator+(const Point& rhs) {
    double xP = this->GetX();
    double yP = this->GetY();
    double xR = rhs.GetX();
    double yR = rhs.GetY();

    return Point(xP + xR, yP + yR);
}
Point Point::operator-(const Point& rhs) {
    double xP = this->GetX();
    double yP = this->GetY();
    double xR = rhs.GetX();
    double yR = rhs.GetY();

    return Point(xP - xR, yP - yR);
}
Point Point::operator*(const Point& rhs) {
    double xP = this->GetX();
    double yP = this->GetY();
    double xR = rhs.GetX();
    double yR = rhs.GetY();

    return Point(xP * xR, yP * yR);
}
Point Point::operator/(const Point& rhs) {
    double xP = this->GetX();
    double yP = this->GetY();
    double xR = rhs.GetX();
    double yR = rhs.GetY();

    assert(xR != 0 || yR != 0);
    return Point(xP / xR, yP / yR);
}
Point Point::operator+(double scalar) {
    double xP = this->GetX();
    double yP = this->GetY();

    return Point(xP + scalar, yP + scalar);
}
Point Point::operator-(double scalar) {
    double xP = this->GetX();
    double yP = this->GetY();

    return Point(xP - scalar, yP - scalar);
}
Point Point::operator*(double scalar) {
    double xP = this->GetX();
    double yP = this->GetY();

    return Point(xP * scalar, yP * scalar);
}
Point Point::operator/(double scalar) {
    assert(scalar != 0);

    double xP = this->GetX();
    double yP = this->GetY();

    return Point(xP / scalar, yP / scalar);
}

Point& Point::operator+=(const Point& rhs) {    
    double x = this->GetX() + rhs.GetX();
    double y = this->GetY() + rhs.GetY();

    this->SetPosition(x, y);

    return *this;
}
Point& Point::operator-=(const Point& rhs) {
    double x = this->GetX() - rhs.GetX();
    double y = this->GetY() - rhs.GetY();

    this->SetPosition(x, y);

    return *this;
}
Point& Point::operator*=(const Point& rhs) {
    double x = this->GetX() * rhs.GetX();
    double y = this->GetY() * rhs.GetY();

    this->SetPosition(x, y);

    return *this;
}
Point& Point::operator/=(const Point& rhs) {
    double xR = rhs.GetX();
    double yR = rhs.GetY();

    assert(xR != 0 || yR != 0);

    double xP = this->GetX();
    double yP = this->GetY();
    
    double x = xP / xR;
    double y = yP / yR;

    this->SetPosition(x, y);
    return *this;
}

Point& Point::operator+=(double scalar) {
    double xP = this->GetX();
    double yP = this->GetY();

    double x = xP + scalar;
    double y = yP + scalar;

    this->SetPosition(x, y);
    return *this;
}
Point& Point::operator-=(double scalar) {
    double xP = this->GetX();
    double yP = this->GetY();

    double x = xP - scalar;
    double y = yP - scalar;

    this->SetPosition(x, y);
    return *this;
}
Point& Point::operator*=(double scalar) {
    double xP = this->GetX();
    double yP = this->GetY();

    double x = xP * scalar;
    double y = yP * scalar;

    this->SetPosition(x, y);
    return *this;
}
Point& Point::operator/=(double scalar) {
    assert(scalar != 0);

    double xP = this->GetX();
    double yP = this->GetY();

    double x = xP / scalar;
    double y = yP / scalar;

    this->SetPosition(x, y);
    return *this;
}

void Point::Draw(BITMAP* dest, const a2de::Color& color, bool /*filled*/) {
    putpixel(dest, a2de::Math::ToScreenScale(this->GetX()), a2de::Math::ToScreenScale(this->GetY()), color);
}

void Point::CalculateArea() { /* DO NOTHING */ }
void Point::SetDimensions(double /*width*/, double /*height*/) { /* DO NOTHING */ }
void Point::SetDimensions(const Vector2D& /*dimensions*/) { /* DO NOTHING */ }
void Point::SetWidth(double /*width*/) { /* DO NOTHING */ }
void Point::SetHeight(double /*height*/) { /* DO NOTHING */ }

bool Point::Intersects(const Vector2D& position) const {
    return (this->GetPosition() == position);
}

bool Point::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Point::Intersects(const Point& point) const {
    return Intersects(point.GetPosition());
}

bool Point::Intersects(const Line& line) const {
    return line.Intersects(*this);
}

bool Point::Intersects(const Rectangle& rectangle) const {

    double rLeft = rectangle.GetX();
    double pWidth = this->GetWidth();
    double pRight = this->GetX() + pWidth;
    if(rLeft > pRight) return false;

    double rWidth = rectangle.GetWidth();
    double rRight = rLeft + rWidth;
    double pLeft = pRight - pWidth;
    if(rRight < pLeft) return false;

    double rTop = rectangle.GetY();
    double pHeight = this->GetHeight();
    double pBottom = this->GetY() + pHeight;
    if(rTop > pBottom) return false;

    double rHeight = rectangle.GetHeight();
    double rBottom = rTop + rHeight;
    double pTop = pBottom - pHeight;
    if(rBottom < pTop) return false;

    return true;
}
bool Point::Intersects(const Circle& circle) const {
    return (GetDistance(GetX(), GetY(), circle.GetPosition().GetX(), circle.GetPosition().GetY()) <= circle.GetRadius());
}
bool Point::Intersects(const Ellipse& ellipse) const {
    bool resultX = (GetDistance(Point(ellipse.GetPosition().GetX(), ellipse.GetPosition().GetY())) <= ellipse.GetRadiusWidth());
    bool resultY = (GetDistance(Point(ellipse.GetPosition().GetX(), ellipse.GetPosition().GetY())) <= ellipse.GetRadiusHeight());
    return (resultX && resultY);
}
bool Point::Intersects(const Triangle& triangle) const {

    //Distance: this from center
    Point tCenter(triangle.GetPosition().GetX(), triangle.GetPosition().GetY());
    double distCtoP = GetDistance(tCenter);

    //Distance: center to sides
    double distCtoAB = tCenter.GetDistance(triangle.GetLineAB());
    double distCtoBC = tCenter.GetDistance(triangle.GetLineBC());
    double distCtoCA = tCenter.GetDistance(triangle.GetLineCA());

    //Distance: this from points
    double distPtoA = GetDistance(triangle.GetPointA());
    double distPtoB = GetDistance(triangle.GetPointB());
    double distPtoC = GetDistance(triangle.GetPointC());

    bool resultAB = (distCtoP <= distCtoAB);
    bool resultBC = (distCtoP <= distCtoBC);
    bool resultCA = (distCtoP <= distCtoCA);
    bool resultA = (distPtoA <= distCtoP);
    bool resultB = (distPtoB <= distCtoP);
    bool resultC = (distPtoC <= distCtoP);

    return (resultAB && resultBC && resultCA && resultA && resultB && resultC);
}

bool Point::Intersects(const Arc& /*arc*/) const {
    return false;
}
bool Point::Intersects(const Polygon& /*polygon*/) const {
    return false;
}
bool Point::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Point::Intersects(const Sector& sector) const {
    return sector.Intersects(*this);
}


bool Point::Contains(const Shape& shape) const {
    return this->Contains(shape);
}

bool Point::Contains(const Point& point) const {
    return (*this) == point;
}

bool Point::Contains(const Line& /*line*/) const {
    return false;
}

bool Point::Contains(const Rectangle& /*rectangle*/) const {
    return false;
}

bool Point::Contains(const Circle& /*circle*/) const {
    return false;
}

bool Point::Contains(const Ellipse& /*ellipse*/) const {
    return false;
}

bool Point::Contains(const Triangle& /*triangle*/) const {
    return false;
}

bool Point::Contains(const Arc& /*arc*/) const {
    return false;
}

bool Point::Contains(const Polygon& /*polygon*/) const {
    return false;
}

bool Point::Contains(const Spline& /*spline*/) const {
    return false;
}

bool Point::Contains(const Sector& /*sector*/) const {
    return false;
}


A2DE_END