/**************************************************************************************************
// file:	Engine\Physics\IBoundingBox.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the IBoundingBox interface
 **************************************************************************************************/
#ifndef A2DE_ADTBOUNDINGBOX_H
#define A2DE_ADTBOUNDINGBOX_H

#include "../a2de_vals.h"

#include <allegro/gfx.h>
#include <allegro/draw.h>

A2DE_BEGIN

class Line;
class Vector2D;
class Transform;

class IBoundingBox {
public:
    virtual a2de::Line GetTop() const =0;
    virtual a2de::Line GetTop() =0;

    virtual a2de::Line GetBottom() const =0;
    virtual a2de::Line GetBottom() =0;

    virtual a2de::Line GetLeft() const =0;
    virtual a2de::Line GetLeft() =0;

    virtual a2de::Line GetRight() const =0;
    virtual a2de::Line GetRight() =0;

    virtual void SetHalfExtents(const a2de::Vector2D& half_extents)=0;
    virtual const a2de::Vector2D& GetHalfExtents() const =0;
    virtual a2de::Vector2D& GetHalfExtents() =0;

    virtual const a2de::Transform& GetTransform() const =0;
    virtual a2de::Transform& GetTransform() =0;

    virtual void Draw(BITMAP* dest)=0;
    virtual ~IBoundingBox() { /* DO NOTHING */ }
protected:
private:
};

A2DE_END

#endif