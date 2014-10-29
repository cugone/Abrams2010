/**************************************************************************************************
// file:	Engine\Physics\CContactData.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the contact data class
 **************************************************************************************************/
#ifndef A2DE_CCONTACTDATA_H
#define A2DE_CCONTACTDATA_H

#include "../a2de_vals.h"

#include "../Math/CVector2D.h"

A2DE_BEGIN

class RigidBody;

class ContactData {
public:
    ContactData(const a2de::Vector2D& contact_point, const a2de::Vector2D& contact_normal, double penetration_amount, const a2de::RigidBody& body_one, const a2de::RigidBody& body_two);
    ContactData(const ContactData& other);

    ContactData& operator=(const ContactData& rhs);

    ~ContactData();

    a2de::Vector2D GetContactPoint() const;
    a2de::Vector2D GetContactPoint();

    a2de::Vector2D GetContactNormal() const;
    a2de::Vector2D GetContactNormal();

    double GetPenetrationAmount() const;
    double GetPenetrationAmount();

    const a2de::RigidBody& GetBodyOne() const;
    a2de::RigidBody& GetBodyOne();

    const a2de::RigidBody& GetBodyTwo() const;
    a2de::RigidBody& GetBodyTwo();

protected:
private:
    a2de::Vector2D _contact_point;
    a2de::Vector2D _contact_normal;
    double _penetration_amount;
    a2de::RigidBody& _body_one;
    a2de::RigidBody& _body_two;
};

A2DE_END

#endif // CCONTACTDATA_H