/**************************************************************************************************
// file:	Engine\Physics\AABB.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the aabb class
 **************************************************************************************************/
#ifndef A2DE_AABB_H
#define A2DE_AABB_H

#include "../Math/CVector2D.h"
#include "../Math/CLine.h"
#include "../Math/CTransform.h"
#include "IBoundingBox.h"

A2DE_BEGIN


class AABB : public IBoundingBox {
public:
    AABB();
    AABB(const a2de::Transform& transform_instance);
    AABB(const a2de::Transform& transform_instance, const Vector2D& half_extents);
    AABB(const a2de::Transform& transform_instance, const Vector2D& half_extents, const Color& color);
    AABB(const AABB& other);
    AABB& operator=(const AABB& rhs);

    virtual ~AABB();

    virtual void SetHalfExtents(const a2de::Vector2D& half_extents);
    const Vector2D& GetHalfExtents() const;
    Vector2D& GetHalfExtents();

    virtual a2de::Line GetRight() const;
    virtual a2de::Line GetRight();

    virtual a2de::Line GetTop() const;
    virtual a2de::Line GetTop();

    virtual void Draw(BITMAP* dest);

    virtual a2de::Line GetLeft() const;
    virtual a2de::Line GetLeft();

    virtual a2de::Line GetBottom() const;
    virtual a2de::Line GetBottom();

    virtual const a2de::Transform& GetTransform() const;
    virtual a2de::Transform& GetTransform();

protected:
private:
    Transform _transform_instance;
    Vector2D _half_extents;
    Color _color;
};

A2DE_END

#endif // AABB_H