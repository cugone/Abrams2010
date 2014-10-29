/**************************************************************************************************
// file:	Engine\Math\CVector3D.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the vector 3 d class
 **************************************************************************************************/
#ifndef A2DE_CVECTOR3D_H
#define A2DE_CVECTOR3D_H


#include "../a2de_vals.h"


A2DE_BEGIN

class Vector2D;
class Vector4D;

class Vector3D {

public:

    /**************************************************************************************************
     * <summary>Default constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    Vector3D();

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    Vector3D(double x, double y);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     * <param name="z">The z coordinate.</param>
     **************************************************************************************************/
    Vector3D(double x, double y, double z);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="v3d">The other 3D vector.</param>
     **************************************************************************************************/
    Vector3D(const Vector3D& v3d);

    /**************************************************************************************************
     * <summary>Constructor. Constructs a 2D Vector from a 3D Vector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <remarks>The resulting vecotr will be [x, y, 0].</remarks>
     * <param name="v2d">The 2D Vector.</param>
     **************************************************************************************************/
    Vector3D(const Vector2D& v2d);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     * <param name="v4d">The 4D Vector.</param>
     **************************************************************************************************/
    //Vector3D(const Vector4D& v4d);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    ~Vector3D();

    /**************************************************************************************************
     * <summary>Get x coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The x coordinate.</returns>
     **************************************************************************************************/
    double GetX() const;

    /**************************************************************************************************
     * <summary>Get y coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The y coordinate.</returns>
     **************************************************************************************************/
    double GetY() const;

    /**************************************************************************************************
     * <summary>Get z coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The z coordinate.</returns>
     **************************************************************************************************/
    double GetZ() const;

    /**************************************************************************************************
     * <summary>Get x coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The x coordinate.</returns>
     **************************************************************************************************/
    double GetX();

    /**************************************************************************************************
     * <summary>Get y coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The y coordinate.</returns>
     **************************************************************************************************/
    double GetY();

    /**************************************************************************************************
     * <summary>Get z coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The z coordinate.</returns>
     **************************************************************************************************/
    double GetZ();

    /**************************************************************************************************
     * <summary>Gets the length.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The length.</returns>
     **************************************************************************************************/
    double GetLength() const;

    /**************************************************************************************************
     * <summary>Gets the length.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The length.</returns>
     **************************************************************************************************/
    double GetLength();

    /**************************************************************************************************
     * <summary>Gets the length squared.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The length squared.</returns>
     **************************************************************************************************/
    double GetLengthSquared() const;

    /**************************************************************************************************
     * <summary>Gets the length squared.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The length squared.</returns>
     **************************************************************************************************/
    double GetLengthSquared();

    /**************************************************************************************************
     * <summary>Gets the angle of the vector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The angle in radians.</returns>
     **************************************************************************************************/
    double GetAngle() const;

    /**************************************************************************************************
     * <summary>Gets the angle of the vector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The angle in radians.</returns>
     **************************************************************************************************/
    double GetAngle();

    /**************************************************************************************************
     * <summary>Returns the result of Normalizing the vector.</summary>
     * <remarks>Casey Ugone, 6/24/2013.</remarks>
     * <returns>.</returns>
     **************************************************************************************************/
    Vector3D Normalize() const;

    /**************************************************************************************************
     * <summary>Normalizes the vector in-place.</summary>
     * <remarks>Casey Ugone, 6/24/2013.</remarks>
     * <param name="v">[in,out] The v.</param>
     **************************************************************************************************/
    static void Normalize(Vector3D& v);

    /**************************************************************************************************
     * <summary>Cross product between b and this vector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="b">The b vector.</param>
     * <returns>The result vector.</returns>
     **************************************************************************************************/
    Vector3D CrossProduct(const Vector3D& b);

    /**************************************************************************************************
     * <summary>Cross product between a and b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="a">The a vector.</param>
     * <param name="b">The b vector.</param>
     * <returns>The result vector.</returns>
     **************************************************************************************************/
    static Vector3D CrossProduct(const Vector3D& a, const Vector3D& b);

    /**************************************************************************************************
     * <summary>Dot product between b and this vector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="b">The b vector.</param>
     * <returns>The scalar product between the b vector and this vector.</returns>
     **************************************************************************************************/
    double DotProduct(const Vector3D& b);

    /**************************************************************************************************
     * <summary>Dot product between a and b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="a">The a vector.</param>
     * <param name="b">The b vector.</param>
     * <returns>The scalar product between the two vectors.</returns>
     **************************************************************************************************/
    static double DotProduct(const Vector3D& a, const Vector3D& b);

    /**************************************************************************************************
     * <summary>Gets a projection.</summary>
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     * <param name="a">The const Vector3D&amp; to process.</param>
     * <param name="b">The const Vector3D&amp; to process.</param>
     * <returns>The projection.</returns>
     **************************************************************************************************/
    static Vector3D GetProjection(const Vector3D& a, const Vector3D& b);

    /**************************************************************************************************
     * <summary>Gets a projection.</summary>
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     * <param name="b">The const Vector3D&amp; to process.</param>
     * <returns>The projection.</returns>
     **************************************************************************************************/
    Vector3D GetProjection(const Vector3D& b);

    /**************************************************************************************************
     * <summary>Gets projection x coordinate axis.</summary>
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     * <returns>The projection x coordinate axis.</returns>
     **************************************************************************************************/
    Vector3D GetProjectionOnXAxis();

    /**************************************************************************************************
     * <summary>Gets projection y coordinate axis.</summary>
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     * <returns>The projection y coordinate axis.</returns>
     **************************************************************************************************/
    Vector3D GetProjectionOnYAxis();

    /**************************************************************************************************
     * <summary>Gets projection z coordinate axis.</summary>
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     * <returns>The projection z coordinate axis.</returns>
     **************************************************************************************************/
    Vector3D GetProjectionOnZAxis();

    /**************************************************************************************************
     * <summary>Gets the angle from b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="b">The b vector.</param>
     * <returns>The angle from the b vector.</returns>
     **************************************************************************************************/
    double GetAngleFrom(const Vector3D& b);

    /**************************************************************************************************
     * <summary>Gets the angle between b to a.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="b">The b vector.</param>
     * <param name="a">The a vector.</param>
     * <returns>The angle between the two vectors in radians.</returns>
     **************************************************************************************************/
    static double GetAngleFrom(const Vector3D& b, const Vector3D& a);

    /**************************************************************************************************
     * <summary>Gets the angle that the target vector must point to face towards source.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="target">The Target vector.</param>
     * <param name="source">The Source vector.</param>
     * <returns>The facing angle in radians.</returns>
     **************************************************************************************************/
    static double GetFacingAngle(const Vector3D& target, const Vector3D& source);

    /**************************************************************************************************
     * <summary>Gets the vector that points from source to target.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="target">The Target vector.</param>
     * <param name="source">The Source vector.</param>
     * <returns>The facing vector.</returns>
     **************************************************************************************************/
    static Vector3D GetFacingVector(const Vector3D& target, const Vector3D& source);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    Vector3D& operator=(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 5/27/2014.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    Vector3D& operator=(const Vector4D& rhs);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 5/27/2014.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    Vector3D& operator=(const Vector2D& rhs);

    /**************************************************************************************************
     * <summary>Equality operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are considered equivalent.</returns>
     **************************************************************************************************/
    bool operator==(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Inequality operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     **************************************************************************************************/
    bool operator!=(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Addition assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D& operator+=(double scalar);

    /**************************************************************************************************
     * <summary>Subtraction assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D& operator-=(double scalar);

    /**************************************************************************************************
     * <summary>Multiplication assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D& operator*=(double scalar);

    /**************************************************************************************************
     * <summary>Division assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D& operator/=(double scalar);

    /**************************************************************************************************
     * <summary>Addition operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D operator+(const Vector3D& rhs) const;

    /**************************************************************************************************
     * <summary>Addition operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D operator+(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Subtraction operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D operator-(const Vector3D& rhs) const;

    /**************************************************************************************************
     * <summary>Subtraction operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D operator-(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Negation operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D operator-();

    /**************************************************************************************************
     * <summary>Multiplication operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D operator*(const Vector3D& rhs) const;

    /**************************************************************************************************
     * <summary>Multiplication operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D operator*(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Division operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D operator/(const Vector3D& rhs) const;

    /**************************************************************************************************
     * <summary>Division operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D operator/(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Addition assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D& operator+=(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Subtraction assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D& operator-=(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Multiplication assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D& operator*=(const Vector3D& rhs);

    /**************************************************************************************************
     * <summary>Division assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Vector3D& operator/=(const Vector3D& rhs);
        
    /**************************************************************************************************
     * <summary>Gets an equivalent 4D vector in homogenous coordinates</summary>
     *
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     *
     * <returns>The vector in 4D homogeneous coordinates.</returns>
     **************************************************************************************************/
    Vector4D GetHomogeneous() const;

    /**************************************************************************************************
     * <summary>Gets an equivalent 4D vector in homogenous coordinates</summary>
     *
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     *
     * <returns>The vector in 4D homogeneous coordinates.</returns>
     **************************************************************************************************/
    Vector4D GetHomogeneous();

    /**************************************************************************************************
     * <summary>Gets an equivalent 4D vector in homogenous coordinates.</summary>
     *
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     *
     * <param name="w">The scale factor.</param>
     *
     * <returns>The vector in 4D homogeneous coordinates.</returns>
     **************************************************************************************************/
    Vector4D GetHomogeneous(double w) const;

    /**************************************************************************************************
     * <summary>Gets an equivalent 4D vector in homogenous coordinates.</summary>
     *
     * <remarks>Casey Ugone, 3/26/2014.</remarks>
     *
     * <param name="w">The scale factor.</param>
     *
     * <returns>The vector in 4D homogeneous coordinates.</returns>
     **************************************************************************************************/
    Vector4D GetHomogeneous(double w);

    /**************************************************************************************************
     * <summary>Negation operator.</summary>
     * <remarks>Casey Ugone, 5/27/2014.</remarks>
     * <param name="lhs">The left hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    friend Vector3D operator-(const Vector3D& lhs);

    /**************************************************************************************************
     * <summary>Addition operator.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="v_lhs">     The first value.</param>
     * <param name="scalar_rhs">A value to add to it.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    friend Vector3D operator+(const Vector3D& v_lhs, double scalar_rhs);

    /**************************************************************************************************
     * <summary>Addition operator.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="scalar_lhs">The first value.</param>
     * <param name="v_rhs">     A value to add to it.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    friend Vector3D operator+(double scalar_lhs, const Vector3D& v_rhs);

    /**************************************************************************************************
     * <summary>Subtraction operator.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="v_lhs">     The first value.</param>
     * <param name="scalar_rhs">A value to subtract from it.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    friend Vector3D operator-(const Vector3D& v_lhs, double scalar_rhs);

    /**************************************************************************************************
     * <summary>Subtraction operator.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="scalar_lhs">The first value.</param>
     * <param name="v_rhs">     A value to subtract from it.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    friend Vector3D operator-(double scalar_lhs, const Vector3D& v_rhs);

    /**************************************************************************************************
     * <summary>Multiplication operator.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="v_lhs">     The first value to multiply.</param>
     * <param name="scalar_rhs">The second value to multiply.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    friend Vector3D operator*(const Vector3D& v_lhs, double scalar_rhs);

    /**************************************************************************************************
     * <summary>Multiplication operator.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="scalar_lhs">The first value to multiply.</param>
     * <param name="v_rhs">     The second value to multiply.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    friend Vector3D operator*(double scalar_lhs, const Vector3D& v_rhs);

    /**************************************************************************************************
     * <summary>Division operator.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="v_lhs">     The numerator.</param>
     * <param name="scalar_rhs">The denominator.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    friend Vector3D operator/(const Vector3D& v_lhs, double scalar_rhs);

    /**************************************************************************************************
     * <summary>Division operator.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="scalar_lhs">The numerator.</param>
     * <param name="v_rhs">     The denominator.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    friend Vector3D operator/(double scalar_lhs, const Vector3D& v_rhs);



protected:

    /**************************************************************************************************
     * <summary>Sets the x coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     **************************************************************************************************/
    void SetX(double x);

    /**************************************************************************************************
     * <summary>Sets the y coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="y">The y coordinate.</param>
     **************************************************************************************************/
    void SetY(double y);

    /**************************************************************************************************
     * <summary>Sets the z coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="z">The z coordinate.</param>
     **************************************************************************************************/
    void SetZ(double z);

    /**************************************************************************************************
     * <summary>Sets the terminal point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">The x coordinate.</param>
     * <param name="y">The y coordinate.</param>
     * <param name="z">The z coordinate.</param>
     **************************************************************************************************/
    void SetTerminal(double x, double y, double z);
    
    /**************************************************************************************************
     * <summary>Calculates the angle.</summary>
     * <remarks>Casey Ugone, 4/24/2014.</remarks>
     **************************************************************************************************/
    void CalculateAngle();

private:
    /// <summary> The terminal point x-coordinate. </summary>
    double _x;
    /// <summary> The terminal point y-coordinate. </summary>
    double _y;
    /// <summary> The terminal point z-coordinate. </summary>
    double _z;
    /// <summary> The angle from horizontal. </summary>
    double _angle;

};

A2DE_END

#endif