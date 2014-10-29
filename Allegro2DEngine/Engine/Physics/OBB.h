/**************************************************************************************************
// file:	Engine\Physics\OBB.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the obb class
 **************************************************************************************************/
#ifndef A2DE_OBB_H
#define A2DE_OBB_H

#include "../Math/CVector2D.h"
#include "../Math/CLine.h"
#include "../Math/CTransform.h"
#include "../GFX/CColor.h"
#include "IBoundingBox.h"

#include <vector>

A2DE_BEGIN

class OBB : public IBoundingBox {
public:
    OBB();
    OBB(const Transform& transform_instance);
    OBB(const Transform& transform_instance, const a2de::Vector2D& half_extents);
    OBB(const Transform& transform_instance, const a2de::Vector2D& half_extents, const a2de::Color& color);
    OBB(const OBB& other);
    OBB& operator=(const OBB& rhs);

    virtual ~OBB();

    virtual void SetHalfExtents(const a2de::Vector2D& half_extents);
    virtual const a2de::Vector2D& GetHalfExtents() const;
    virtual a2de::Vector2D& GetHalfExtents();

    virtual a2de::Line GetRight() const;
    virtual a2de::Line GetRight();

    virtual a2de::Line GetTop() const;
    virtual a2de::Line GetTop();

    virtual a2de::Line GetLeft() const;
    virtual a2de::Line GetLeft();

    virtual a2de::Line GetBottom() const;
    virtual a2de::Line GetBottom();

    virtual void Draw(BITMAP* dest);

    virtual const a2de::Transform& GetTransform() const;
    virtual a2de::Transform& GetTransform();

protected:
private:
    enum POINTS {
        POINTS_TOP_LEFT,
        POINTS_TOP_RIGHT,
        POINTS_BOTTOM_LEFT,
        POINTS_BOTTOM_RIGHT,
    };
    a2de::Transform _transform_instance;
    a2de::Vector2D _half_extents;
    std::vector<a2de::Vector2D> _points;
    a2de::Color _color;

};

A2DE_END

#endif
