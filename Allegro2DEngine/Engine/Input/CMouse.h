/**************************************************************************************************
// file:	Engine\Input\CMouse.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the mouse class
 **************************************************************************************************/
#ifndef A2DE_CMOUSE_H
#define A2DE_CMOUSE_H

#include "../a2de_vals.h"
#include <bitset>
#include <utility>
#include <tuple>
#include "../Math/CPoint.h"
#include "../Math/CVector2D.h"
#include "../Math/CVector3D.h"

struct BITMAP;

A2DE_BEGIN

class Sprite;
class GameWindow;

/**************************************************************************************************
 * <summary>Mouse.</summary>
 * <remarks>Casey Ugone, 7/28/2011.</remarks>
 **************************************************************************************************/
class Mouse {

public:

    /**************************************************************************************************
     * <summary>Bitfield Values that represent the BUTTONS.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
    typedef enum BUTTONS {
        MOUSEBUTTON_ANY     = 0,                            //0x0000
		MOUSEBUTTON_BUTTON1  = 1,                           //0x0001
		MOUSEBUTTON_BUTTON2  = MOUSEBUTTON_BUTTON1 << 1,    //0x0002
		MOUSEBUTTON_BUTTON3  = MOUSEBUTTON_BUTTON2 << 1,    //0x0004
		MOUSEBUTTON_BUTTON4  = MOUSEBUTTON_BUTTON3 << 1,    //0x0008
		MOUSEBUTTON_BUTTON5  = MOUSEBUTTON_BUTTON4 << 1,    //0x0010
		MOUSEBUTTON_BUTTON6  = MOUSEBUTTON_BUTTON5 << 1,    //0x0020
		MOUSEBUTTON_BUTTON7  = MOUSEBUTTON_BUTTON6 << 1,    //0x0040
		MOUSEBUTTON_BUTTON8  = MOUSEBUTTON_BUTTON7 << 1,    //0x0080
		MOUSEBUTTON_BUTTON9  = MOUSEBUTTON_BUTTON8 << 1,    //0x0100
		MOUSEBUTTON_BUTTON10 = MOUSEBUTTON_BUTTON9 << 1,    //0x0200
		MOUSEBUTTON_BUTTON11 = MOUSEBUTTON_BUTTON10 << 1,   //0x0400
		MOUSEBUTTON_BUTTON12 = MOUSEBUTTON_BUTTON11 << 1,   //0x0800
		MOUSEBUTTON_BUTTON13 = MOUSEBUTTON_BUTTON12 << 1,   //0x1000
		MOUSEBUTTON_BUTTON14 = MOUSEBUTTON_BUTTON13 << 1,   //0x2000
		MOUSEBUTTON_BUTTON15 = MOUSEBUTTON_BUTTON14 << 1,   //0x4000
		MOUSEBUTTON_BUTTON16 = MOUSEBUTTON_BUTTON15 << 1,   //0x8000
    };

    /**************************************************************************************************
     * <summary>Creates the mouse with a default arrow pointer.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>null if it fails, else a pointer to a Mouse.</returns>
     **************************************************************************************************/
	static Mouse* CreateMouse();

    /**************************************************************************************************
     * <summary>Creates a mouse with a custom pointer.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="image"> [in] If non-null, the image.</param>
     * <param name="focusX">The focus x coordinate.</param>
     * <param name="focusY">The focus y coordinate.</param>
     * <returns>null if it fails, else a pointer to a Mouse.</returns>
     **************************************************************************************************/
    static Mouse* CreateMouse(Sprite* image, int focusX, int focusY);

    /**************************************************************************************************
     * <summary>Creates a mouse.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <param name="image"> [in,out] If non-null, the image.</param>
     * <param name="focus_coordinates">The focus coordinates.</param>
     * <returns>null if it fails, else a pointer to a Mouse.</returns>
     **************************************************************************************************/
    static Mouse* CreateMouse(Sprite* image, const a2de::Vector2D& focus_coordinates);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
    ~Mouse();

    /**************************************************************************************************
     * <summary>Gets the sprite of the mouse image.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>null if it fails, else the sprite.</returns>
     **************************************************************************************************/
    Sprite* GetSprite() const;

    /**************************************************************************************************
     * <summary>Gets the position as a Vector3D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The position 3d.</returns>
     **************************************************************************************************/
    Vector3D GetPosition3d() const;

    /**************************************************************************************************
     * <summary>Gets the position as a Vector3D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The position 3d.</returns>
     **************************************************************************************************/
    Vector3D GetPosition3d();

    /**************************************************************************************************
     * <summary>Gets the position as a Vector2D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The position 2d.</returns>
     **************************************************************************************************/
    Vector2D GetPosition2d() const;

    /**************************************************************************************************
     * <summary>Gets the position as a Vector2D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The position 2d.</returns>
     **************************************************************************************************/
    Vector2D GetPosition2d();

    /**************************************************************************************************
     * <summary>Get x coordinate.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The x coordinate.</returns>
     **************************************************************************************************/
    int GetX() const;

    /**************************************************************************************************
     * <summary>Get y coordinate.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The y coordinate.</returns>
     **************************************************************************************************/
    int GetY() const;

    /**************************************************************************************************
     * <summary>Get mouse wheel value.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The mouse wheel value..</returns>
     **************************************************************************************************/
    int GetZ() const;

    /**************************************************************************************************
     * <summary>Gets the mickeys as a Vector3D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The mickeys.</returns>
     **************************************************************************************************/
    Vector3D GetMickeys3d() const;

    /**************************************************************************************************
     * <summary>Gets the mickeys as a Vector3D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The mickeys.</returns>
     **************************************************************************************************/
    Vector3D GetMickeys3d();

    Vector2D GetMickeys2d() const;
    Vector2D GetMickeys2d();

    /**************************************************************************************************
     * <summary>Gets the change in x coordinates between Updates.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The mickey x coordinate.</returns>
     **************************************************************************************************/
    int GetMickeyX() const;

    /**************************************************************************************************
     * <summary>Gets the change in y coordinates between Updates..</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The mickey y coordinate.</returns>
     **************************************************************************************************/
    int GetMickeyY() const;

    /**************************************************************************************************
     * <summary>Gets the change in mouse wheel position between Updates.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The mickey z coordinate.</returns>
     **************************************************************************************************/
    int GetMickeyZ() const;

    /**************************************************************************************************
     * <summary>Gets the focus as a Vector2D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The focus.</returns>
     **************************************************************************************************/
    Vector2D GetFocus() const;

    /**************************************************************************************************
     * <summary>Gets the focus as a Vector2D object.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <returns>The focus.</returns>
     **************************************************************************************************/
    Vector2D GetFocus();

    /**************************************************************************************************
     * <summary>Gets the focus x coordinate.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The focus x coordinate.</returns>
     **************************************************************************************************/
	int GetFocusX() const;

    /**************************************************************************************************
     * <summary>Gets the focus y coordinate.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The focus y coordinate.</returns>
     **************************************************************************************************/
	int GetFocusY() const;

    /**************************************************************************************************
     * <summary>Gets the number of buttons.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The number of buttons.</returns>
     **************************************************************************************************/
	int GetNumButtons() const;

    /**************************************************************************************************
     * <summary>Queries if the image has changed.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>true if it has, false if not.</returns>
     **************************************************************************************************/
	bool ImageHasChanged() const;

    /**************************************************************************************************
     * <summary>Sets the x coordinate.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="x">The x coordinate.</param>
     **************************************************************************************************/
    void SetX(int x);

    /**************************************************************************************************
     * <summary>Sets the y coordinate.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    void SetY(int y);

    /**************************************************************************************************
     * <summary>Sets the z coordinate.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="z">The z coordinate.</param>
     **************************************************************************************************/
    void SetZ(int z);

    /**************************************************************************************************
     * <summary>Sets the position.</summary>
     * <remarks>Casey Ugone, 7/6/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    void SetPosition(int x, int y);

    /**************************************************************************************************
     * <summary>Sets the position.</summary>
     * <remarks>Casey Ugone, 7/6/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     * <param name="z">The z coordinate.</param>
     **************************************************************************************************/
    void SetPosition(int x, int y, int z);

    /**************************************************************************************************
     * <summary>Sets the position.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <param name="pos">The position as a Vector2D object.</param>
     **************************************************************************************************/
    void SetPosition(const a2de::Vector2D& pos);

    /**************************************************************************************************
     * <summary>Sets the position.</summary>
     * <remarks>Casey Ugone, 1/2/2013.</remarks>
     * <param name="pos">The position as a Vector3D object.</param>
     **************************************************************************************************/
    void SetPosition(const a2de::Vector3D& pos);

    /**************************************************************************************************
     * <summary>Sets the focus point.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
	void SetFocus(int x, int y);

    /**************************************************************************************************
     * <summary>Updates the mouse parameters.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
    void Update();

    /**************************************************************************************************
     * <summary>Queries if a Button was pressed.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="button">The button.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
	bool ButtonDown(Mouse::BUTTONS button);

    /**************************************************************************************************
     * <summary>Queries if a Button was held.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="button">The button.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
	bool ButtonPress(Mouse::BUTTONS button);

    /**************************************************************************************************
     * <summary>Queries if a Button was released.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="button">The button.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
	bool ButtonUp(Mouse::BUTTONS button);

    /**************************************************************************************************
     * <summary>Query if any button is in the Down state.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>true if a button is pressed, false if not.</returns>
     **************************************************************************************************/
	bool IsButtonPressed();

    /**************************************************************************************************
     * <summary>Sets the image.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="image"> [in] If non-null, the image, else clears the image.</param>
     * <param name="focusX">The focus x coordinate.</param>
     * <param name="focusY">The focus y coordinate.</param>
     **************************************************************************************************/
	void SetImage(Sprite* image, int focusX, int focusY);

    /**************************************************************************************************
     * <summary>Query if this object is visible.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>true if visible, false if not.</returns>
     **************************************************************************************************/
	bool IsVisible();

    /**************************************************************************************************
     * <summary>Sets the mouse's visible state.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="visible">true to show, false to hide.</param>
     **************************************************************************************************/
	void SetVisible(bool visible);

    /**************************************************************************************************
     * <summary>Shows the mouse on the specified BITMAP.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <remarks>Synonoumus with Show(dest, 0, 0, dest->w, dest->h)</remarks>
     * <param name="dest">[in] If non-null, destination for the Bitmap, else hides the mouse pointer.</param>
     **************************************************************************************************/
    void Show(BITMAP* dest);

    /**************************************************************************************************
     * <summary>Shows on the specified GameWindow's backbuffer.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="dest">[in]The Gamewindow destination.</param>
     **************************************************************************************************/
    void Show(const GameWindow& dest);

    /**************************************************************************************************
     * <summary>Hides the mouse pointer.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
	void Hide();

    /**************************************************************************************************
     * <summary>Sets the image to the default image.</summary>
     * <remarks>Casey Ugone, 12/11/2012.</remarks>
     **************************************************************************************************/
    void SetImageToDefault();

private:

    /// <summary> The position </summary>
    Vector3D _position;
    /// <summary> The mickeys </summary>
    Vector3D _mickeys;
    /// <summary> The focus </summary>
    Vector2D _focus;
    /// <summary> The image </summary>
    Sprite* _image;
    /// <summary> The previous button state </summary>
    std::bitset<17> _prevbuttons;
    /// <summary> The current button state </summary>
    std::bitset<17> _curbuttons;
    /// <summary> image needs updating status </summary>
    bool _dirtyImage;
    /// <summary> true to show, false to hide the image</summary>
    bool _isVisible;

    /// <summary> Number of buttons </summary>
    static int _numButtons;
    
    /// <summary> The default image </summary>
    static BITMAP* DEFAULT_MOUSE_IMAGE;

    /// <summary> The instance </summary>
    static Mouse* _instance;

    /**************************************************************************************************
     * <summary>Configs this object.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    static bool Config();

    /**************************************************************************************************
     * <summary>Creates the default image.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    static bool CreateDefaultImage();

    /**************************************************************************************************
     * <summary>Initializes a new instance of the Mouse class.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
    Mouse();

    /**************************************************************************************************
     * <summary>Initializes a new instance of the Mouse class.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="image"> [in] If non-null, the image.</param>
     * <param name="focusX">The focus x coordinate.</param>
     * <param name="focusY">The focus y coordinate.</param>
     **************************************************************************************************/
    Mouse(Sprite* image, int focusX, int focusY);

    /**************************************************************************************************
     * <summary>Gets a button's index value.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="button">The button.</param>
     * <returns>The button.</returns>
     **************************************************************************************************/
    int GetButtonIndex(Mouse::BUTTONS button);

};

A2DE_END

#endif