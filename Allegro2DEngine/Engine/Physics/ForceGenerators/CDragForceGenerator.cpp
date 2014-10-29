/**************************************************************************************************
// file:	Engine\Physics\ForceGenerators\CDragForceGenerator.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the drag force generator class
 **************************************************************************************************/
#include "CDragForceGenerator.h"

#include "../../a2de_objects.h"
#include "../../a2de_math.h"
#include <algorithm>

A2DE_BEGIN

void DragForceGenerator::Update(double /*deltaTime*/) {

    if(_subscribers.empty()) return;

    std::for_each(_subscribers.begin(), _subscribers.end(), [&](Object* elem) //UpdateObject(_coefficients));
    {
        if(elem == nullptr) return;
        a2de::RigidBody* body = elem->GetBody();
        if(body == nullptr) return;

        Vector2D force = body->GetVelocity();

        double dragCoeff = force.GetLength();
        if(a2de::Math::IsEqual(dragCoeff, 0.0)) return;
        dragCoeff = _coefficients.first * dragCoeff + _coefficients.second * dragCoeff * dragCoeff;

        a2de::Vector2D::Normalize(force);
        force *= (-dragCoeff);
        body->ApplyImpulse(force);
    });
}

DragForceGenerator::DragForceGenerator() : ADTForceGenerator(), _coefficients(0.0, 0.0) { /* DO NOTHING */ }

DragForceGenerator::DragForceGenerator(double k1, double k2) : ADTForceGenerator(), _coefficients(k1, k2) { /* DO NOTHING */ }

DragForceGenerator::DragForceGenerator(const DragForceGenerator& other) : ADTForceGenerator(other), _coefficients(other._coefficients) { /* DO NOTHING */ }

DragForceGenerator& DragForceGenerator::operator=(const DragForceGenerator& rhs) {
    if(this == &rhs) return *this;

    ADTForceGenerator::operator=(rhs);
    this->_coefficients = rhs._coefficients;

    return *this;
}

DragForceGenerator::~DragForceGenerator() {
    /* DO NOTHING */
}

void DragForceGenerator::SetK1(double k1) {
    _coefficients.first = k1;
}

double DragForceGenerator::GetK1() const {
    return _coefficients.first;
}

double DragForceGenerator::GetK1() {
    return static_cast<const DragForceGenerator&>(*this).GetK1();
}

void DragForceGenerator::SetK2(double k2) {
    _coefficients.second = k2;
}

double DragForceGenerator::GetK2() const {
    return _coefficients.second;
}

double DragForceGenerator::GetK2() {
    return static_cast<const DragForceGenerator&>(*this).GetK2();
}


A2DE_END