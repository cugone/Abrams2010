/**************************************************************************************************
// file:	Engine\GFX\CColor.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the color class
 **************************************************************************************************/
#ifndef A2DE_COLOR_H
#define A2DE_COLOR_H

#include "../a2de_vals.h"
#include <allegro/color.h>

A2DE_BEGIN

class Color {
public:

    /**************************************************************************************************
     * <summary>Default constructor. Creates a color with a value equal to BLACK.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    Color();

    /**************************************************************************************************
     * <summary>Constructor. Creates a color equivalent to value. RGB to BGR conversion is gaurenteed.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="value">The value.</param>
     **************************************************************************************************/
    Color(int value);

    /**************************************************************************************************
     * <summary>Constructor. Creates a color with specific RGB values.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="r">The red value.</param>
     * <param name="g">The green value.</param>
     * <param name="b">The blue value.</param>
     **************************************************************************************************/
    Color(unsigned char r, unsigned char g, unsigned char b);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    ~Color();

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="other">The other color.</param>
     **************************************************************************************************/
    Color(const Color& other);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side color.</param>
     * <returns>A deep copy of the object.</returns>
     **************************************************************************************************/
    Color& operator=(const Color& rhs);

    /**************************************************************************************************
     * <summary>Sets the red value of this object.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="r">The.</param>
     **************************************************************************************************/
    void SetRed(unsigned char r);

    /**************************************************************************************************
     * <summary>Gets the red value of this object.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <returns>The red.</returns>
     **************************************************************************************************/
    unsigned char GetRed() const;

    /**************************************************************************************************
     * <summary>Gets the red value of this object.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <returns>The red.</returns>
     **************************************************************************************************/
    unsigned char GetRed();

    /**************************************************************************************************
     * <summary>Sets the green value of this object.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="g">The.</param>
     **************************************************************************************************/
    void SetGreen(unsigned char g);

    /**************************************************************************************************
     * <summary>Gets the green value of this object.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <returns>The green.</returns>
     **************************************************************************************************/
    unsigned char GetGreen() const;

    /**************************************************************************************************
     * <summary>Gets the green value of this object.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <returns>The green.</returns>
     **************************************************************************************************/
    unsigned char GetGreen();

    /**************************************************************************************************
     * <summary>Sets the blue value of this object.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="b">The.</param>
     **************************************************************************************************/
    void SetBlue(unsigned char b);

    /**************************************************************************************************
     * <summary>Gets the blue value of this object.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <returns>The blue.</returns>
     **************************************************************************************************/
    unsigned char GetBlue() const;

    /**************************************************************************************************
     * <summary>Gets the blue value of this object.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <returns>The blue.</returns>
     **************************************************************************************************/
    unsigned char GetBlue();

    /**************************************************************************************************
     * <summary>Implicit Conversion function. Used to seamlessly integrate with Allegro's
     * functions that require a color to be an int.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    operator int() const;

    /**************************************************************************************************
    * <summary>Implicit Conversion function. Used to seamlessly integrate with Allegro's
    * functions that require a color to be an int.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    operator int();

    /**************************************************************************************************
     * <summary>Equality operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the color values are considered equivalent.</returns>
     **************************************************************************************************/
    bool operator==(const Color& rhs) const;

    /**************************************************************************************************
     * <summary>Equality operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the color values are considered equivalent.</returns>
     **************************************************************************************************/
    bool operator==(const Color& rhs);

    /**************************************************************************************************
     * <summary>Non-member Equality operator. Allows comparison of a Color to an int where the syntax is int == Color.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="lhs">The integer to compare.</param>
     * <param name="rhs">The color to compare.</param>
     * <returns>true if the parameters are considered equivalent.</returns>
     **************************************************************************************************/
    friend bool operator==(int lhs, const Color& rhs);

    /**************************************************************************************************
     * <summary>Inequality operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are not considered equivalent.</returns>
     **************************************************************************************************/
    bool operator!=(const Color& rhs) const;

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are not considered equivalent.</returns>
     **************************************************************************************************/
    bool operator!=(const Color& rhs);

    /**************************************************************************************************
     * <summary>Non-member Inequality operator. Allows comparison of a Color to an int where the syntax is int != Color.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="lhs">The first instance to compare.</param>
     * <param name="rhs">The second instance to compare.</param>
     * <returns>true if the parameters are not considered equivalent.</returns>
     **************************************************************************************************/
    friend bool operator!=(int lhs, const Color& rhs);

    /**************************************************************************************************
     * <summary>Less-than comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is less than the second.</returns>
     **************************************************************************************************/
    bool operator<(const Color& rhs) const;

    /**************************************************************************************************
     * <summary>Less-than comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is less than the second.</returns>
     **************************************************************************************************/
    bool operator<(const Color& rhs);

    /**************************************************************************************************
     * <summary>Less-than comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="lhs">The first instance to compare.</param>
     * <param name="rhs">The second instance to compare.</param>
     * <returns>true if the first parameter is less than the second.</returns>
     **************************************************************************************************/
    friend bool operator<(int lhs, const Color& rhs);

    /**************************************************************************************************
     * <summary>Less-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is less than or equal to the second.</returns>
     **************************************************************************************************/
    bool operator<=(const Color& rhs) const;

    /**************************************************************************************************
     * <summary>Less-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is less than or equal to the second.</returns>
     **************************************************************************************************/
    bool operator<=(const Color& rhs);

    /**************************************************************************************************
     * <summary>Less-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="lhs">The first instance to compare.</param>
     * <param name="rhs">The second instance to compare.</param>
     * <returns>true if the first parameter is less than or equal to the second.</returns>
     **************************************************************************************************/
    friend bool operator<=(int lhs, const Color& rhs);

    /**************************************************************************************************
     * <summary>Greater-than comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is greater than to the second.</returns>
     **************************************************************************************************/
    bool operator>(const Color& rhs) const;

    /**************************************************************************************************
     * <summary>Greater-than comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is greater than to the second.</returns>
     **************************************************************************************************/
    bool operator>(const Color& rhs);

    /**************************************************************************************************
     * <summary>Greater-than comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="lhs">The first instance to compare.</param>
     * <param name="rhs">The second instance to compare.</param>
     * <returns>true if the first parameter is greater than to the second.</returns>
     **************************************************************************************************/
    friend bool operator>(int lhs, const Color& rhs);

    /**************************************************************************************************
     * <summary>Greater-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is greater than or equal to the second.</returns>
     **************************************************************************************************/
    bool operator>=(const Color& rhs) const;

    /**************************************************************************************************
     * <summary>Greater-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is greater than or equal to the second.</returns>
     **************************************************************************************************/
    bool operator>=(const Color& rhs);

    /**************************************************************************************************
     * <summary>Greater-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     * <param name="lhs">The first instance to compare.</param>
     * <param name="rhs">The second instance to compare.</param>
     * <returns>true if the first parameter is greater than or equal to the second.</returns>
     **************************************************************************************************/
    friend bool operator>=(int lhs, const Color& rhs);


    //Pre-defined colors for ease-of-use. Taken from http://en.wikipedia.org/wiki/Web_colors#HTML_color_names
    //Included are the European spellings of some colors....except "colour".

    /**************************************************************************************************
     * <summary>Returns the color white.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color WHITE();

    /**************************************************************************************************
     * <summary>Returns the color silver.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color SILVER();

    /**************************************************************************************************
     * <summary>Returns the color light grey.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color LIGHT_GREY();

    /**************************************************************************************************
     * <summary>Returns the color light gray.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color LIGHT_GRAY();

    /**************************************************************************************************
     * <summary>Returns the color grey.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color GREY();

    /**************************************************************************************************
     * <summary>Returns the color dark grey.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color DARK_GREY();

    /**************************************************************************************************
     * <summary>Returns the color dark gray.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color DARK_GRAY();

    /**************************************************************************************************
     * <summary>Returns the color gray.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color GRAY();

    /**************************************************************************************************
     * <summary>Returns the color black.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color BLACK();

    /**************************************************************************************************
     * <summary>Returns the color red.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color RED();

    /**************************************************************************************************
     * <summary>Returns the color maroon.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color MAROON();

    /**************************************************************************************************
     * <summary>Returns the color yellow.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color YELLOW();

    /**************************************************************************************************
     * <summary>Returns the color olive.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color OLIVE();

    /**************************************************************************************************
     * <summary>Returns the color lime.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color LIME();

    /**************************************************************************************************
     * <summary>Returns the color green.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color GREEN();

    /**************************************************************************************************
     * <summary>Returns the color cyan.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color CYAN();

    /**************************************************************************************************
     * <summary>Returns the color aqua.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color AQUA();

    /**************************************************************************************************
     * <summary>Returns the color teal.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color TEAL();

    /**************************************************************************************************
     * <summary>Returns the color blue.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color BLUE();

    /**************************************************************************************************
     * <summary>Returns the color navy blue.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color NAVY_BLUE();

    /**************************************************************************************************
     * <summary>Returns the color magenta.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color MAGENTA();

    /**************************************************************************************************
     * <summary>Returns the color fuchsia.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color FUCHSIA();

    /**************************************************************************************************
     * <summary>Returns the color purple.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color PURPLE();

    /**************************************************************************************************
     * <summary>Returns the color orange.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color ORANGE();

    /**************************************************************************************************
     * <summary>Returns the color hot pink.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color HOT_PINK();

    /**************************************************************************************************
     * <summary>Returns the color lime green.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color LIME_GREEN();

    /**************************************************************************************************
     * <summary>Returns the color seafoam green.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color SEAFOAM_GREEN();

    /**************************************************************************************************
     * <summary>Returns the color violet.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color VIOLET();

    /**************************************************************************************************
     * <summary>Returns the color sky blue.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color SKY_BLUE();

    /**************************************************************************************************
     * <summary>Returns the color brown.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color BROWN();

    /**************************************************************************************************
     * <summary>Returns the color pink.</summary>
     * <remarks>Casey Ugone, 1/16/2013.</remarks>
     **************************************************************************************************/
    static const Color PINK();

protected:
private:
    /// <summary> The numerical color value </summary>
    int _value;

};

A2DE_END

#endif