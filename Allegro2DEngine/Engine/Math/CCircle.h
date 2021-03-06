/**************************************************************************************************
// file:	Engine\Math\CCircle.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the circle class
 **************************************************************************************************/
#ifndef A2DE_CCIRCLE_H
#define A2DE_CCIRCLE_H

#include "../a2de_vals.h"
#include "CShape.h"

struct BITMAP;

A2DE_BEGIN

class Point;
class Line;
class Rectangle;
class Ellipse;
class Triangle;
class Arc;
class Polygon;
class Spline;
class Sector;
class Vector2D;


class Circle : public Shape {
public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">     The x coordinate.</param>
     * <param name="y">     The y coordinate.</param>
     * <param name="radius">The radius.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    Circle(double x, double y,  double radius, const a2de::Color& color, bool filled);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="center">The center.</param>
     * <param name="radius">The radius.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    Circle(const Vector2D& center, double radius, const a2de::Color& color, bool filled);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="circle">The circle.</param>
     **************************************************************************************************/
    Circle(const Circle& circle);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual ~Circle();

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="circle">The circle.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    Circle& operator=(const Circle& circle);

    /**************************************************************************************************
     * <summary>Equality operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are considered equivalent.</returns>
     **************************************************************************************************/
    bool operator==(const Circle& rhs) const;

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     **************************************************************************************************/
    bool operator!=(const Circle& rhs) const;

    /**************************************************************************************************
     * <summary>Less-than comparison operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is less than the second.</returns>
     **************************************************************************************************/
    bool operator<(const Circle& rhs) const;

    /**************************************************************************************************
     * <summary>Greater-than comparison operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is greater than to the second.</returns>
     **************************************************************************************************/
    bool operator>(const Circle& rhs) const;

    /**************************************************************************************************
     * <summary>Less-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is less than or equal to the second.</returns>
     **************************************************************************************************/
    bool operator<=(const Circle& rhs) const;

    /**************************************************************************************************
     * <summary>Greater-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is greater than or equal to the second.</returns>
     **************************************************************************************************/
    bool operator>=(const Circle& rhs) const;

    /**************************************************************************************************
     * <summary>Gets the radius.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The radius.</returns>
     **************************************************************************************************/
    double GetRadius() const;

    /**************************************************************************************************
     * <summary>Gets the radius.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The radius.</returns>
     **************************************************************************************************/
    double GetRadius();
    
    /**************************************************************************************************
     * <summary>Gets the diameter.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The diameter.</returns>
     **************************************************************************************************/
    double GetDiameter() const;

    /**************************************************************************************************
     * <summary>Gets the diameter.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The diameter.</returns>
     **************************************************************************************************/
    double GetDiameter();
    
    /**************************************************************************************************
     * <summary>Gets the circumference.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The circumference.</returns>
     **************************************************************************************************/
    double GetCircumference() const;

    /**************************************************************************************************
     * <summary>Gets the circumference.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The circumference.</returns>
     **************************************************************************************************/
    double GetCircumference();

    /**************************************************************************************************
     * <summary>Query if 'line' is tangent.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if tangent, false if not.</returns>
     **************************************************************************************************/
    bool IsTangent(const Line& line);

    /**************************************************************************************************
     * <summary>Sets an x coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     **************************************************************************************************/
    virtual void SetX(double x);

    /**************************************************************************************************
     * <summary>Sets a y coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    virtual void SetY(double y);

    /**************************************************************************************************
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    virtual void SetPosition(double x, double y);

    /**************************************************************************************************
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    virtual void SetPosition(const Vector2D& position);

    /**************************************************************************************************
     * <summary>Sets the radius.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="radius">The radius.</param>
     **************************************************************************************************/
    void SetRadius(double radius);

    /**************************************************************************************************
     * <summary>Query if this object intersects the given position.</summary>
     * <remarks>Casey Ugone, 8/23/2013.</remarks>
     * <param name="position">The position.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Vector2D& position) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given shape.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="shape">The shape.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Shape& shape) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given rectangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rectangle">The rectangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Rectangle& rectangle) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given circle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="circle">The circle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Circle& circle) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given ellipse.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="ellipse">The ellipse.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Ellipse& ellipse) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given triangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="triangle">The triangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Triangle& triangle) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="point">The point.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Point& point) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given line.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Line& line) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given arc.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="arc">The arc.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Arc& arc) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given polygon.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="polygon">The polygon.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Polygon& polygon) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given spline.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="spline">The spline.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Spline& spline) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given sector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="sector">The sector.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Sector& sector) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given circle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="circle">The circle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Circle& circle) const;

    /**************************************************************************************************
     * <summary>Draws.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dest">  [in,out] If non-null, destination for the.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    virtual void Draw(BITMAP* dest, const a2de::Color& color, bool filled);

    /**************************************************************************************************
     * <summary>Sets the dimensions.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="width"> The width.</param>
     * <param name="height">The height.</param>
     **************************************************************************************************/
    virtual void SetDimensions(double width, double height);

    /**************************************************************************************************
     * <summary>Sets the dimensions.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dimensions">The dimensions.</param>
     **************************************************************************************************/
    virtual void SetDimensions(const Vector2D& dimensions);

    /**************************************************************************************************
     * <summary>Sets a width.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="width">The width.</param>
     **************************************************************************************************/
    virtual void SetWidth(double width);

    /**************************************************************************************************
     * <summary>Sets a height.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="height">The height.</param>
     **************************************************************************************************/
    virtual void SetHeight(double height);

protected:

    /**************************************************************************************************
     * <summary>Calculates the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateArea();

    /**************************************************************************************************
     * <summary>Calculates the center.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateCenter();

    /**************************************************************************************************
     * <summary>Calculates the circumference.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void CalculateCircumference();
private:
    /// <summary> The radius </summary>
    double _radius;
    /// <summary> The circumference </summary>
    double _circumference;

};

A2DE_END

#endif