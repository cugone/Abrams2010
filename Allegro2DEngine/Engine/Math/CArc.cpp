/**************************************************************************************************
// file:	Engine\Math\CArc.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the arc class
 **************************************************************************************************/
#include "CArc.h"


#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"



#include "MathConstants.h"
#include "MiscMath.h"
#include "../a2de_exceptions.h"

A2DE_BEGIN

Arc::Arc(double x, double y, double startAngle, double endAngle, double radius, const a2de::Color& color, bool filled) : Shape(x, y, (radius < 0.0 ? 0.0 : radius), (radius < 0.0 ? 0.0 : radius), color, filled), _startAngle(0.0), _endAngle(0.0), _theta(0.0), _radius((radius < 0.0 ? 0.0 : radius)) {
    _type = Shape::SHAPETYPE_ARC;
    _radius = radius;
    SetAngles(startAngle, endAngle);
    CalculateLength();
    CalculateArea();
}

Arc::Arc(const Vector2D& position, double startAngle, double endAngle, double radius, const a2de::Color& color, bool filled) : Shape(position, (radius < 0.0 ? 0.0 : radius), (radius < 0.0 ? 0.0 : radius), color, filled), _startAngle(0.0), _endAngle(0.0), _theta(0.0), _radius((radius < 0.0 ? 0.0 : radius)) {
    _type = Shape::SHAPETYPE_ARC;
    _radius = radius;
    SetAngles(startAngle, endAngle);
    CalculateLength();
    CalculateArea();
}

Arc::Arc(const Arc& arc) : Shape(arc), _startAngle(arc._startAngle), _endAngle(arc._endAngle), _theta(arc._theta), _radius(arc._radius) {
    _type = Shape::SHAPETYPE_ARC;
    SetAngles(_startAngle, _endAngle);
    CalculateLength();
    CalculateArea();
}

Arc::~Arc() {
    /* DO NOTHING. ALL DE-INITIALIZATION DONE IN BASE CLASS */
}

double Arc::GetRadius() const {
    return _radius;
}

void Arc::SetRadius(double radius) {
    if(radius < 0.0) radius = 0.0;
    SetDimensions(Vector2D(radius, radius));
}

void Arc::SetDimensions(double width, double height) {
    if(Math::IsEqual(width, height) == false) return;
    SetDimensions(Vector2D(width, height));
}

void Arc::SetDimensions(const Vector2D& dimensions) {
    if(Math::IsEqual(dimensions.GetX(), dimensions.GetY()) == false) return;
    _half_extents = Vector2D((dimensions.GetX() < 0.0 ? 0.0 : dimensions.GetX()), (dimensions.GetY() < 0.0 ? 0.0 : dimensions.GetY()));
    _radius = dimensions.GetX();
    CalculateLength();
    CalculateArea();
}

void Arc::SetWidth(double width) {
    SetDimensions(width, width);
}

void Arc::SetHeight(double height) {
    SetDimensions(height, height);
}

double Arc::GetLength() const {
    return _length;
}

double Arc::GetLength() {
    return static_cast<const Arc&>(*this).GetLength();
}

void Arc::SetX(double x) {
    SetPosition(x, GetY());
}

void Arc::SetY(double y) {
    SetPosition(GetX(), y);
}

void Arc::SetPosition(double x, double y) {
    SetPosition(Vector2D(x, y));
}

void Arc::SetPosition(const Vector2D& position) {
    Shape::SetPosition(position);
}

bool Arc::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Arc::Intersects(const Point& /*point*/) const {
    return false;
}

bool Arc::Intersects(const Line& line) const {
    return line.Intersects(*this);
}

bool Arc::Intersects(const Rectangle& rectangle) const {
    double r = _radius;
    bool resultCTop = a2de::Line::GetDistance(rectangle.GetTop(), _position) <= r;
    bool resultCLeft = a2de::Line::GetDistance(rectangle.GetLeft(), _position) <= r;
    bool resultCRight = a2de::Line::GetDistance(rectangle.GetRight(), _position) <= r;
    bool resultCBottom = a2de::Line::GetDistance(rectangle.GetBottom(), _position) <= r;
    bool CisInside = rectangle.Intersects(_position);
    bool resultC = (CisInside || resultCTop || resultCLeft || resultCRight || resultCBottom);

    bool resultS = false; //GetStartPoint().Intersects(rectangle);
    bool resultE = false; //GetEndPoint().Intersects(rectangle);

    return (resultC || resultS || resultE);
}

bool Arc::Intersects(const Circle& circle) const {
    bool resultC = Point(GetPosition().GetX(), GetPosition().GetY()).GetDistance(circle.GetPosition()) <= circle.GetRadius();
    bool resultS = false; //GetStartPoint().Intersects(circle);
    bool resultE = false; //GetEndPoint().Intersects(circle);
    return (resultC || resultS || resultE);
}
bool Arc::Intersects(const Ellipse& ellipse) const {
    double dist = Point(GetPosition().GetX(), GetPosition().GetY()).GetDistance(ellipse.GetPosition());
    bool resultC = dist <= ellipse.GetRadiusWidth() || dist <= ellipse.GetRadiusHeight();
    bool resultS = false; //GetStartPoint().Intersects(ellipse);
    bool resultE = false; //GetEndPoint().Intersects(ellipse);
    return (resultC || resultS || resultE);
}
bool Arc::Intersects(const Triangle& triangle) const {
    bool resultC = Point(GetPosition().GetX(), GetPosition().GetY()).Intersects(triangle);
    bool resultS = Point(GetPosition().GetX(), GetPosition().GetY()).Intersects(triangle);
    bool resultE = Point(GetPosition().GetX(), GetPosition().GetY()).Intersects(triangle);
    return (resultC || resultS || resultE);
}

bool Arc::Intersects(const Arc& arc) const {
    Point myCenter(this->GetPosition().GetX(), this->GetPosition().GetY(), 0.0);
    Point yourCenter(arc.GetPosition().GetX(), arc.GetPosition().GetY(), 0.0);
    double distance_between_centers = myCenter.GetDistance(yourCenter);

    return ((myCenter == yourCenter) && distance_between_centers == arc.GetRadius() || distance_between_centers == this->GetRadius());
}

bool Arc::Intersects(const Polygon& /*polygon*/) const {
    return false; //this->GetStartPoint().Intersects(polygon) || this->GetEndPoint().Intersects(polygon);
}

bool Arc::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Arc::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Arc::Intersects(const Vector2D& /*position*/) const {
    return false;
}

void Arc::Draw(BITMAP* dest, const a2de::Color& color, bool /*filled*/) {
    arc(dest, a2de::Math::ToScreenScale(GetX()), a2de::Math::ToScreenScale(GetY()), Math::RadianToFixed(_startAngle), Math::RadianToFixed(_endAngle), a2de::Math::ToScreenScale(_radius), color);
}

void Arc::CalculateArea() {
    _area = 0.5 * _radius * _radius * _theta;
}

void Arc::CalculateLength() {
    _length = _theta * _radius;
}
void Arc::SetAnglesDegrees(double startAngle, double endAngle) {
    SetAngles(Math::DegreeToRadian(startAngle), Math::DegreeToRadian(endAngle));
}

void Arc::SetAngles(double startAngle, double endAngle) {
    while(startAngle > Math::A2DE_PI) {
        startAngle -= Math::A2DE_2PI;
    }
    while(startAngle < -Math::A2DE_PI) {
        startAngle += Math::A2DE_2PI;
    }
    while(endAngle > Math::A2DE_PI) {
        endAngle -= Math::A2DE_2PI;
    }
    while(endAngle < -Math::A2DE_PI) {
        endAngle += Math::A2DE_2PI;
    }
    _startAngle = std::fmod(startAngle, Math::A2DE_2PI);
    _endAngle = std::fmod(endAngle, Math::A2DE_2PI);
    double eA = _endAngle;
    double sA = _startAngle;
    if(eA < sA) {
        eA = _endAngle + Math::A2DE_2PI;
    }
    _theta = std::fabs(eA - sA);
    CalculateLength();
    CalculateArea();
}

double Arc::GetStartAngle() const {
    return _startAngle;
}

double Arc::GetStartAngle() {
    return static_cast<const Arc&>(*this).GetStartAngle();
}

double Arc::GetEndAngle() const {
    return _endAngle;
}
double Arc::GetEndAngle() {
    return static_cast<const Arc&>(*this).GetEndAngle();
}

a2de::Vector2D Arc::GetStartPoint() const {
    return Vector2D(GetPosition().GetX() + std::cos(GetStartAngle()) * GetRadius(), GetPosition().GetY() + -std::sin(GetStartAngle()) * GetRadius());
}
a2de::Vector2D Arc::GetEndPoint() const {
    return Vector2D(GetPosition().GetX() + std::cos(GetEndAngle()) * GetRadius(), GetPosition().GetY() + -std::sin(GetEndAngle()) * GetRadius());
}

a2de::Vector2D Arc::GetCenterPoint() const {
    Vector2D s(GetStartPoint());
    Vector2D e(GetEndPoint());
    return Vector2D(s + (e - s) * 0.5);
}

double Arc::GetTheta() const {
    return _theta;
}

double Arc::GetTheta() {
    return static_cast<const Arc&>(*this).GetTheta();
}

bool Arc::Contains(const Shape& shape) const {
    return this->Contains(shape);
}

bool Arc::Contains(const Point& /*point*/) const {
    return false;
}

bool Arc::Contains(const Line& /*line*/) const {
    return false;
}

bool Arc::Contains(const Rectangle& /*rectangle*/) const {
    return false;
}

bool Arc::Contains(const Circle& /*circle*/) const {
    return false;
}

bool Arc::Contains(const Ellipse& /*ellipse*/) const {
    return false;
}

bool Arc::Contains(const Triangle& /*triangle*/) const {
    return false;
}

bool Arc::Contains(const Arc& /*arc*/) const {
    return false;
}

bool Arc::Contains(const Polygon& /*polygon*/) const {
    return false;
}

bool Arc::Contains(const Spline& /*spline*/) const {
    return false;
}

bool Arc::Contains(const Sector& /*sector*/) const {
    return false;
}

Arc& Arc::operator=(const Arc& rhs) {
    if(this == &rhs) return *this;

    Shape::operator=(rhs);
    this->_startAngle = rhs._startAngle;
    this->_endAngle = rhs._endAngle;
    this->_radius = rhs._radius;
    this->_theta = rhs._theta;
    this->_length = rhs._length;
    SetAngles(_startAngle, _endAngle);
    CalculateLength();
    CalculateArea();

    return *this;
}


A2DE_END