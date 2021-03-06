/**************************************************************************************************
// file:	Engine\Physics\AABB.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the aabb class
 **************************************************************************************************/
#include "AABB.h"

A2DE_BEGIN

AABB::AABB() : _transform_instance(), _half_extents(), _color() { /* DO NOTHING */ }

AABB::AABB(const a2de::Transform& transform_instance) : _transform_instance(transform_instance), _half_extents(), _color() { /* DO NOTHING */ }

AABB::AABB(const a2de::Transform& transform_instance, const Vector2D& half_extents) : _transform_instance(transform_instance), _half_extents(half_extents), _color() { /* DO NOTHING */ }

AABB::AABB(const a2de::Transform& transform_instance, const Vector2D& half_extents, const Color& color) : _transform_instance(transform_instance), _half_extents(half_extents), _color(color) { /* DO NOTHING */ }

AABB::AABB(const AABB& other) : _transform_instance(other._transform_instance), _half_extents(other._half_extents), _color(other._color) { /* DO NOTHING */ }

AABB& AABB::operator=(const AABB& rhs) {
    if(this == &rhs) return *this;

    this->_transform_instance = rhs._transform_instance;
    this->_half_extents = rhs._half_extents;
    this->_color = rhs._color;

    return *this;
}


AABB::~AABB() { /* DO NOTHING */ }

void AABB::SetHalfExtents(const a2de::Vector2D& half_extents) {
    _half_extents = half_extents;
}

const Vector2D& AABB::GetHalfExtents() const {
    return _half_extents;
}

Vector2D& AABB::GetHalfExtents() {
    return const_cast<Vector2D&>(static_cast<const AABB&>(*this).GetHalfExtents());
}

Line AABB::GetRight() const {
    double x = _transform_instance.GetPosition().GetX();
    double y = _transform_instance.GetPosition().GetY();
    double xhe = _half_extents.GetX();
    double yhe = _half_extents.GetY();
    return Line(x + xhe, y - yhe, x + xhe, y + yhe, _color);
}

Line AABB::GetRight() {
    return static_cast<const AABB&>(*this).GetRight();
}

Line AABB::GetTop() const {
    double x = _transform_instance.GetPosition().GetX();
    double y = _transform_instance.GetPosition().GetY();
    double xhe = _half_extents.GetX();
    double yhe = _half_extents.GetY();
    return Line(x - xhe, y - yhe, x + xhe, y - yhe, _color);
}

Line AABB::GetTop() {
    return static_cast<const AABB&>(*this).GetTop();
}

void AABB::Draw(BITMAP* dest) {

    double x = _transform_instance.GetPosition().GetX();
    double y = _transform_instance.GetPosition().GetY();
    double xhe = _half_extents.GetX();
    double yhe = _half_extents.GetY();
    double ulx = x - xhe;
    double uly = y - yhe;
    double lrx = x + xhe;
    double lry = y + yhe;

    rect(dest, Math::ToScreenScale(ulx), Math::ToScreenScale(uly), Math::ToScreenScale(lrx), Math::ToScreenScale(lry), _color);
}

Line AABB::GetLeft() const {
    double x = _transform_instance.GetPosition().GetX();
    double y = _transform_instance.GetPosition().GetY();
    double xhe = _half_extents.GetX();
    double yhe = _half_extents.GetY();
    return Line(x - xhe, y - yhe, x - xhe, y + yhe, _color);
}

Line AABB::GetLeft() {
    return static_cast<const AABB&>(*this).GetLeft();
}

Line AABB::GetBottom() const {
    double x = _transform_instance.GetPosition().GetX();
    double y = _transform_instance.GetPosition().GetY();
    double xhe = _half_extents.GetX();
    double yhe = _half_extents.GetY();
    return Line(x - xhe, y + yhe, x + xhe, y + yhe, _color);
}

Line AABB::GetBottom() {
    return static_cast<const AABB&>(*this).GetBottom();
}

const a2de::Transform& AABB::GetTransform() const {
    return _transform_instance;
}

a2de::Transform& AABB::GetTransform() {
    return const_cast<a2de::Transform&>(static_cast<const AABB&>(*this).GetTransform());
}


A2DE_END
