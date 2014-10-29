/**************************************************************************************************
// file:	Engine\Math\CTriangle.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the triangle class
 **************************************************************************************************/
#ifndef A2DE_CTRIANGLE_H
#define A2DE_CTRIANGLE_H

#include "../a2de_vals.h"

#include "CShape.h"

#include <tuple>

#include "CPoint.h"
#include "CLine.h"

A2DE_BEGIN


class Rectangle;
class Circle;
class Ellipse;
class Arc;
class Polygon;
class Spline;
class Sector;

class Triangle : public Shape {
public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x1">    The first x value.</param>
     * <param name="y1">    The first y value.</param>
     * <param name="x2">    The second x value.</param>
     * <param name="y2">    The second y value.</param>
     * <param name="x3">    The third double.</param>
     * <param name="y3">    The third double.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3, const a2de::Color& color, bool filled);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="pointOne">  The point one.</param>
     * <param name="pointTwo">  The point two.</param>
     * <param name="pointThree">The point three.</param>
     * <param name="color">     The color.</param>
     * <param name="filled">    true to filled.</param>
     **************************************************************************************************/
    Triangle(const Vector2D& pointOne, const Vector2D& pointTwo, const Vector2D& pointThree, const a2de::Color& color, bool filled);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="triangle">The triangle.</param>
     **************************************************************************************************/
    Triangle(const Triangle& triangle);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual ~Triangle();
    
    /**************************************************************************************************
     * <summary>Get x coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The x coordinate.</returns>
     **************************************************************************************************/
    virtual double GetX() const;

    /**************************************************************************************************
     * <summary>Get x coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The x coordinate.</returns>
     **************************************************************************************************/
    virtual double GetX();
    
    /**************************************************************************************************
     * <summary>Get y coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The y coordinate.</returns>
     **************************************************************************************************/
    virtual double GetY() const;

    /**************************************************************************************************
     * <summary>Get y coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The y coordinate.</returns>
     **************************************************************************************************/
    virtual double GetY();
    
    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    virtual const Vector2D& GetPosition() const;

    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    virtual Vector2D& GetPosition();

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
     * <summary>Query if this object intersects the given position.</summary>
     * <remarks>Casey Ugone, 8/23/2013.</remarks>
     * <param name="position">The position.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const a2de::Vector2D& position) const;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given shape.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="shape">The shape.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Shape& shape) const;

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
     * <summary>Query if this object fully contains the given ellipse.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="ellipse">The ellipse.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Ellipse& ellipse) const;

    /**************************************************************************************************
     * <summary>Draws the triangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dest">  [in,out] If non-null, destination BITMAP.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    virtual void Draw(BITMAP* dest, const a2de::Color& color, bool filled);

    /**************************************************************************************************
     * <summary>Gets the point a.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The point a.</returns>
     **************************************************************************************************/
    const Vector2D& GetPointA() const;

    /**************************************************************************************************
     * <summary>Gets the point a.</summary>
     * <remarks>Casey Ugone, 5/3/2013.</remarks>
     * <returns>The point a.</returns>
     **************************************************************************************************/
    Vector2D& GetPointA();

    /**************************************************************************************************
     * <summary>Gets the point b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The point b.</returns>
     **************************************************************************************************/
    const Vector2D& GetPointB() const;

    /**************************************************************************************************
     * <summary>Gets the point b.</summary>
     * <remarks>Casey Ugone, 5/3/2013.</remarks>
     * <returns>The point b.</returns>
     **************************************************************************************************/
    Vector2D& GetPointB();

    /**************************************************************************************************
     * <summary>Gets the point c.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The point c.</returns>
     **************************************************************************************************/
    const Vector2D& GetPointC() const;

    /**************************************************************************************************
     * <summary>Gets the point c.</summary>
     * <remarks>Casey Ugone, 5/3/2013.</remarks>
     * <returns>The point c.</returns>
     **************************************************************************************************/
    Vector2D& GetPointC();

    /**************************************************************************************************
     * <summary>Gets the line a b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The line a b.</returns>
     **************************************************************************************************/
    Vector2D GetLineAB() const;

    /**************************************************************************************************
     * <summary>Gets the line bc.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The line bc.</returns>
     **************************************************************************************************/
    Vector2D GetLineBC() const;

    /**************************************************************************************************
     * <summary>Gets the line ca.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The line ca.</returns>
     **************************************************************************************************/
    Vector2D GetLineCA() const;

    /**************************************************************************************************
     * <summary>Gets the side a.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The side a.</returns>
     **************************************************************************************************/
    double GetSideA() const;

    /**************************************************************************************************
     * <summary>Gets the side b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The side b.</returns>
     **************************************************************************************************/
    double GetSideB() const;

    /**************************************************************************************************
     * <summary>Gets the side c.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The side c.</returns>
     **************************************************************************************************/
    double GetSideC() const;

    /**************************************************************************************************
     * <summary>Gets the angle a.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The angle a.</returns>
     **************************************************************************************************/
    double GetAngleA() const;

    /**************************************************************************************************
     * <summary>Gets the angle b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The angle b.</returns>
     **************************************************************************************************/
    double GetAngleB() const;

    /**************************************************************************************************
     * <summary>Gets the angle c.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The angle c.</returns>
     **************************************************************************************************/
    double GetAngleC() const;

    /**************************************************************************************************
     * <summary>Query if this object is right triangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if right triangle, false if not.</returns>
     **************************************************************************************************/
    bool IsRightTriangle() const;

    /**************************************************************************************************
     * <summary>Sets a point a.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    void SetPointA(const Vector2D& position);

    /**************************************************************************************************
     * <summary>Sets a point b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    void SetPointB(const Vector2D& position);

    /**************************************************************************************************
     * <summary>Sets a point c.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    void SetPointC(const Vector2D& position);

    /**************************************************************************************************
     * <summary>Sets a point a.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="A">a.</param>
     **************************************************************************************************/
    void SetPointA(const Point& A);

    /**************************************************************************************************
     * <summary>Sets a point b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="B">The.</param>
     **************************************************************************************************/
    void SetPointB(const Point& B);

    /**************************************************************************************************
     * <summary>Sets a point c.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="C">The.</param>
     **************************************************************************************************/
    void SetPointC(const Point& C);

    /**************************************************************************************************
     * <summary>Sets a point a.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    void SetPointA(double x, double y);

    /**************************************************************************************************
     * <summary>Sets a point b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    void SetPointB(double x, double y);

    /**************************************************************************************************
     * <summary>Sets a point c.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    void SetPointC(double x, double y);

    /**************************************************************************************************
     * <summary>Sets the points.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="xA">The x coordinate a.</param>
     * <param name="yA">The y coordinate a.</param>
     * <param name="xB">The x coordinate b.</param>
     * <param name="yB">The y coordinate b.</param>
     * <param name="xC">The x coordinate c.</param>
     * <param name="yC">The y coordinate c.</param>
     **************************************************************************************************/
    void SetPoints(double xA, double yA, double xB, double yB, double xC, double yC);

    /**************************************************************************************************
     * <summary>Sets the points.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="pointA">The point a.</param>
     * <param name="pointB">The point b.</param>
     * <param name="pointC">The point c.</param>
     **************************************************************************************************/
    void SetPoints(const Vector2D& pointA, const Vector2D& pointB, const Vector2D& pointC);

    /**************************************************************************************************
     * <summary>Sets the points.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="A">Point A.</param>
     * <param name="B">Point B.</param>
     * <param name="C">Point C.</param>
     **************************************************************************************************/
    void SetPoints(const Point& A, const Point& B, const Point& C);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A deep copy of this object.</returns>
     **************************************************************************************************/
    Triangle& operator=(const Triangle& rhs);

protected:

    /**************************************************************************************************
     * <summary>Calculates the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateArea();

    /**************************************************************************************************
     * <summary>Calculates the lines.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="pointOne">  The point one.</param>
     * <param name="pointTwo">  The point two.</param>
     * <param name="pointThree">The point three.</param>
     **************************************************************************************************/
    void CalculateLines(const Point& pointOne, const Point& pointTwo, const Point& pointThree);

    /**************************************************************************************************
     * <summary>Calculates the dimensions.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void CalculateDimensions();

    /// <summary> The points </summary>
    Vector2D _pointA;
    Vector2D _pointB;
    Vector2D _pointC;

};

A2DE_END

#endif