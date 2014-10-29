/**************************************************************************************************
// file:	Engine\Physics\OBB.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the obb class
 **************************************************************************************************/
#include "OBB.h"

#include "../Math/CMatrix4x4.h"
#include "../Math/CVector3D.h"
#include "../Math/CVector4D.h"


A2DE_BEGIN

OBB::OBB() : _transform_instance(), _half_extents(), _points(4), _color() { /* DO NOTHING */ }

OBB::OBB(const a2de::Transform& transform) : _transform_instance(transform), _half_extents(), _points(4), _color() { /* DO NOTHING */ }

OBB::OBB(const a2de::Transform& transform, const a2de::Vector2D& half_extents) : _transform_instance(transform), _half_extents(half_extents), _points(4), _color() { /* DO NOTHING */ }

OBB::OBB(const a2de::Transform& transform, const a2de::Vector2D& half_extents, const a2de::Color& color) : _transform_instance(transform), _half_extents(half_extents), _points(4), _color(color) { /* DO NOTHING */ }

OBB::OBB(const OBB& other) : _transform_instance(other._transform_instance), _half_extents(other._half_extents), _points(other._points), _color(other._color) { /* DO NOTHING */ }

OBB& OBB::operator=(const OBB& rhs) {
    if(this == &rhs) return *this;

    this->_transform_instance = rhs._transform_instance;
    this->_half_extents = rhs._half_extents;
    this->_points = rhs._points;
    this->_color = rhs._color;

    return *this;
}

OBB::~OBB() { /* DO NOTHING */ }


void OBB::SetHalfExtents(const a2de::Vector2D& half_extents) {
    _half_extents = half_extents;
}

a2de::Vector2D& OBB::GetHalfExtents() {
    return const_cast<a2de::Vector2D&>(static_cast<const OBB&>(*this).GetHalfExtents());
}

const a2de::Vector2D& OBB::GetHalfExtents() const {
    return _half_extents;
}

a2de::Line OBB::GetTop() {
    return static_cast<const OBB&>(*this).GetTop();
}

a2de::Line OBB::GetTop() const {
    return a2de::Line(_points[POINTS_TOP_LEFT], _points[POINTS_TOP_RIGHT], this->_color);
}

a2de::Line OBB::GetLeft() {
    return static_cast<const OBB&>(*this).GetLeft();
}

a2de::Line OBB::GetLeft() const {
    return a2de::Line(_points[POINTS_TOP_LEFT], _points[POINTS_BOTTOM_LEFT], this->_color);
}

a2de::Line OBB::GetRight() {
    return static_cast<const OBB&>(*this).GetRight();
}

a2de::Line OBB::GetRight() const {
    return a2de::Line(_points[POINTS_TOP_RIGHT], _points[POINTS_BOTTOM_RIGHT], this->_color);
}

a2de::Line OBB::GetBottom() {
    return static_cast<const OBB&>(*this).GetBottom();
}

a2de::Line OBB::GetBottom() const {
    return a2de::Line(_points[POINTS_BOTTOM_LEFT], _points[POINTS_BOTTOM_RIGHT], this->_color);
}

void OBB::Draw(BITMAP* dest) {

    a2de::Matrix4x4 m(_transform_instance.GetLocalTransform());

    a2de::Matrix4x4 t_inv(a2de::Matrix4x4::GetTranslationMatrix(-_transform_instance.GetPosition()));
    a2de::Matrix4x4 t(a2de::Matrix4x4::GetTranslationMatrix(_transform_instance.GetPosition()));
    a2de::Matrix4x4 r(a2de::Matrix4x4::GetRotationMatrix(_transform_instance.GetRotation()));
    a2de::Matrix4x4 s(a2de::Matrix4x4::GetScaleMatrix(a2de::Vector3D(1.0, 1.0, 1.0)));

    _points[POINTS_TOP_LEFT] = a2de::Vector2D(-_half_extents.GetX(), -_half_extents.GetY());
    _points[POINTS_TOP_RIGHT] = a2de::Vector2D(_half_extents.GetX(), -_half_extents.GetY());
    _points[POINTS_BOTTOM_LEFT] = a2de::Vector2D(-_half_extents.GetX(), _half_extents.GetY());
    _points[POINTS_BOTTOM_RIGHT] = a2de::Vector2D(_half_extents.GetX(), _half_extents.GetY());

    m = t * r * s;

    std::size_t points_size = _points.size();
    for(std::size_t i = 0; i < points_size; ++i) {
        a2de::Vector4D curPoint = m * (a2de::Vector3D(_points[i])).GetHomogeneous();
        double w = curPoint.GetW();
        curPoint = a2de::Vector4D(curPoint.GetX() / w, curPoint.GetY() / w, curPoint.GetZ() / w, 1.0);
        _points[i] = curPoint;
    }

    double tplx = _points[POINTS_TOP_LEFT].GetX();
    double tply = _points[POINTS_TOP_LEFT].GetY();
    double tprx = _points[POINTS_TOP_RIGHT].GetX();
    double tpry = _points[POINTS_TOP_RIGHT].GetY();

    double btlx = _points[POINTS_BOTTOM_LEFT].GetX();
    double btly = _points[POINTS_BOTTOM_LEFT].GetY();
    double btrx = _points[POINTS_BOTTOM_RIGHT].GetX();
    double btry = _points[POINTS_BOTTOM_RIGHT].GetY();

    line(dest, a2de::Math::ToScreenScale(btlx), a2de::Math::ToScreenScale(btly), a2de::Math::ToScreenScale(tplx), a2de::Math::ToScreenScale(tply), this->_color);
    line(dest, a2de::Math::ToScreenScale(tplx), a2de::Math::ToScreenScale(tply), a2de::Math::ToScreenScale(tprx), a2de::Math::ToScreenScale(tpry), this->_color);
    line(dest, a2de::Math::ToScreenScale(tprx), a2de::Math::ToScreenScale(tpry), a2de::Math::ToScreenScale(btrx), a2de::Math::ToScreenScale(btry), this->_color);
    line(dest, a2de::Math::ToScreenScale(btrx), a2de::Math::ToScreenScale(btry), a2de::Math::ToScreenScale(btlx), a2de::Math::ToScreenScale(btly), this->_color);

}

const a2de::Transform& OBB::GetTransform() const {
    return _transform_instance;
}

a2de::Transform& OBB::GetTransform() {
    return const_cast<a2de::Transform&>(static_cast<const OBB&>(*this).GetTransform());
}


A2DE_END
