/**************************************************************************************************
// file:	Engine\Physics\CCamera.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the camera class
 **************************************************************************************************/
#ifndef A2DE_CCAMERA_H
#define A2DE_CCAMERA_H

#include "../a2de_vals.h"
#include "../Math/CVector2D.h"
#include "../GFX/CFont.h"
#include <iostream>
#include <string>

struct BITMAP;

A2DE_BEGIN

class World;
class Rectangle;
class Shape;
class Sprite;
class Color;

/**************************************************************************************************
 * <summary>Camera. </summary>
 * <remarks>Casey Ugone, 6/29/2012.</remarks>
 **************************************************************************************************/
class Camera {

public:

    /**************************************************************************************************
     * <summary>Default constructor.</summary>
     * <remarks>Casey Ugone, 6/24/2014.</remarks>
     **************************************************************************************************/
    Camera();

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="position">  The position.</param>
     * <param name="extents">The extents.</param>
     **************************************************************************************************/
    Camera(const Vector2D& position, const Vector2D& extents);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="parent">    The parent.</param>
     * <param name="position">  The position.</param>
     * <param name="extents">The extents.</param>
     **************************************************************************************************/
    Camera(const World& parent, const Vector2D& position, const Vector2D& extents);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="other">The other.</param>
     **************************************************************************************************/
    Camera(const Camera& other);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     **************************************************************************************************/
    ~Camera();

    /**************************************************************************************************
     * <summary>Gets the parent of this item.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The parent.</returns>
     **************************************************************************************************/
    const World* const GetParent() const;

    /**************************************************************************************************
     * <summary>Gets the parent of this item.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>null if it fails, else the parent.</returns>
     **************************************************************************************************/
    const World* GetParent();

    /**************************************************************************************************
     * <summary>Sets a parent.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="parent">The parent.</param>
     **************************************************************************************************/
    void SetParent(const World& parent);

    /**************************************************************************************************
     * <summary>Get x coordinate.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The x coordinate.</returns>
     **************************************************************************************************/
    double GetX() const;

    /**************************************************************************************************
     * <summary>Get x coordinate.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The x coordinate.</returns>
     **************************************************************************************************/
    double GetX();

    /**************************************************************************************************
     * <summary>Get y coordinate.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The y coordinate.</returns>
     **************************************************************************************************/
    double GetY() const;

    /**************************************************************************************************
     * <summary>Get y coordinate.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The y coordinate.</returns>
     **************************************************************************************************/
    double GetY();

    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    const Vector2D& GetPosition() const;

    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    Vector2D& GetPosition();

    /**************************************************************************************************
     * <summary>Sets an x coordinate.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     **************************************************************************************************/
    void SetX(double x);

    /**************************************************************************************************
     * <summary>Sets a y coordinate.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    void SetY(double y);

    /**************************************************************************************************
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    void SetPosition(const Vector2D& position);

    /**************************************************************************************************
     * <summary>Gets the extents.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The extents.</returns>
     **************************************************************************************************/
    const Vector2D& GetExtents() const;

    /**************************************************************************************************
     * <summary>Gets the extents.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The extents.</returns>
     **************************************************************************************************/
    Vector2D& GetExtents();

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    Camera& operator=(const Camera& rhs);

    /**************************************************************************************************
     * <summary>Camera to world position.</summary>
     * <remarks>Casey Ugone, 7/28/2012.</remarks>
     * <param name="cam">            The camera.</param>
     * <param name="screen_position">The screen position.</param>
     * <returns>.</returns>
     **************************************************************************************************/
    static Vector2D CameraToWorldPosition(const Camera& cam, const Vector2D& screen_position);

    /**************************************************************************************************
     * <summary>World to camera position.</summary>
     * <remarks>Casey Ugone, 7/28/2012.</remarks>
     * <param name="cam">           The camera.</param>
     * <param name="world_position">The world position.</param>
     * <returns>.</returns>
     **************************************************************************************************/
    static Vector2D WorldToCameraPosition(const Camera& cam, const Vector2D& world_position);

    /**************************************************************************************************
     * <summary>Starts a camera render.</summary>
     * <remarks>Casey Ugone, 9/8/2012.</remarks>
     **************************************************************************************************/
    void StartRenderView();

    /**************************************************************************************************
     * <summary>Ends a camera render.</summary>
     * <remarks>Casey Ugone, 9/8/2012.</remarks>
     **************************************************************************************************/
    void EndRenderView();

    /**************************************************************************************************
     * <summary>Renders the camera's view.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dest">    [in,out] The destination BITMAP.</param>
     * <param name="position">Location to draw the view on the destination.</param>
     **************************************************************************************************/
    void RenderView(BITMAP* dest, const Vector2D& position);

    /**************************************************************************************************
     * <summary>Renders the view described by dest.</summary>
     * <remarks>Casey Ugone, 2/8/2013.</remarks>
     * <param name="dest">[in,out] If non-null, destination BITMAP.</param>
     * <remarks>Synonymous with RenderView(dest, Vector2D(0.0, 0.0))</remarks>
     **************************************************************************************************/
    void RenderView(BITMAP* dest);

    /**************************************************************************************************
     * <summary>Renders argument the text.</summary>
     * <remarks>Casey Ugone, 9/8/2012.</remarks>
     * <param name="font_type">           [in,out] If non-null, type of the font.</param>
     * <param name="x">                   The x coordinate.</param>
     * <param name="y">                   The y coordinate.</param>
     * <param name="message_line">        The message line.</param>
     * <param name="foreground_color">    The foreground color.</param>
     **************************************************************************************************/
    void RenderText(FONT* font_type, int x, int y, const std::string& message_line, const a2de::Color& foreground_color);

    /**************************************************************************************************
     * <summary>Renders the text.</summary>
     * <remarks>Casey Ugone, 8/21/2013.</remarks>
     * <param name="font_type">       [in,out] If non-null, type of the font.</param>
     * <param name="x">               The x coordinate.</param>
     * <param name="y">               The y coordinate.</param>
     * <param name="message_line">    The message line.</param>
     * <param name="foreground_color">The foreground color.</param>
     * <param name="background_color">The background color.</param>
     **************************************************************************************************/
    void RenderText(FONT* font_type, int x, int y, const std::string& message_line, const a2de::Color& foreground_color, const a2de::Color& background_color);

    /**************************************************************************************************
     * <summary>Renders the object described by sprite.</summary>
     * <remarks>Casey Ugone, 2/8/2013.</remarks>
     * <param name="sprite">[in,out] If non-null, the sprite.</param>
     **************************************************************************************************/
    void RenderObject(Sprite* sprite);

    /**************************************************************************************************
     * <summary>Renders the object described by shape.</summary>
     * <remarks>Casey Ugone, 2/8/2013.</remarks>
     * <param name="shape">[in,out] If non-null, the shape.</param>
     **************************************************************************************************/
    void RenderObject(Shape* shape);

    /**************************************************************************************************
     * <summary>Gets the buffer.</summary>
     * <remarks>Casey Ugone, 9/8/2012.</remarks>
     * <returns>null if it fails, else the buffer.</returns>
     **************************************************************************************************/
    BITMAP* GetBuffer() const;

    /**************************************************************************************************
     * <summary>Gets the buffer.</summary>
     * <remarks>Casey Ugone, 9/8/2012.</remarks>
     * <returns>null if it fails, else the buffer.</returns>
     **************************************************************************************************/
    BITMAP* GetBuffer();

protected:
private:
    /// <summary> The parent </summary>
    const World* _parent;
    /// <summary> The position </summary>
    Vector2D _position;
    /// <summary> The extents </summary>
    Vector2D _extents;

    BITMAP* _buffer;
};

A2DE_END

#endif