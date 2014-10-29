#ifndef A2DE_CRODFORCEGENERATOR_H
#define A2DE_CRODFORCEGENERATOR_H

#include "../../a2de_vals.h"
#include "../../Math/CVector2D.h"
#include <utility>

#include "ADTForceGenerator.h"

A2DE_BEGIN

class Object;

class RodForceGenerator : public ADTForceGenerator {
public:

    /**************************************************************************************************
     * <summary>Default constructor.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     **************************************************************************************************/
    RodForceGenerator();

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="rod_length">The length of the rod.</param>
     **************************************************************************************************/
    RodForceGenerator(double rod_length);
    
    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     **************************************************************************************************/
    virtual ~RodForceGenerator();

    /**************************************************************************************************
     * <summary>Draws the rod.</summary>
     * <remarks>Casey Ugone, 7/13/2014.</remarks>
     * <param name="dest">[in,out] If non-null, destination for the.</param>
     **************************************************************************************************/
    virtual void Draw(BITMAP* dest);

    /**************************************************************************************************
     * <summary>Updates the bodies attached.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="deltaTime">Time since the last frame.</param>
     **************************************************************************************************/
    virtual void Update(double deltaTime);

    /**************************************************************************************************
     * <summary>Attach first end to a body.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="body">[in,out] If non-null, the body to attach.</param>
     **************************************************************************************************/
    void AttachFirstEndTo(a2de::Object* body);

    /**************************************************************************************************
     * <summary>Attach second end to a body.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="body">[in,out] If non-null, the body.</param>
     **************************************************************************************************/
    void AttachSecondEndTo(a2de::Object* body);

    /**************************************************************************************************
     * <summary>Detach first end.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     **************************************************************************************************/
    void DetachFirstEnd();

    /**************************************************************************************************
     * <summary>Detach second end.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     **************************************************************************************************/
    void DetachSecondEnd();


protected:
private:

    /// <summary> Length of the rod. </summary>
    double _length;

    /// <summary> The bodies attached to the rod ends </summary>
    std::pair<Object*, Object*> _rod_ends;

    //RegisterBody unavailable for Rods!
    /**************************************************************************************************
     * <summary>Registers the body described by body.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="body">[in,out] If non-null, the body.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    bool RegisterBody(Object* body);

    //UnregisterBody unavailable for Rods!
    /**************************************************************************************************
     * <summary>Unregisters the body described by body.</summary>
     * <remarks>Casey Ugone, 5/20/2013.</remarks>
     * <param name="body">[in,out] If non-null, the body.</param>
     **************************************************************************************************/
    void UnregisterBody(Object* body);
};

A2DE_END

#endif // CRODFORCEGENERATOR_H
