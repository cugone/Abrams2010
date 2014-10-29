/**************************************************************************************************
// file:	Engine\Math\CLine.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the line class
 **************************************************************************************************/
#include "CLine.h"


#include "CPoint.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"



#include <cmath>
#include <algorithm>
#include "../Math/MiscMath.h"
#include "../a2de_exceptions.h"

A2DE_BEGIN

Line::Line()
    : Shape(),
    _extent_one(a2de::Vector2D()),
    _extent_two(a2de::Vector2D()),
     _slope(),
    _length_squared(0.0) {
    _type = Shape::SHAPETYPE_LINE;
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}
Line::Line(double x1, double y1, double x2, double y2)
    : Shape(0.0, 0.0, 0, 0, a2de::Color::BLACK(), false),
    _extent_one(a2de::Vector2D(x1, y1)),
    _extent_two(a2de::Vector2D(x2, y2)),
    _slope(),
    _length_squared(0.0) {
    _type = Shape::SHAPETYPE_LINE;
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}

Line::Line(double x1, double y1, double x2, double y2, const a2de::Color& color)
    : Shape(0.0, 0.0, 0, 0, color, false),
    _extent_one(a2de::Vector2D(x1, y1)),
    _extent_two(a2de::Vector2D(x2, y2)),
    _slope(),
    _length_squared(0.0) {
    _type = Shape::SHAPETYPE_LINE;
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}

Line::Line(const Point& one, const Point& two)
    : Shape(0.0, 0.0, 0, 0, a2de::Color::BLACK(), false),
    _extent_one(one.GetPosition()),
    _extent_two(two.GetPosition()),
    _slope(),
    _length_squared(0.0) {
    _type = Shape::SHAPETYPE_LINE;
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}

Line::Line(const Point& one, const Point& two, const a2de::Color& color)
    : Shape(0.0, 0.0, 0, 0, color, false),
    _extent_one(one.GetPosition()),
    _extent_two(two.GetPosition()),
    _slope(),
    _length_squared(0.0) {
    _type = Shape::SHAPETYPE_LINE;
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}

Line::Line(const Line& line)
    : Shape(line),
    _extent_one(line.GetPointOne()),
    _extent_two(line.GetPointTwo()),
    _slope(),
    _length_squared(0.0) {
    _type = Shape::SHAPETYPE_LINE;
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}

Line::Line(const Vector2D& one, const Vector2D& two)
    : Shape(0.0, 0.0, 0, 0, a2de::Color::BLACK(), false),
    _extent_one(one),
    _extent_two(two),
    _slope(),
    _length_squared(0.0) {
    _type = Shape::SHAPETYPE_LINE;
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}

Line::Line(const Vector2D& one, const Vector2D& two, const a2de::Color& color)
    : Shape(0.0, 0.0, 0, 0, color, false),
    _extent_one(one),
    _extent_two(two),
    _slope(),
    _length_squared(0.0) {
    _type = Shape::SHAPETYPE_LINE;
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}

Line::~Line() { /* DO NOTHING */ }

const Vector2D& Line::GetPointOne() const {
    return _extent_one;
}

Vector2D& Line::GetPointOne() {
    return const_cast<Vector2D&>(static_cast<const Line&>(*this).GetPointOne());
}

const Vector2D& Line::GetPointTwo() const {
    return _extent_two;
}

Vector2D& Line::GetPointTwo() {
    return const_cast<Vector2D&>(static_cast<const Line&>(*this).GetPointTwo());
}

double Line::GetLength() const {
    return std::sqrt(_length_squared);
}

double Line::GetLength() {
    return static_cast<const Line&>(*this).GetLength();
}

double Line::GetLengthSquared() const {
    return _length_squared;
}

double Line::GetLengthSquared() {
    return static_cast<const Line&>(*this).GetLengthSquared();
}
const Vector2D& Line::GetSlope() const {
    return _slope;
}

Vector2D& Line::GetSlope() {
    return const_cast<Vector2D&>(static_cast<const Line&>(*this).GetSlope());
}

void Line::SetPointOne(double x, double y) {
    _extent_one = Vector2D(x, y);
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}

void Line::SetPointTwo(double x, double y) {
    _extent_two = Vector2D(x, y);
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}

void Line::SetPointOne(const Vector2D& point) {
    if(GetPointOne() == point) return;
    SetPointOne(point);
}

void Line::SetPointTwo(const Vector2D& point) {
    if(GetPointTwo() == point) return;
    SetPointTwo(point);
}

Line& Line::operator=(const Line& rhs) {
    if(this == &rhs) return *this;
    Shape::operator=(rhs);
    this->_extent_one = rhs._extent_one;
    this->_extent_two = rhs._extent_two;
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
    return *this;
}

bool Line::operator==(const Line& rhs) const {
    if(this == &rhs) return true;
    //A line is equal to another if:
    //the both first points are equal AND
    //the both second points are equal.
    return (
            (this->_extent_one == rhs._extent_one) &&
            (this->_extent_two == rhs._extent_two)
           );
}

bool Line::operator!=(const Line& rhs) const {
    return !(*this == rhs);
}
bool Line::operator<(const Line& rhs) const {
    return ((*this) != rhs) && (this->GetLengthSquared() < rhs.GetLengthSquared());
}
bool Line::operator>(const Line& rhs) const {
    return (rhs < *this);
}
bool Line::operator<=(const Line& rhs) const {
    return !(rhs < *this);
}
bool Line::operator>=(const Line& rhs) const {
    return !(*this < rhs);
}

void Line::Draw(BITMAP* dest, const a2de::Color& color, bool /*filled*/) {
    if(dest == nullptr) return;
    line(dest, a2de::Math::ToScreenScale(_extent_one.GetX()), a2de::Math::ToScreenScale(_extent_one.GetY()), a2de::Math::ToScreenScale(_extent_two.GetX()), a2de::Math::ToScreenScale(_extent_two.GetY()), color);
}

Line::LINEINTERSECTIONTYPE Line::Intersects(const Line& line, Point& at) const {
    //Points to the same line.
    if(this == &line) return Line::COLINEAR;

    Line::LINEINTERSECTIONTYPE result = Line::NONE;
    double ua_t = (line.GetPointTwo().GetX() - line.GetPointOne().GetX()) * (this->GetPointOne().GetY() - line.GetPointOne().GetY()) - (line.GetPointTwo().GetY() - line.GetPointOne().GetY()) * (this->GetPointOne().GetX() - line.GetPointOne().GetX());

    double ub_t = (this->GetPointTwo().GetX() - this->GetPointOne().GetX()) *
        (this->GetPointOne().GetY() - line.GetPointOne().GetY()) -
        (this->GetPointTwo().GetY() - this->GetPointOne().GetY()) *
        (this->GetPointOne().GetX() - line.GetPointOne().GetX());

    double u_b  = (line.GetPointTwo().GetY() - line.GetPointOne().GetY()) * (this->GetPointTwo().GetX() - this->GetPointOne().GetX()) - (line.GetPointTwo().GetX() - line.GetPointOne().GetX()) * (this->GetPointTwo().GetY() - this->GetPointOne().GetY());

    if ( u_b != 0.0 ) {
        double ua = ua_t / u_b;
        double ub = ub_t / u_b;

        if ( 0.0 <= ua && ua <= 1.0 && 0.0 <= ub && ub <= 1.0 ) {
            at = Point(this->GetPointOne().GetX() + ua * (this->GetPointTwo().GetX() - this->GetPointOne().GetX()),
                this->GetPointOne().GetY() + ua * (this->GetPointTwo().GetY() - this->GetPointOne().GetY()));
            result = Line::ONE;
        } else {
            result = Line::NONE;
        }
    } else {
        if ( ua_t == 0.0 || ub_t == 0.0 ) {
            result = Line::COLINEAR;
        } else {
            result = Line::PARALLEL;
        }
    }

    return result;

}

bool Line::IsVertical() const {
    return Math::IsEqual(_slope.GetX(), 0.0);
}

bool Line::IsHorizontal() const {
    if(IsVertical()) return false;
    return Math::IsEqual(_slope.GetY(), 0.0);
}

bool Line::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Line::Intersects(const Point& point) const {
    return this->Contains(point);
}
bool Line::Intersects(const Line& line) const {
    Point at(0.0, 0.0);
    Line::LINEINTERSECTIONTYPE resultT = this->Intersects(line, at);
    bool result = false;
    switch(resultT) {
    case NONE:
    case PARALLEL:
        result = false;
        break;
    case ONE:
    case COLINEAR:
        result = true;
        break;
    }
    return result;
}
bool Line::Intersects(const Rectangle& rectangle) const {

    if(this->IsVertical()) {
        double Xr = rectangle.GetX();
        double Xrw = rectangle.GetWidth();
        double Xl = _extent_one.GetX();
        if(Xr > Xl) return false;
        double Xrb = Xr + Xrw;
        if(Xrb < Xl) return false;
        return true;
    } else if(this->IsHorizontal()) {
        double Yr = rectangle.GetY();
        double Yrh = rectangle.GetHeight();
        double Yl = _extent_one.GetY();
        if(Yr > Yl) return false;
        double Yrb = Yr + Yrh;
        if(Yrb < Yl) return false;
        return true;
    }

    double eOne_x = _extent_one.GetX();
    double eOne_y = _extent_one.GetY();
    double eTwo_x = _extent_two.GetX();
    double eTwo_y = _extent_two.GetY();
    double rTop = rectangle.GetY();
    double rLeft = rectangle.GetX();
    double rRight = rLeft + rectangle.GetWidth();
    double rBottom = rTop + rectangle.GetHeight();

    bool point_one_result = eOne_x > rLeft && eOne_x < rRight && eOne_y > rTop && eOne_y < rBottom;
    bool point_two_result = eTwo_x > rLeft && eTwo_x < rRight && eTwo_y > rTop && eTwo_y < rBottom;
    if(point_one_result || point_two_result) return true;

    bool result = Intersects(rectangle.GetTop()) ||
                  Intersects(rectangle.GetLeft()) ||
                  Intersects(rectangle.GetRight()) ||
                  Intersects(rectangle.GetBottom());
    return result;
}
bool Line::Intersects(const Circle& circle) const {
    double r2 = circle.GetRadius();
    r2 *= r2;
    bool eOne_result = ((_extent_one - circle.GetPosition()).GetLengthSquared() < r2);
    bool eTwo_result = ((_extent_two - circle.GetPosition()).GetLengthSquared() < r2);
    if(eOne_result) return true;
    if(eTwo_result) return true;
    return this->GetDistance(Point(circle.GetPosition())) <= circle.GetRadius();
}
bool Line::Intersects(const Ellipse& ellipse) const {
    bool resultX = this->GetDistance(Point(ellipse.GetPosition())) <= ellipse.GetRadiusWidth();
    bool resultY = this->GetDistance(Point(ellipse.GetPosition())) <= ellipse.GetRadiusHeight();
    return (resultX && resultY);
}

bool Line::Intersects(const Triangle& /*triangle*/) const {
    return false;
    //bool resultAB = Intersects(triangle.GetLineAB());
    //bool resultBC = Intersects(triangle.GetLineBC());
    //bool resultCA = Intersects(triangle.GetLineCA());
    //bool isInside = Point(GetPointOne()).Intersects(triangle) || Point(GetPointTwo()).Intersects(triangle);
    //return (isInside || resultAB || resultBC || resultCA);
}

bool Line::Intersects(const Arc& /*arc*/) const {
    return false;
}

bool Line::Intersects(const Polygon& /*polygon*/) const {
    return false;
}

bool Line::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Line::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Line::Intersects(const Vector2D& position) const {
    return this->GetDistance(position) <= 0.0001;
}

double Line::GetDistance(const Vector2D& point) const {
    return std::sqrt(GetDistanceSquared(*this, point));
}

double Line::GetDistanceSquared(const Vector2D& point) const {
    return GetDistanceSquared(*this, point);
}

double Line::GetDistance(const Point& point) const {
    return this->GetDistance(point.GetPosition());
}

double Line::GetDistance(const Line& line, const Vector2D& point) {
    return std::sqrt(GetDistanceSquared(line, point));
}

double Line::GetDistanceSquared(const Line& line, const Vector2D& point) {

    //Taken from http://stackoverflow.com/a/1501725/421178

    Vector2D v = line.GetPointOne();
    Vector2D w = line.GetPointTwo();
    Vector2D w_minus_v = w - v;
    // Return minimum distance between line segment vw and point p
    const double l2 = w_minus_v.GetLengthSquared();  // i.e. |w-v|^2
    Vector2D p_minus_v = point - v;
    if (Math::IsEqual(l2, 0.0)) return p_minus_v.GetLengthSquared();   // v == w case
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line. 
    // It falls where t = [(p-v) . (w-v)] / ||w-v||^2
    const float t = Vector2D::DotProduct(p_minus_v, w_minus_v) / l2;
    if (t < 0.0) return p_minus_v.GetLengthSquared();       // Beyond the 'v' end of the segment
    else if (t > 1.0) return (point - w).GetLengthSquared();  // Beyond the 'w' end of the segment
    const Vector2D projection(v + (w_minus_v) * t);  // Projection falls on the segment
    return (point - projection).GetLengthSquared();
}

void Line::CalculateSlope() {
    //(y2 - y1) / (x2 - x1)

    double yDiff = (_extent_two.GetY() - _extent_one.GetY());
    double xDiff = (_extent_two.GetX() - _extent_one.GetX());
    
    _slope = Vector2D(xDiff, yDiff);
}

void Line::CalculateLengthSquared() {
    _length_squared = (_extent_two - _extent_one).GetLengthSquared();
}

void Line::CalculateArea() {
    _area = 0.0;
}

double Line::GetX() const {
    return _position.GetX();
}

double Line::GetX() {
    return const_cast<const Line&>(*this).GetX();
}

double Line::GetY() const {
    return _position.GetY();
}

double Line::GetY() {
    return const_cast<const Line&>(*this).GetY();
}

void Line::SetX(double x) { SetPosition(x, GetY()); }
void Line::SetY(double y) { SetPosition(GetX(), y); }
void Line::SetPosition(double x, double y) { SetPosition(Vector2D(x, y)); }
void Line::SetPosition(const Vector2D& position) {
    this->SetPointOne(GetPointOne().GetX() - position.GetX(), GetPointOne().GetY() - -position.GetY());
    this->SetPointTwo(GetPointTwo().GetX() - position.GetX(), GetPointTwo().GetY() - -position.GetY());
    CalculateLengthSquared();
    CalculateSlope();
    Shape::SetPosition(a2de::Vector2D(_extent_one.GetX() + _extent_two.GetX() / 2.0, _extent_one.GetY() + _extent_two.GetY() / 2.0));
}
void Line::SetDimensions(double /*width*/, double /*height*/) { /* DO NOTHING */}
void Line::SetDimensions(const Vector2D& /*dimensions*/) { /* DO NOTHING */ }
void Line::SetWidth(double /*width*/) { /* DO NOTHING */ };
void Line::SetHeight(double /*height*/) { /* DO NOTHING */};

a2de::Vector2D Line::GetPerpendicularSlope() const {
    return Vector2D(-_slope.GetY(), _slope.GetX());
}

a2de::Vector2D Line::GetPerpendicularSlope() {
    return static_cast<const a2de::Line&>(*this).GetPerpendicularSlope();
}

a2de::Vector2D Line::GetLeftNormal() const {
    a2de::Vector2D v(_extent_two - _extent_one);
    return v.GetLeftNormal();
}

a2de::Vector2D Line::GetLeftNormal() {
    return static_cast<const a2de::Line&>(*this).GetLeftNormal();
}

a2de::Vector2D Line::GetRightNormal() const {
    a2de::Vector2D v(_extent_two - _extent_one);
    return v.GetRightNormal();
}

a2de::Vector2D Line::GetRightNormal() {
    return static_cast<const a2de::Line&>(*this).GetRightNormal();
}


bool Line::Contains(const Shape& shape) const {
    return this->Contains(shape);
}

bool Line::Contains(const Point& point) const {
    return this->GetDistance(point) <= 0.0001;
}

bool Line::Contains(const Line& line) const {
    return (*this) == line;
}

bool Line::Contains(const Rectangle& /*rectangle*/) const {
    return false;
}

bool Line::Contains(const Circle& /*circle*/) const {
    return false;
}

bool Line::Contains(const Ellipse& /*ellipse*/) const {
    return false;
}

bool Line::Contains(const Triangle& /*triangle*/) const {
    return false;
}

bool Line::Contains(const Arc& /*arc*/) const {
    return false;
}

bool Line::Contains(const Polygon& /*polygon*/) const {
    return false;
}

bool Line::Contains(const Spline& /*spline*/) const {
    return false;
}

bool Line::Contains(const Sector& /*sector*/) const {
    return false;
}


A2DE_END