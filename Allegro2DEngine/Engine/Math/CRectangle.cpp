/**************************************************************************************************
// file:	Engine\Math\CRectangle.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the rectangle class
 **************************************************************************************************/
#include "CRectangle.h"

#include <utility>
#include <algorithm>

#include "CPoint.h"
#include "CLine.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"
#include "CVector2D.h"

#include "MiscMath.h"
#include "../a2de_exceptions.h"

A2DE_BEGIN

Rectangle::Rectangle() : Shape(0.0, 0.0) {
    _type = Shape::SHAPETYPE_RECTANGLE;
    CalculateArea();

}

Rectangle::Rectangle(double x, double y, double half_width, double half_height)
    : Shape(x, y, half_width, half_height) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}
Rectangle::Rectangle(const Vector2D& position, double half_width, double half_height)
    : Shape(position, half_width, half_height) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}
Rectangle::Rectangle(double x, double y, const Vector2D& dimensions)
    : Shape(x, y, dimensions) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}
Rectangle::Rectangle(const Vector2D& position, const Vector2D& dimensions)
    : Shape(position, dimensions) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}

Rectangle::Rectangle(double x, double y, double half_width, double half_height, const a2de::Color& color)
    : Shape(x, y, half_width, half_height, color) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}
Rectangle::Rectangle(const Vector2D& position, double half_width, double half_height, const a2de::Color& color)
    : Shape(position, half_width, half_height, color) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}
Rectangle::Rectangle(double x, double y, const Vector2D& half_extents, const a2de::Color& color)
    : Shape(x, y, half_extents, color) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}
Rectangle::Rectangle(const Vector2D& position, const Vector2D& half_extents, const a2de::Color& color)
    : Shape(position, half_extents, color) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}

Rectangle::Rectangle(double x, double y, double half_width, double half_height, const a2de::Color& color, bool filled)
    : Shape(x, y, half_width, half_height, color, filled) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}
Rectangle::Rectangle(const Vector2D& position, double half_width, double half_height, const a2de::Color& color, bool filled)
    : Shape(position, half_width, half_height, color, filled) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}
Rectangle::Rectangle(double x, double y, const Vector2D& half_extents, const a2de::Color& color, bool filled)
    : Shape(x, y, half_extents, color, filled) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}
Rectangle::Rectangle(const Vector2D& position, const Vector2D& half_extents, const a2de::Color& color, bool filled)
    : Shape(position, half_extents, color, filled) {
        _type = Shape::SHAPETYPE_RECTANGLE;
        CalculateArea();
}

Rectangle::Rectangle(const Rectangle& rect) : Shape(rect) {
    _type = Shape::SHAPETYPE_RECTANGLE;
    CalculateArea();
}

Rectangle::~Rectangle() {

}
Line Rectangle::GetTop() const {
    double x1 = GetX() - GetWidth();
    double x2 = GetX() + GetWidth();
    double y = GetY() - GetHeight();
    return Line(x1, y, x2, y, false);
}
Line Rectangle::GetLeft() const {
    double x = GetX() - GetWidth();
    double y1 = GetY() - GetHeight();
    double y2 = GetY() + GetHeight();
    return Line(x, y1, x, y2, false);
}
Line Rectangle::GetBottom() const {
    double x1 = GetX() - GetWidth();
    double x2 = GetX() + GetWidth();
    double y = GetY() + GetHeight();
    return Line(x1, y, x2, y, false);
}
Line Rectangle::GetRight() const {
    double x = GetX() + GetWidth();
    double y1 = GetY() - GetHeight();
    double y2 = GetY() + GetHeight();
    return Line(x, y1, x, y2, false);
}
Point Rectangle::GetTopLeft() const {
    return Point(GetX() - GetWidth(), GetY() - GetHeight());
}
Point Rectangle::GetTopRight() const {
    return Point(GetX() + GetWidth(), GetY() + GetHeight());
}
Point Rectangle::GetBottomLeft() const {
    return Point(GetX() - GetWidth(), GetY() + GetHeight());
}
Point Rectangle::GetBottomRight() const {
    return Point(GetX() + GetWidth(), GetY() + GetHeight());
}

void Rectangle::SetX(double x) {
    SetPosition(x, GetY());
}

void Rectangle::SetY(double y) {
    SetPosition(GetX(), y);
}

void Rectangle::SetPosition(double x, double y) {
    SetPosition(Vector2D(x, y));
}

void Rectangle::SetPosition(const Vector2D& position) {
    Shape::SetPosition(position);
}

void Rectangle::SetDimensions(double half_width, double half_height) {
    if(half_width < 0.0) half_width = 0.0;
    if(half_height < 0.0) half_height = 0.0;
    Shape::SetDimensions(half_width, half_height);
    CalculateArea();
}

void Rectangle::SetDimensions(const Vector2D& dimensions) {
    SetDimensions(dimensions.GetX(), dimensions.GetY());
}

void Rectangle::SetWidth(double half_width) {
    SetDimensions(half_width, GetHeight());
}

void Rectangle::SetHeight(double half_height) {
    SetDimensions(GetWidth(), half_height);
}

void Rectangle::Draw(BITMAP* dest, const a2de::Color& color, bool filled) {
    double x1 = a2de::Math::ToScreenScale(GetX() - GetWidth());
    double y1 = a2de::Math::ToScreenScale(GetY() - GetHeight());
    double x2 = a2de::Math::ToScreenScale(GetX() + GetWidth());
    double y2 = a2de::Math::ToScreenScale(GetY() + GetHeight());
    
    if(filled) {
        rectfill(dest, x1, y1, x2, y2, color);
    } else {
        rect(dest, x1, y1, x2, y2, color);
    }
}

bool Rectangle::Intersects(const Polygon& polygon) const {
    return polygon.Intersects(*this);
}
bool Rectangle::Intersects(const Rectangle& rectangle) const {
    double tx = this->GetX();
    double ty = this->GetY();
    double tw = this->GetWidth();
    double th = this->GetHeight();

    double rx = rectangle.GetX();
    double ry = rectangle.GetY();
    double rw = rectangle.GetWidth();
    double rh = rectangle.GetHeight();

    double myTop = ty - th;
    double myLeft = tx - tw;
    double myRight = tx + tw;
    double myBottom = ty + th;
    double rTop = ty - rh;
    double rLeft = rx - rw;
    double rRight = rx + rw;
    double rBottom = ry + rh;

    if(myTop > rBottom) return false;
    if(myBottom < rTop) return false;
    if(myLeft > rRight) return false;
    if(myRight < rLeft) return false;

    return true;
}
bool Rectangle::Intersects(const Triangle& /*triangle*/) const {
    return false;
    //bool resultTop = GetTop().Intersects(triangle.GetLineAB()) ||
    //    GetTop().Intersects(triangle.GetLineBC()) ||
    //    GetTop().Intersects(triangle.GetLineCA());
    //bool resultLeft = GetLeft().Intersects(triangle.GetLineAB()) ||
    //    GetLeft().Intersects(triangle.GetLineBC()) ||
    //    GetLeft().Intersects(triangle.GetLineCA());
    //bool resultRight = GetRight().Intersects(triangle.GetLineAB()) ||
    //    GetRight().Intersects(triangle.GetLineBC()) ||
    //    GetRight().Intersects(triangle.GetLineCA());
    //bool resultBottom = GetBottom().Intersects(triangle.GetLineAB()) ||
    //    GetBottom().Intersects(triangle.GetLineBC()) ||
    //    GetBottom().Intersects(triangle.GetLineCA());
    //bool isInside = Intersects(Point(triangle.GetCenter(), triangle.GetColor()));
    //return (isInside || resultTop || resultLeft || resultRight || resultBottom);
}
bool Rectangle::Intersects(const Ellipse& ellipse) const {

    double ellipseResultWidth = ellipse.GetRadiusWidth();
    double ellipseResultHeight = ellipse.GetRadiusHeight();

    double distTop = Point(ellipse.GetPosition()).GetDistance(GetTop());
    double distLeft = Point(ellipse.GetPosition()).GetDistance(GetLeft());
    double distRight = Point(ellipse.GetPosition()).GetDistance(GetRight());
    double distBottom = Point(ellipse.GetPosition()).GetDistance(GetBottom());

    bool resultTop = (distTop <= ellipseResultWidth) || (distTop <= ellipseResultHeight);
    bool resultLeft = (distLeft <= ellipseResultWidth) || (distLeft <= ellipseResultHeight);
    bool resultRight = (distRight <= ellipseResultWidth) || (distRight <= ellipseResultHeight);
    bool resultBottom = (distBottom <= ellipseResultWidth) || (distBottom <= ellipseResultHeight);

    return (resultTop || resultLeft || resultRight || resultBottom);
}
bool Rectangle::Intersects(const Circle& circle) const {

    double radius = circle.GetRadius();

    double distTop = Point(circle.GetPosition()).GetDistance(GetTop());
    double distLeft = Point(circle.GetPosition()).GetDistance(GetLeft());
    double distRight = Point(circle.GetPosition()).GetDistance(GetRight());
    double distBottom = Point(circle.GetPosition()).GetDistance(GetBottom());

    bool resultTop = distTop <= radius;
    bool resultLeft = distLeft <= radius;
    bool resultRight = distRight <= radius;
    bool resultBottom = distBottom <= radius;
    bool isInside = Intersects(Point(circle.GetPosition()));
    return (isInside || resultTop || resultLeft || resultRight || resultBottom);
}

bool Rectangle::Intersects(const Line& line) const {
    return line.Intersects(*this);
}

bool Rectangle::Intersects(const Point& point) const {
    return Intersects(point.GetPosition());
}

bool Rectangle::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Rectangle::Intersects(const Arc& /*arc*/) const {
    return false;
}

bool Rectangle::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Rectangle::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Rectangle::Intersects(const Vector2D& position) const {

    double rx = this->GetX();
    double rw = this->GetWidth();
    double rLeft = rx - rw;
    double pX = position.GetX();
    if(rLeft > pX) return false;

    double rRight = rx + rw;
    if(rRight < pX) return false;

    double ry = this->GetY();
    double rh = this->GetHeight();
    double rTop = ry - rh;
    double pY = position.GetY();
    if(rTop > pY) return false;

    double rBottom = ry + rh;
    if(rBottom < pY) return false;

    return true;
}

void Rectangle::Overlap(const Rectangle& rectIN, Rectangle& rectOUT, bool& result) {
    if(this->Intersects(rectIN) == false) {
        result = false;
        return;
    }

    a2de::Vector2D my_TL(_position - _half_extents);
    a2de::Vector2D my_BR(_position + _half_extents);

    a2de::Vector2D your_TL(rectIN._position - rectIN._half_extents);
    a2de::Vector2D your_BR(rectIN._position + rectIN._half_extents);

    a2de::Vector2D topLeft(std::max(my_TL.GetX(), your_TL.GetX()), std::max(my_TL.GetY(), your_TL.GetY()));
    a2de::Vector2D bottomRight(std::min(my_BR.GetX(), your_BR.GetX()), std::min(my_BR.GetY(), your_BR.GetY()));

    a2de::Vector2D dimensions(std::abs((bottomRight - topLeft).GetX() / 2.0), std::abs((bottomRight - topLeft).GetY() / 2.0));
    rectOUT = Rectangle(topLeft + dimensions, dimensions, rectOUT.GetColor(), rectOUT.IsFilled());
    result = true;
}

Rectangle& Rectangle::operator=(const Rectangle& rhs) {
    if(this == &rhs) return *this;

    Shape::operator=(rhs);
    CalculateArea();

    return *this;
}

bool Rectangle::operator==(const Rectangle& rhs) {
    if(this == &rhs) return true;
    return (this->GetArea() == rhs.GetArea());
}
bool operator==(const Rectangle& lhs, const Rectangle& rhs) {
    if(&lhs == &rhs) return true;
    return (lhs.GetArea() == rhs.GetArea());
}
bool Rectangle::operator!=(const Rectangle& rhs) {
    return !(*this == rhs);
}
bool operator!=(const Rectangle& lhs, const Rectangle& rhs) {
    if(&lhs == &rhs) return false;
    return (lhs.GetArea() != rhs.GetArea());
}
bool Rectangle::operator<(const Rectangle& rhs) {
    if(this == &rhs) return false;
    return (this->GetArea() < rhs.GetArea());
}
bool operator<(const Rectangle& lhs, const Rectangle& rhs) {
    if(&lhs == &rhs) return false;
    return (lhs.GetArea() < rhs.GetArea());
}
bool Rectangle::operator>(const Rectangle& rhs) {
    if(this == &rhs) return false;
    return (this->GetArea() > rhs.GetArea());
}
bool operator>(const Rectangle& lhs, const Rectangle& rhs) {
    if(&lhs == &rhs) return false;
    return (lhs.GetArea() > rhs.GetArea());
}
bool Rectangle::operator<=(const Rectangle& rhs) {
    return !(*this > rhs);
}
bool operator<=(const Rectangle& lhs, const Rectangle& rhs) {
    return !(lhs.GetArea() < rhs.GetArea());
}

bool Rectangle::operator>=(const Rectangle& rhs) {
    return !(*this < rhs);
}
bool operator>=(const Rectangle& lhs, const Rectangle& rhs) {
    return !(lhs.GetArea() > rhs.GetArea());
}

void Rectangle::CalculateArea() {
    _area = _half_extents.GetX() *  _half_extents.GetY() * 4.0;
}

A2DE_END