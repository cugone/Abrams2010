/**************************************************************************************************
// file:	Engine\Math\CShape.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the shape class
 **************************************************************************************************/
#include "CShape.h"

#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"


A2DE_BEGIN


Shape::Shape() :
_position(0.0, 0.0),
_half_extents(0.0, 0.0),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(0),
_filled(false) { }

Shape::Shape(double x, double y) :
_position(x, y),
_half_extents(0.0, 0.0),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(0),
_filled(false) { }

Shape::Shape(const Vector2D& position) :
_position(position),
_half_extents(0.0, 0.0),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(0),
_filled(false) { }

Shape::Shape(double x, double y, double width, double height) :
_position(x, y),
_half_extents(width, height),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(0),
_filled(false) { }

Shape::Shape(const Vector2D& position, double width, double height) :
_position(position),
_half_extents(width, height),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(0),
_filled(false) { }

Shape::Shape(double x, double y, const Vector2D& dimensions) :
_position(x, y),
_half_extents(dimensions),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(0),
_filled(false) { }

Shape::Shape(const Vector2D& position, const Vector2D& dimensions) :
_position(position),
_half_extents(dimensions),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(0),
_filled(false) { }


Shape::Shape(double x, double y, double width, double height, const a2de::Color& color) :
_position(x, y),
_half_extents(width, height),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(color),
_filled(false) { }

Shape::Shape(const Vector2D& position, double width, double height, const a2de::Color& color) :
_position(position),
_half_extents(width, height),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(color),
_filled(false) { }

Shape::Shape(double x, double y, const Vector2D& dimensions, const a2de::Color& color) :
_position(x, y),
_half_extents(dimensions),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(color),
_filled(false) { }


Shape::Shape(const Vector2D& position, const Vector2D& dimensions, const a2de::Color& color) :
_position(position),
_half_extents(dimensions),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(color),
_filled(false) { }


Shape::Shape(double x, double y, double width, double height, const a2de::Color& color, bool filled) :
_position(x, y),
_half_extents(width, height),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(color),
_filled(filled) { }

Shape::Shape(const Vector2D& position, double width, double height, const a2de::Color& color, bool filled) :
_position(position),
_half_extents(width, height),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(color),
_filled(filled) { }


Shape::Shape(double x, double y, const Vector2D& dimensions, const a2de::Color& color, bool filled) :
_position(x, y),
_half_extents(dimensions),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(color),
_filled(filled) { }


Shape::Shape(const Vector2D& position, const Vector2D& dimensions, const a2de::Color& color, bool filled) :
_position(position),
_half_extents(dimensions),
_area(0.0),
_type(Shape::SHAPETYPE_SHAPE),
_color(color),
_filled(filled) { }


Shape::Shape(const Shape& shape) :
_position(shape._position),
_half_extents(shape._half_extents),
_area(shape._area),
_type(Shape::SHAPETYPE_SHAPE),
_color(shape._color),
_filled(shape._filled) { }

Shape& Shape::operator=(const Shape& rhs) {
    if(this == &rhs) return *this;
    this->_position = rhs._position;
    this->_half_extents = rhs._half_extents;
    this->_area = rhs._area;
    this->_type = rhs._type;
    this->_color = rhs._color;
    this->_filled = rhs._filled;
    return *this;
}
Shape::~Shape() {

}

const a2de::Color& Shape::GetColor() const {
    return _color;
}

a2de::Color& Shape::GetColor() {
    return const_cast<a2de::Color&>(static_cast<const Shape&>(*this).GetColor());
}

bool Shape::IsFilled() const {
    return _filled;
}

void Shape::SetColor(const a2de::Color& color) {
    _color = color;
}

void Shape::SetFill(bool filled) {
    _filled = filled;
}

double Shape::GetWidth() const {
    return _half_extents.GetX();
}

double Shape::GetWidth(){
    return static_cast<const Shape&>(*this).GetWidth();
}

double Shape::GetHeight() const {
    return _half_extents.GetY();
}

double Shape::GetHeight() {
    return static_cast<const Shape&>(*this).GetHeight();
}

const Vector2D& Shape::GetDimensions() const {
    return _half_extents;
}

Vector2D& Shape::GetDimensions() {
    return const_cast<a2de::Vector2D&>(static_cast<const Shape&>(*this).GetDimensions());
}

const Vector2D& Shape::GetPosition() const {
    return _position;
}

Vector2D& Shape::GetPosition() {
    return const_cast<a2de::Vector2D&>(static_cast<const Shape&>(*this).GetPosition());
}


double Shape::GetArea() const {
    return _area;
}

double Shape::GetArea() {
    return static_cast<const Shape&>(*this).GetArea();
}

double Shape::GetX() const {
    return _position.GetX();
}

double Shape::GetX() {
    return static_cast<const Shape&>(*this).GetX();
}

double Shape::GetY() const {
    return _position.GetY();
}

double Shape::GetY() {
    return static_cast<const Shape&>(*this).GetY();
}

void Shape::SetX(double x) {
    Shape::SetPosition(x, GetY());
}
void Shape::SetY(double y) {
    Shape::SetPosition(GetX(), y);
}

void Shape::SetPosition(double x, double y) {
    Shape::SetPosition(Vector2D(x, y));
}

void Shape::SetPosition(const Vector2D& position) {
    _position = position;
}

void Shape::SetWidth(double width) {
    Shape::SetDimensions(width, GetHeight());
}
void Shape::SetHeight(double height) {
    Shape::SetDimensions(GetWidth(), height);
}
void Shape::SetDimensions(double width, double height) {
    Shape::SetDimensions(Vector2D(width, height));
}

void Shape::SetDimensions(const Vector2D& dimensions) {
    _half_extents = dimensions;
}

const Shape::SHAPE_TYPE& Shape::GetShapeType() const {
    return _type;
}

Shape::SHAPE_TYPE& Shape::GetShapeType() {
    return const_cast<Shape::SHAPE_TYPE&>(static_cast<const Shape&>(*this).GetShapeType());
}


Shape* Shape::Clone(Shape* shape) {
    if(shape == nullptr) return nullptr;
    Shape::SHAPE_TYPE type = shape->GetShapeType();

    switch(type) {
    case Shape::SHAPETYPE_POINT:
        return new Point(*dynamic_cast<Point*>(shape));
    case Shape::SHAPETYPE_LINE:
        return new Line(*dynamic_cast<Line*>(shape));
    case Shape::SHAPETYPE_RECTANGLE:
        return new Rectangle(*dynamic_cast<Rectangle*>(shape));
    case Shape::SHAPETYPE_CIRCLE:
        return new Circle(*dynamic_cast<Circle*>(shape));
    case Shape::SHAPETYPE_ELLIPSE:
        return new Ellipse(*dynamic_cast<Ellipse*>(shape));
    case Shape::SHAPETYPE_TRIANGLE:
        return new Triangle(*dynamic_cast<Triangle*>(shape));
    case Shape::SHAPETYPE_ARC:
        return new Arc(*dynamic_cast<Arc*>(shape));
    case Shape::SHAPETYPE_POLYGON:
        return new Polygon(*dynamic_cast<Polygon*>(shape));
    case Shape::SHAPETYPE_SPLINE:
        return new Spline(*dynamic_cast<Spline*>(shape));
    case Shape::SHAPETYPE_SECTOR:
        return new Sector(*dynamic_cast<Sector*>(shape));
    default:
        return nullptr;
    }

}

bool Shape::Contains(const Shape& shape) const {

    Shape::SHAPE_TYPE type = shape.GetShapeType();
    switch(type) {
    case Shape::SHAPETYPE_POINT:
        return this->Contains(dynamic_cast<const Point&>(shape));
    case Shape::SHAPETYPE_LINE:
        return this->Contains(dynamic_cast<const Line&>(shape));
    case Shape::SHAPETYPE_RECTANGLE:
        return this->Contains(dynamic_cast<const Rectangle&>(shape));
    case Shape::SHAPETYPE_CIRCLE:
        return this->Contains(dynamic_cast<const Circle&>(shape));
    case Shape::SHAPETYPE_ELLIPSE:
        return this->Contains(dynamic_cast<const Ellipse&>(shape));
    case Shape::SHAPETYPE_TRIANGLE:
        return this->Contains(dynamic_cast<const Triangle&>(shape));
    case Shape::SHAPETYPE_ARC:
        return this->Contains(dynamic_cast<const Arc&>(shape));
    case Shape::SHAPETYPE_POLYGON:
        return this->Contains(dynamic_cast<const Polygon&>(shape));
    case Shape::SHAPETYPE_SPLINE:
        return this->Contains(dynamic_cast<const Spline&>(shape));
    case Shape::SHAPETYPE_SECTOR:
        return this->Contains(dynamic_cast<const Sector&>(shape));
    default:
        return false;
    }

}

bool Shape::Contains(const Point& point) const {
    return this->Intersects(point);
}

bool Shape::Contains(const Line& line) const {
    return this->Intersects(Point(line.GetPointOne())) && this->Intersects(Point(line.GetPointTwo()));
}

bool Shape::Contains(const Rectangle& rectangle) const {
    double rleft = rectangle.GetX();
    double rtop = rectangle.GetY();
    double rright = rleft + rectangle.GetWidth();
    double rbottom = rtop + rectangle.GetHeight();

    double tleft = this->GetX();
    double ttop = this->GetY();
    double tright = tleft + this->GetWidth();
    double tbottom = ttop + this->GetHeight();

    bool is_exact = a2de::Math::IsEqual(rtop, ttop) && a2de::Math::IsEqual(rleft, tleft) && a2de::Math::IsEqual(rbottom, tbottom) && a2de::Math::IsEqual(rright, tright);
    bool is_smaller = (rtop > ttop && rleft > tleft && rbottom < tbottom && rright < tright);
    return (is_exact || is_smaller);
}

bool Shape::Contains(const Circle& circle) const {
    double cdiameter = circle.GetDiameter();
    double twidth = this->GetWidth();
    double theight = this->GetHeight();

    bool diameter_equal_to_width = a2de::Math::IsEqual(cdiameter, twidth);
    bool diameter_equal_to_height = a2de::Math::IsEqual(cdiameter, theight);
    bool diameter_less_than_width = cdiameter < twidth;
    bool diameter_less_than_height = cdiameter < theight;
    
    bool diameter_less_equal_width = diameter_less_than_width || diameter_equal_to_width;
    bool diameter_less_equal_height = diameter_less_than_height || diameter_equal_to_height;

    bool center_inside_shape = this->Intersects(Point(circle.GetPosition()));

    bool contains = center_inside_shape && diameter_less_equal_width && diameter_less_equal_height;

    return contains;
}

bool Shape::Contains(const Ellipse& ellipse) const {
    return this->Intersects(Point(ellipse.GetPosition())) && ellipse.GetWidth() <= this->GetWidth() && ellipse.GetHeight() <= this->GetHeight();
}

bool Shape::Contains(const Triangle& triangle) const {
    return this->Intersects(Point(triangle.GetPointA())) && this->Intersects(Point(triangle.GetPointB())) && this->Intersects(Point(triangle.GetPointC()));
}

bool Shape::Contains(const Arc& arc) const {
    return this->Intersects(arc.GetStartPoint()) && this->Intersects(arc.GetEndPoint());
}

bool Shape::Contains(const Polygon& polygon) const {

    int total_points = polygon.GetNumVertices();
    for(int i = 0; i < total_points; ++i) {
        if(this->Intersects(polygon.GetVertices()[i])) continue;
        return false;
    }
    return true;
}

bool Shape::Contains(const Spline& /*spline*/) const {
    return false;
}

bool Shape::Contains(const Sector& sector) const {
    return this->Intersects(sector.GetStartPoint()) && this->Intersects(sector.GetEndPoint()) && this->Intersects(Point(sector.GetPosition()));
}

void Shape::Draw(BITMAP* dest) {
    Draw(dest, _color, _filled);
}


A2DE_END