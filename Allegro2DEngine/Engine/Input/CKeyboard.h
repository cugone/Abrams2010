/**************************************************************************************************
// file:	Engine\Input\CKeyboard.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the keyboard class
 **************************************************************************************************/
#ifndef A2DE_CKEYBOARD_H
#define A2DE_CKEYBOARD_H

#include "../a2de_vals.h"
#include <allegro/keyboard.h>
#include <bitset>
#include <string>

A2DE_BEGIN

/**************************************************************************************************
 * <summary>Keyboard.</summary>
 * <remarks>Casey Ugone, 7/28/2011.</remarks>
 **************************************************************************************************/
class Keyboard {

public:

    /**************************************************************************************************
     * <summary>Creates the keyboard.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>null if it fails, else a valid keyboard object.</returns>
     **************************************************************************************************/
	static Keyboard* CreateKeyboard();

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
    ~Keyboard();

    /**************************************************************************************************
     * <summary>Queries if a Key was pressed.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="scancode">The scancode.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool KeyDown(int scancode);

    /**************************************************************************************************
     * <summary>Queries if a Key was held.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="scancode">The scancode.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool KeyPress(int scancode);

    /**************************************************************************************************
     * <summary>Queries if a Key was released.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <param name="scancode">The scancode.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool KeyUp(int scancode);

    /**************************************************************************************************
     * <summary>Query if this any key is pressed.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>true if key pressed, false if not.</returns>
     **************************************************************************************************/
    bool IsKeyPressed();

    /**************************************************************************************************
     * <summary>Gets the next key by scancode.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The next key by its scancode.</returns>
     **************************************************************************************************/
    int GetNextKeyByScancode();

    /**************************************************************************************************
     * <summary>Gets the next key by ascii value.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     * <returns>The next key by ascii.</returns>
     **************************************************************************************************/
    int GetNextKeyByAscii();

    /**************************************************************************************************
     * <summary>Updates this object.</summary>
     * <remarks>Casey Ugone, 7/28/2011.</remarks>
     **************************************************************************************************/
    void Update();
private:
    /// <summary> The previous key states.</summary>
    std::bitset<KEY_MAX> _prevKey;
    /// <summary> The current key states</summary>
    std::bitset<KEY_MAX> _curKey;

    /**************************************************************************************************
     * <summary>Default constructor. Use Named Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    Keyboard();
    /// <summary> The Singleton instance </summary>
    static Keyboard* _instance;

    /**************************************************************************************************
     * <summary>Configs this object.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    static bool Config();
};

A2DE_END

#endif
