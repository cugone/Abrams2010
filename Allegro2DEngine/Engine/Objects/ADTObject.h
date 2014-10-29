/************************************************************************/
/* DISABLE VS2010 and earlier bug                                       */
/************************************************************************/
#if defined(_MSC_VER) && (_MSC_VER <= 1600)
#  pragma warning(disable:4505)
#endif
/**************************************************************************************************
// file:	Engine\Objects\ADTObject.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the adt object class
 **************************************************************************************************/
#ifndef A2DE_ADTOBJECT_H
#define A2DE_ADTOBJECT_H

#include "../a2de_vals.h"
#include "../Physics/CRigidBody.h"
#include "../Physics/IUpdatable.h"
#include "../GFX/IDrawable.h"

A2DE_BEGIN

class Object : public IUpdatable, public IDrawable {
public:
    Object();
    Object(const Object& other);
    Object& operator=(const Object& rhs);

    virtual ~Object() =0;

    virtual void Update(double deltaTime);

    virtual void SetBody(const a2de::RigidBodyDef& body);
    virtual const a2de::RigidBody* GetBody() const;
    virtual a2de::RigidBody* GetBody();

    virtual void Draw(BITMAP* dest);


protected:
private:
};

A2DE_END

#endif