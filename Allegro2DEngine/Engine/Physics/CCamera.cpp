/**************************************************************************************************
// file:	Engine\Physics\CCamera.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the camera class
 **************************************************************************************************/
#include "CCamera.h"

#include <allegro/gfx.h>
#include <allegro/draw.h>

#include "../a2de_math.h"
#include "../a2de_graphics.h"
#include "CWorld.h"

A2DE_BEGIN


Camera::Camera() : _parent(nullptr), _position(), _extents(a2de::Math::ToWorldScale(a2de::Vector2D(0.5, 0.5))), _buffer(nullptr) { /* DO NOTHING */ }

Camera::Camera(const Vector2D& position, const Vector2D& extents)
    : _parent(nullptr), _position(position), _extents(extents), _buffer(nullptr) { }

Camera::Camera(const World& parent, const Vector2D& position, const Vector2D& extents)
    : _parent(&parent), _position(position), _extents(extents), _buffer(nullptr) {
    SetPosition(_position);
}

Camera::Camera(const Camera& other)
    : _parent(other._parent), _position(other._position), _extents(other._extents), _buffer(nullptr) {
    SetPosition(_position);
}

Camera::~Camera() {
    _parent = nullptr;
    if(_buffer) {
        destroy_bitmap(_buffer);
        _buffer = nullptr;
    }
}

Camera& Camera::operator=(const Camera& rhs) {
    if(this == &rhs) return *this;

    this->_parent = rhs._parent;
    this->_position = rhs._position;
    this->_extents = rhs._extents;
    this->_buffer = nullptr;

    return *this;
}

const Vector2D& Camera::GetPosition() const {
    return _position;
}

Vector2D& Camera::GetPosition() {
    return const_cast<Vector2D&>(static_cast<const Camera&>(*this).GetPosition());
}

void Camera::SetPosition(const Vector2D& position) {
    double x = position.GetX();
    double y = position.GetY();

    double d_width = _extents.GetX();
    double d_height = _extents.GetY();
    double p_width = _parent->GetWidth();
    double p_height = _parent->GetHeight();

    if(x < d_width) x = d_width;
    if(y < d_height) y = d_height;

    if((p_width > d_width) && (x > p_width - d_width)) x = p_width - d_width;
    if((p_height > d_height) && (y > p_height - d_height)) y = p_height - d_height;

    _position = Vector2D(x, y);
}

const Vector2D& Camera::GetExtents() const {
    return _extents;
}

Vector2D& Camera::GetExtents() {
    return const_cast<Vector2D&>(static_cast<const Camera&>(*this).GetExtents());
}

double Camera::GetX() const {
    return _position.GetX();
}

double Camera::GetX() {
    return static_cast<const Camera&>(*this).GetX();
}

double Camera::GetY() const {
    return _position.GetY();
}

double Camera::GetY() {
    return static_cast<const Camera&>(*this).GetY();
}

void Camera::SetX(double x) {
    SetPosition(Vector2D(x, _position.GetY()));
}

void Camera::SetY(double y) {
    SetPosition(Vector2D(_position.GetX(), y));
}

const World* const Camera::GetParent() const {
    return _parent;
}

const World* Camera::GetParent() {
    return static_cast<const Camera&>(*this).GetParent();
}

void Camera::SetParent(const World& parent) {
    _parent = &parent;
}

a2de::Vector2D Camera::CameraToWorldPosition(const Camera& cam, const Vector2D& screen_position) {
    Vector2D world_pos(cam.GetPosition() - cam.GetExtents());
    world_pos += a2de::Math::ToWorldScale(screen_position);
    return world_pos;
}

a2de::Vector2D Camera::WorldToCameraPosition(const Camera& cam, const Vector2D& world_position) {
    Vector2D screen_pos(a2de::Math::ToScreenScale(world_position));
    screen_pos -= a2de::Vector2D(a2de::Math::ToScreenScale(cam.GetPosition() - cam.GetExtents()));
    return screen_pos;
}

void Camera::RenderView(BITMAP* dest, const Vector2D& position) {
    if(dest == nullptr || _buffer == nullptr) return;
    double x = position.GetX();
    double y = position.GetY();
    double w = this->GetExtents().GetX() * 2.0;
    double h = this->GetExtents().GetY() * 2.0;
    double scaled_w = a2de::Math::ToScreenScale(w);
    double scaled_h = a2de::Math::ToScreenScale(h);
    blit(_buffer, dest, 0, 0, x, y, scaled_w, scaled_h);
}

void Camera::RenderView(BITMAP* dest) {
    this->RenderView(dest, a2de::Vector2D(0.0, 0.0));
}

void Camera::RenderText(FONT* font_type, int x, int y, const std::string& message_line, const a2de::Color& foreground_color) {
    if(font_type == nullptr || _buffer == nullptr) return;
    textout_ex(_buffer, font_type, message_line.c_str(), x, y, foreground_color, -1);
}

void Camera::RenderText(FONT* font_type, int x, int y, const std::string& message_line, const a2de::Color& foreground_color, const a2de::Color& background_color) {
    if(font_type == nullptr || _buffer == nullptr) return;
    textout_ex(_buffer, font_type, message_line.c_str(), x, y, foreground_color, background_color);
}

void Camera::StartRenderView() {
    a2de::Vector2D e = GetExtents();
    a2de::Vector2D p = GetPosition();
    a2de::Vector2D top_left(a2de::Math::ToScreenScale(p - e));
    a2de::Vector2D bottom_right(a2de::Math::ToScreenScale(p + e));
    double x = top_left.GetX();
    double y = top_left.GetY();
    double w = bottom_right.GetX() - top_left.GetX();
    double h = bottom_right.GetY() - top_left.GetY();
    _buffer = create_sub_bitmap(_parent->GetBuffer(), x, y, w, h);
}

void Camera::EndRenderView() {
    destroy_bitmap(_buffer);
    _buffer = nullptr;
}

BITMAP* Camera::GetBuffer() const {
    return _buffer;
}

BITMAP* Camera::GetBuffer() {
    return static_cast<const Camera&>(*this).GetBuffer();
}

void Camera::RenderObject(Sprite* sprite) {
    if(sprite == nullptr) return;
    double my_x = this->GetPosition().GetX();
    double my_y = this->GetPosition().GetY();
    double my_w = this->GetExtents().GetX();
    double my_h = this->GetExtents().GetY();
    double spr_x = sprite->GetPosition().GetX();
    double spr_y = sprite->GetPosition().GetY();
    double spr_w = sprite->GetWidth();
    double spr_h = sprite->GetHeight();
    Rectangle box(my_x, my_y, my_w, my_h);
    if(box.Intersects(Rectangle(my_x + a2de::Math::ToWorldScale(spr_x), my_y + a2de::Math::ToWorldScale(spr_y), a2de::Math::ToWorldScale(spr_w), a2de::Math::ToWorldScale(spr_h)))) {
        SpriteHandler::Draw(_buffer, sprite);
    }
}

void Camera::RenderObject(Shape* shape) {
    if(shape == nullptr) return;
    Rectangle box(this->GetPosition() + shape->GetPosition(), this->GetExtents());
    if(shape->Intersects(box)) {
        SpriteHandler::Draw(_buffer, shape);
    }
}

A2DE_END