/**************************************************************************************************
// file:	Engine\Physics\CPhysicsArea.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the physics area class
 **************************************************************************************************/
#include "CPhysicsArea.h"

#include "../a2de_physics.h"
#include "../Math/CVector2D.h"
#include "a2de_force_generators.h"
#include "../a2de_objects.h"

A2DE_BEGIN

void PhysicsArea::OnEnter(Object* entered_object) {
    if(_gravity) _gravity->RegisterBody(entered_object);
    if(_drag) _drag->RegisterBody(entered_object);
    Trigger<Object*>::RegisterObject(entered_object);
}

void PhysicsArea::OnTick(Object* object) {
    Trigger<Object*>::OnTick(object);
}

void PhysicsArea::OnExit(Object* exited_object) {
    if(_gravity) _gravity->UnregisterBody(exited_object);
    if(_drag) _drag->UnregisterBody(exited_object);
    Trigger<Object*>::UnregisterObject(exited_object);
}

void PhysicsArea::Update(double deltaTime) {
    if(_gravity) _gravity->Update(deltaTime);
    if(_drag) _drag->Update(deltaTime);
    a2de::Trigger<Object*>::Update(deltaTime);
}

PhysicsArea::PhysicsArea() : a2de::Trigger<Object*>(), _gravity(nullptr), _drag(nullptr) {
    /* DO NOTHING */
}

PhysicsArea::~PhysicsArea() {
    delete _drag;
    delete _gravity;
}

void PhysicsArea::SetGravity(const a2de::Vector2D& gravity) {
    if(_gravity == nullptr) {
        _gravity = new a2de::GravityForceGenerator(gravity);
        return;
    }
    _gravity->SetGravity(gravity);
}

void PhysicsArea::SetDragCoefficients(const a2de::Vector2D& k1k2) {
    if(_drag == nullptr) {
        _drag = new a2de::DragForceGenerator(k1k2.GetX(), k1k2.GetY());
        return;
    }
    _drag->SetK1(k1k2.GetX());
    _drag->SetK2(k1k2.GetY());
}

A2DE_END