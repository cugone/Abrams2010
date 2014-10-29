#ifndef A2DE_IDRAWABLE_H
#define A2DE_IDRAWABLE_H

#include "../a2de_vals.h"
#include <allegro/draw.h>


A2DE_BEGIN

class IDrawable {
public:

    /**************************************************************************************************
     * <summary>Draws the object given destination bitmap.</summary>
     * <remarks>Casey Ugone, 5/27/2014.</remarks>
     * <param name="dest">[in,out] If non-null, destination for the.</param>
     **************************************************************************************************/
    virtual void Draw(BITMAP* dest)=0;
    virtual ~IDrawable(){ /* DO NOTHING */ }
};

A2DE_END

#endif