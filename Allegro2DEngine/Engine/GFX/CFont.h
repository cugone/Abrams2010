/**************************************************************************************************
// file:	Engine\GFX\CFont.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the font class
 **************************************************************************************************/
#ifndef A2DE_CFONT_H
#define A2DE_CFONT_H

#include "../a2de_vals.h"
#include <allegro/gfx.h>
#include <allegro/palette.h>
#include <allegro/font.h>
#include <allegro/file.h>
#include <allegro/text.h>

#include <string>

A2DE_BEGIN

class Font {

public:

    /**************************************************************************************************
     * <summary>Creates a bitmapped font.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <remarks>Currently only .bmp files are supported.</remarks>
     * <param name="file">The file path and filename of the font to load.</param>
     * <returns>A pointer to a created Font object, nullptr if the memory allocation fails.</returns>
     **************************************************************************************************/
	static Font* CreateFont(std::string file);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     **************************************************************************************************/
	~Font();

    /**************************************************************************************************
     * <summary>Returns a pointer to the underlying Allegro FONT structure.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>null if it fails, else the font.</returns>
     **************************************************************************************************/
	FONT* GetFont() const;

    /**************************************************************************************************
     * <summary>Returns the filename of the font object.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>null if it fails, else the filename.</returns>
     **************************************************************************************************/
	std::string GetFilename() const;

    /**************************************************************************************************
     * <summary>Returns the height of this FONT.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <returns>The height in pixels.</returns>
     **************************************************************************************************/
	unsigned int GetHeight() const;

    /**************************************************************************************************
     * <summary>Returns the height of any FONT.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="fontobj">[in,out] If non-null, the fontobj.</param>
     * <returns>The height in pixels.</returns>
     **************************************************************************************************/
	static unsigned int GetHeight(FONT* fontobj);

    /**************************************************************************************************
     * <summary>Returns the length of the specified text in pixels using this FONT.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="text">The text to measure.</param>
     * <returns>The length in pixels.</returns>
     **************************************************************************************************/
	unsigned long GetLength(std::string text);

    /**************************************************************************************************
     * <summary>Returns the length of the specified text in pixels using any FONT.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="fontobj">[in,out] If non-null, the fontobj.</param>
     * <param name="text">   The text to measure.</param>
     * <returns>The length in pixels.</returns>
     **************************************************************************************************/
	static unsigned long GetLength(FONT* fontobj, std::string text);

    /**************************************************************************************************
     * <summary>Dynamically changes the font during run-time.</summary>
     * <remarks>Casey Ugone, 6/29/2012.</remarks>
     * <param name="file">The bmp file to load.</param>
     **************************************************************************************************/
	void AdjustFont(std::string file);

protected:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="file">The file.</param>
     **************************************************************************************************/
    Font(std::string file);

private:
    /// <summary> The file </summary>
    std::string _file;
    /// <summary> The font </summary>
    FONT* _font;
    /// <summary> The height </summary>
    unsigned int _height;

    /**************************************************************************************************
     * <summary>Default constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    Font();

};

A2DE_END

#endif