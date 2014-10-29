/**************************************************************************************************
// file:	Engine\Physics\CWorld.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the world class
 **************************************************************************************************/
#include "CWorld.h"

#include "../a2de_exceptions.h"
#include "../a2de_math.h"
#include "../a2de_graphics.h"
#include "CRigidBody.h"
#include <allegro/draw.h>
#include <allegro/gfx.h>
#include <utility>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "../GFX/CSprite.h"
#include "../Objects/ADTObject.h"
#include "CRigidBody.h"
#include "CContactPair.h"
#include "CContactData.h"

#include "../Physics/IBoundingBox.h"

#include "../Objects/ADTObject.h"

#include <set>
#include <cmath>

A2DE_BEGIN

World::World(const a2de::WorldDef& world_definition) throw(...) : _dimensions(Vector2D(world_definition.width, world_definition.height)), _cameras(MapCams()), _objects(Objects()), _buffer(nullptr), _gh(nullptr), _dh(nullptr), _grid() {
    a2de::Math::SetWorldScale(world_definition.scale);
    double screen_x = a2de::Math::ToScreenScale(_dimensions.GetX());
    double screen_y = a2de::Math::ToScreenScale(_dimensions.GetY());
    if(screen_x <= 1.0 || screen_y <= 1.0) {
        throw InvalidArgumentException("All Dimensions of World must be greater than world scale.");
    }


    _buffer = create_bitmap(screen_x, screen_y);
    if(_buffer == nullptr) {
        std::ostringstream ss;
        ss << "World Buffer creation failed. Width: " << screen_x << "px Height: " << screen_y << "px";
        throw Exception(ss.str());
    }
    clear_bitmap(_buffer);

    try {
        //Don't bother allocating gravity and drag forces if the gravity and drag will not affect physics!
        if(a2de::Math::IsEqual(world_definition.gravity_x, 0.0) == false || a2de::Math::IsEqual(world_definition.gravity_y, 0.0) == false) {
            _gh = new GravityForceGenerator(world_definition.gravity_x, world_definition.gravity_y);
        }
        if(a2de::Math::IsEqual(world_definition.drag_k1, 0.0) == false || a2de::Math::IsEqual(world_definition.drag_k2, 0.0) == false) {
            _dh = new DragForceGenerator(world_definition.drag_k1, world_definition.drag_k2);
        }
        Vector2D dims(world_definition.width, world_definition.height);
        _grid = new QuadTree<a2de::Vector2D>(a2de::Rectangle(dims / 2.0, dims, a2de::Color::GREEN(), false));

    } catch(...) {
        DeallocateWorld();
        throw;
    }
}

World::~World() {
    DeallocateWorld();    
}

bool World::AddCamera(const Camera& camera) {
    MapCams::size_type msize = _cameras.max_size();
    MapCams::size_type s = _cameras.size();
    if(msize == s) return false;
    std::pair<MapCamsIter, bool> result = _cameras.insert(std::make_pair(s, camera));
    return result.second;
}

bool World::RemoveCamera(const unsigned char camera_index) {
    MapCamsIter result = _cameras.find(camera_index);
    MapCamsIter e = _cameras.end();
    if(result == e) return false;
    return (_cameras.erase(result) == e);
}

bool World::RemoveCamera(const Camera& camera) {

    MapCamsIter b = _cameras.begin();
    MapCamsIter e = _cameras.end();
    for(MapCamsIter _iter = b; _iter != e; /* DO NOTHING */) {
        if(&_iter->second != &camera) {
            _iter++;
            continue;
        } else {
            _cameras.erase(_iter++);
        }
    }

    return true;
}

void World::CameraToObject(Camera& cam, const Object& obj) {
    if(obj.GetBody() == nullptr) return;
    cam.SetPosition(obj.GetBody()->GetPosition() - (cam.GetExtents()));
}

void World::ObjectToCamera(Object& obj, const Camera& cam) {
    if(obj.GetBody() == nullptr) return;
    obj.GetBody()->SetPosition(cam.GetPosition() + (cam.GetExtents()));
}

bool World::AddObject(Object* obj) {
    if(obj == nullptr) return false;
    if(std::find(_objects.begin(), _objects.end(), obj) != _objects.end()) return false;

    if(this->_gh) this->_gh->RegisterBody(obj);
    if(this->_dh) this->_dh->RegisterBody(obj);
    if(obj->GetBody()) this->_grid->Add(obj->GetBody()->GetPosition());

    this->_objects.insert(obj);
    return true;
}

bool World::RemoveObject(Object* obj) {
    if(obj == nullptr) return false;
    if(obj->GetBody() == nullptr) return false;

    ObjectsIter b = _objects.begin();

    for(ObjectsIter _iter = b; _iter != _objects.end(); ++_iter) {
        if(*_iter != obj) continue;
        _objects.erase(_iter);
        if(_gh) _gh->UnregisterBody(obj);
        if(_dh) _dh->UnregisterBody(obj);
        _grid->Remove(obj->GetBody()->GetPosition());
        return true;
    }
    return false;
}

double World::GetWidth() const {
    return _dimensions.GetX();
}

double World::GetWidth() {
    return static_cast<const World&>(*this).GetWidth();
}

double World::GetHeight() const {
    return _dimensions.GetY();
}

double World::GetHeight() {
    return static_cast<const World&>(*this).GetHeight();
}

Vector2D World::GetDimensions() const {
    return _dimensions;
}

Vector2D World::GetDimensions() {
    return static_cast<const World&>(*this).GetDimensions();
}

void World::SetDimensions(double width, double height) {

    bool width_less_equal_zero = a2de::Math::IsEqual(width, 0.0) || width < 0.0;
    bool height_less_equal_zero = a2de::Math::IsEqual(height, 0.0) || height < 0.0;
    bool width_not_changed = a2de::Math::IsEqual(width, _dimensions.GetX());
    bool height_not_changed = a2de::Math::IsEqual(height, _dimensions.GetY());
    bool dimensions_not_changed = width_not_changed && height_not_changed;

    bool invalid_dimensions = dimensions_not_changed || width_less_equal_zero || height_less_equal_zero;

    if(invalid_dimensions) return;

    destroy_bitmap(_buffer);
    _buffer = create_bitmap(a2de::Math::ToScreenScale(width), a2de::Math::ToScreenScale(height));
    if(_buffer == nullptr) {
        _buffer = create_bitmap(a2de::Math::ToScreenScale(_dimensions.GetX()), a2de::Math::ToScreenScale(_dimensions.GetY()));
        return;
    }
    clear_bitmap(_buffer);

    _dimensions = Vector2D(width, height);

}

World::MapCamsIter World::GetCamera(unsigned char index) throw(...) {
    MapCamsIter result = _cameras.find(index);
    if(result == _cameras.end()) throw a2de::IndexOutOfBoundsException("index", "0", "_cameras.size() - 1");
    return result;
}

BITMAP* World::GetBuffer() const {
    return _buffer;
}

BITMAP* World::GetBuffer() {
    return static_cast<const World&>(*this).GetBuffer();
}

a2de::Vector2D World::CameraToWorldPosition(const Camera& cam, const Vector2D& screen_position) {
    return Camera::CameraToWorldPosition(cam, screen_position);
}

a2de::Vector2D World::WorldToCameraPosition(const Camera& cam, const Vector2D& world_position) {
    return Camera::WorldToCameraPosition(cam, world_position);
}

unsigned char World::GetCameraCount() const {
    return _cameras.size();
}

unsigned char World::GetCameraCount() {
    return static_cast<const World&>(*this).GetCameraCount();
}

World::MapCams World::GetCameras() const {
    return _cameras;
}

World::MapCams World::GetCameras() {
    return static_cast<const World&>(*this).GetCameras();
}

const World::Objects& World::GetObjects() const {
    return _objects;
}

World::Objects& World::GetObjects() {
    return const_cast<World::Objects&>(static_cast<const World&>(*this).GetObjects());
}

void World::SetGravity(const Vector2D& gravity) {
    if(a2de::Math::IsEqual(gravity.GetX(), 0.0) && a2de::Math::IsEqual(gravity.GetY(), 0.0)) {
        delete _gh;
        _gh = nullptr;
        return;
    }

    if(_gh == nullptr) {
        if(a2de::Math::IsEqual(gravity.GetX(), 0.0) == false || a2de::Math::IsEqual(gravity.GetY(), 0.0) == false) {
            _gh = new GravityForceGenerator(gravity);
        }
    }
    if(_gh) _gh->SetGravity(gravity);
}

const GravityForceGenerator* World::GetGravityHandler() const {
    return _gh;
}

void World::SetDragCoefficients(const Vector2D& k1k2) {
    if(a2de::Math::IsEqual(k1k2.GetX(), 0.0) && a2de::Math::IsEqual(k1k2.GetY(), 0.0)) {
        delete _dh;
        _dh = nullptr;
        return;
    }

    if(_dh == nullptr) {
        if(a2de::Math::IsEqual(k1k2.GetX(), 0.0) == false || a2de::Math::IsEqual(k1k2.GetY(), 0.0) == false) {
            _dh = new DragForceGenerator();
        }
    }
    if(_dh) _dh->SetK1(k1k2.GetX());
    if(_dh) _dh->SetK2(k1k2.GetY());
}

const DragForceGenerator* World::GetDragHandler() const {
    return _dh;
}

void World::Update(double deltaTime) {
    UpdateObjectsInWorld(deltaTime);
    ResolveCollisions(deltaTime);
}

void World::ClearVisibleScene(const Camera& cam) {
    ClearVisibleScene(cam, Color::BLACK());
}

void World::ClearVisibleScene(const Camera& cam, const Color& color) {
    int x = a2de::Math::ToScreenScale(cam.GetX());
    int y = a2de::Math::ToScreenScale(cam.GetY());
    int w = a2de::Math::ToScreenScale(cam.GetExtents().GetX());
    int h = a2de::Math::ToScreenScale(cam.GetExtents().GetY());
    rectfill(_buffer, x - w, y - h, x + w, y + h, color);
}

void World::Render() {
    if(_objects.empty()) return;
    std::for_each(_objects.begin(), _objects.end(), [this](a2de::Object* elem)
    {
        this->RenderObject(elem);
    });
}

void World::RenderObject(Sprite* sprite) {

    if(sprite == nullptr) return;

    Rectangle bounding_box(sprite->GetX(), sprite->GetY(), a2de::Math::ToWorldScale(sprite->GetWidth()), a2de::Math::ToWorldScale(sprite->GetHeight()));
    std::for_each(_cameras.begin(), _cameras.end(), [&](std::pair<unsigned char, Camera> elem) 
    {

        if(_buffer == nullptr) return;
        if(sprite == nullptr) return;

        double spriteL = sprite->GetX();
        double cameraR = elem.second.GetX() + elem.second.GetExtents().GetX();

        if(spriteL > cameraR) return;

        double spriteR = sprite->GetX() + sprite->GetWidth();
        double cameraL = elem.second.GetX() - elem.second.GetExtents().GetX();

        if(spriteR < cameraL) return;

        double spriteT = sprite->GetY();            
        double cameraB = elem.second.GetY() + elem.second.GetExtents().GetY();

        if(spriteT > cameraB) return;

        double cameraT = elem.second.GetY() - elem.second.GetExtents().GetY();
        double spriteB = sprite->GetY() + sprite->GetHeight();

        if(spriteB < cameraT) return;

        sprite->Draw(_buffer);
    });

}

void World::RenderObject(IDrawable* drawable) {
    if(drawable == nullptr) return;
    drawable->Draw(_buffer);
}

void World::RenderObject(Object* object) {
    if(object == nullptr) return;

    std::for_each(_cameras.begin(), _cameras.end(), [&](const std::pair<unsigned char, Camera>& elem)
    {
        if(_buffer == nullptr) return;
        if(object == nullptr) return;
        
        a2de::RigidBody* b = object->GetBody();
        if(b == nullptr) return;
        
        IBoundingBox* bb = b->GetBoundingRectangle();
        if(bb == nullptr) return;

        a2de::Vector2D pos(bb->GetTransform().GetPosition());
        a2de::Vector2D he(bb->GetHalfExtents());

        a2de::Vector2D tl(pos + a2de::Vector2D(-he.GetX(), -he.GetY()));
        a2de::Vector2D tr(pos + a2de::Vector2D(he.GetX(), -he.GetY()));
        a2de::Vector2D bl(pos + a2de::Vector2D(-he.GetX(), he.GetY()));
        a2de::Vector2D br(pos + a2de::Vector2D(he.GetX(), he.GetY()));

        Rectangle camera_bounds(elem.second.GetPosition(), elem.second.GetExtents());
        if(camera_bounds.Intersects(tl) || camera_bounds.Intersects(tr) || camera_bounds.Intersects(br) || camera_bounds.Intersects(bl)) {
            object->Draw(_buffer);
        }

    });

}

void World::RenderObject(Shape* shape) {

    if(shape == nullptr) return;

    std::for_each(_cameras.begin(), _cameras.end(), [&](const std::pair<unsigned char, Camera>& elem)
    {
        if(_buffer == nullptr) return;
        if(shape == nullptr) return;
        Rectangle camera_bounds(elem.second.GetPosition(), elem.second.GetExtents());
        if(shape->Intersects(camera_bounds)) {
            a2de::SpriteHandler::Draw(_buffer, shape);
        }
    });

}

void World::RenderObject(IBoundingBox* bounding_box) {
    IBoundingBox* bb = bounding_box;
    if(bb == nullptr) return;

    a2de::Vector2D pos(bb->GetTransform().GetPosition());
    a2de::Vector2D he(bb->GetHalfExtents());
    a2de::Vector2D tl(pos + a2de::Vector2D(-he.GetX(), -he.GetY()));
    a2de::Vector2D tr(pos + a2de::Vector2D(he.GetX(), -he.GetY()));
    a2de::Vector2D bl(pos + a2de::Vector2D(-he.GetX(), he.GetY()));
    a2de::Vector2D br(pos + a2de::Vector2D(he.GetX(), he.GetY()));

    std::for_each(_cameras.begin(), _cameras.end(), [&](const std::pair<unsigned char, Camera>& elem)
    {
        Rectangle camera_bounds(elem.second.GetPosition(), elem.second.GetExtents());
        if(camera_bounds.Intersects(tl) || camera_bounds.Intersects(tr) || camera_bounds.Intersects(br) || camera_bounds.Intersects(bl)) {
            bb->Draw(_buffer);
        }
    });

}

void World::DrawGrid() {
    _grid->Draw(_buffer, true);
}

void World::UpdateObjectsInWorld(double deltaTime) {
    if(_gh) _gh->Update(deltaTime);
    if(_dh) _dh->Update(deltaTime);

    if(_objects.empty()) return;
    std::for_each(_objects.begin(), _objects.end(),  [deltaTime](Object* elem)
    {
        elem->Update(deltaTime);
    });

}

void World::ResolveCollisions(double deltaTime) {
    //BroadPhase: Check if Bounding Boxes are colliding.
    //NarrowPhase: Check if Collision Shapes are colliding and handle shape-specific resolution.
    ContactPairs cps = BroadPhaseCollision();
    NarrowPhaseCollision(cps, deltaTime);
}

World::ContactPairs World::BroadPhaseCollision() {

    //Update the QuadTree Grid.
    //For each Camera: Query any visible Objects.
    //For each visible Object in all Cameras: generate a unique Contact Pair.
    //Return the set of Contact Pairs.

    UpdateGrid();

    ContactPairs cps;
    if(_objects.empty()) return cps; //returns empty cps

    //Must use oldie-but-goody for-loop here due to conditional processing of some objects and not others.
    for(ObjectsIter objects_iter = _objects.begin(); objects_iter != _objects.end(); ++objects_iter) {
        if((*objects_iter)->GetBody() == nullptr) continue;
        std::vector<a2de::QuadTree<a2de::Vector2D>* > p = this->_grid->GetNodesByLocation((*objects_iter)->GetBody()->GetPosition());
        if(p.empty()) continue;

        std::size_t ps = p.size();
        std::vector<a2de::Vector2D> v;
        for(std::size_t i = 0; i < ps; ++i) {
            std::vector<a2de::Vector2D> current_element_vec(p[i]->GetAllElements());
            std::size_t cs = current_element_vec.size();
            if(i == 0) {
                v = current_element_vec;
                continue;
            }
            v.reserve(cs + v.size());
            v.insert(v.end(), current_element_vec.begin(), current_element_vec.end());
        }

        ContactPairs current_cps_pairs = GenerateContactPairs(v);

        //Remove any false positives. FP = non-colliding bounding boxes.
        for(World::ContactPairsIter contacts_iter = current_cps_pairs.begin(); contacts_iter != current_cps_pairs.end(); /* DO NOTHING */ ) {
            a2de::RigidBody* first_body = const_cast<a2de::RigidBody*>((*contacts_iter).GetFirstBody());
            a2de::RigidBody* second_body = const_cast<a2de::RigidBody*>((*contacts_iter).GetSecondBody());

            IBoundingBox* fBB = first_body->GetBoundingRectangle();
            IBoundingBox* sBB = second_body->GetBoundingRectangle();
            if(fBB == nullptr || sBB == nullptr) {
                current_cps_pairs.erase(contacts_iter++);
                continue;
            }
            a2de::Rectangle fR(fBB->GetTransform().GetPosition(), fBB->GetHalfExtents());
            a2de::Rectangle sR(sBB->GetTransform().GetPosition(), sBB->GetHalfExtents());
            if(fR.Intersects(sR) == false) {
                current_cps_pairs.erase(contacts_iter++);
                continue;
            }
            ++contacts_iter;
        }
        cps.insert(current_cps_pairs.begin(), current_cps_pairs.end());
    }
    return cps;
}

void World::NarrowPhaseCollision(ContactPairs& contact_pairs, double deltaTime) {

    //For Each contact pair, update the post-collision physics.
    for(World::ContactPairsIter _iter = contact_pairs.begin(); _iter != contact_pairs.end(); ++_iter) {
        a2de::RigidBody* first_body = const_cast<a2de::RigidBody*>((*_iter).GetFirstBody());
        a2de::RigidBody* second_body = const_cast<a2de::RigidBody*>((*_iter).GetSecondBody());

        first_body->Wake();
        second_body->Wake();

        //Process contact: Adjust Velocity. Adjust Position.
        VelocitySolver(first_body, second_body);
        PositionSolver(first_body, second_body, deltaTime);
    }

}

void World::UpdateGrid() {

    std::vector<a2de::Vector2D> objs;
    for(auto _iter = this->_objects.begin(); _iter != this->_objects.end(); ++_iter ) {
        if((*_iter)->GetBody() == nullptr) continue;
        a2de::Vector2D collision_position = (*_iter)->GetBody()->GetPosition();
        objs.push_back(collision_position);
    }
    _grid->Clear();
    _grid->Add(objs);
}

void World::QueryAllCameras(std::vector<a2de::Vector2D>& queried_elems) {
    std::size_t max_cameras = _cameras.size();
    for(std::size_t i = 0; i < max_cameras; ++i) {
        std::vector<a2de::Vector2D> temp_queried_elems(_grid->Query(a2de::Rectangle(_cameras.at(i).GetPosition(), _cameras.at(i).GetExtents())));
        queried_elems.insert(queried_elems.end(), temp_queried_elems.begin(), temp_queried_elems.end());
    }
}

a2de::World::ContactPairs World::GenerateContactPairs(std::vector<a2de::Vector2D>& queried_elems) {

    a2de::World::ContactPairs contact_pairs;

    std::size_t max_elems = queried_elems.size();
    if(max_elems == 0) return contact_pairs;

    for(std::size_t i = 0; i < max_elems - 1; ++i) {
        for(std::size_t j = i + 1; j < max_elems; ++j) {

            if(queried_elems[i] == queried_elems[j]) continue;
            a2de::Vector2D& left_position(queried_elems[i]);
            ObjectsIter left_iter = std::find_if(_objects.begin(), _objects.end(), [&left_position](a2de::Object* elem)->bool
            {
                if(elem == nullptr) return false;
                if(elem->GetBody() == nullptr) return false;
                return elem->GetBody()->GetPosition() == left_position;
            });
            if(left_iter == _objects.end()) continue;

            if((*left_iter)->GetBody() == nullptr) continue;
            a2de::RigidBody* left_body = (*left_iter)->GetBody();

            a2de::Vector2D& right_position(queried_elems[j]);
            ObjectsIter right_iter = std::find_if(_objects.begin(), _objects.end(), [&right_position](a2de::Object* elem)->bool
            {
                if(elem == nullptr) return false;
                if(elem->GetBody() == nullptr) return false;
                return elem->GetBody()->GetPosition() == right_position;
            });
            if(right_iter == _objects.end()) continue;

            if((*right_iter)->GetBody() == nullptr) continue;
            a2de::RigidBody* right_body = (*right_iter)->GetBody();

            if(left_body == right_body) continue;

            //The result doesn't matter. Inserted or not, the loop will continue.
            contact_pairs.insert(a2de::ContactPair(left_body, right_body));

        }
    }
    return contact_pairs;
}

void World::VelocitySolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Vector2D first_position = first_body->GetPosition();
    a2de::Vector2D second_position = second_body->GetPosition();
    a2de::Vector2D first_contact_normal;
    a2de::Vector2D relPosFirst = first_position - second_position;
    if(relPosFirst != a2de::Vector2D(0.0, 0.0)) {
        first_contact_normal = relPosFirst.Normalize();
    }
    a2de::Vector2D second_contact_normal;
    a2de::Vector2D relPosSecond = second_position - first_position;
    if(relPosSecond != a2de::Vector2D(0.0, 0.0)) {
        second_contact_normal = relPosSecond.Normalize();
    }

    double m1 = first_body->GetMass();
    double m2 = second_body->GetMass();
    double mass_sum = m1 + m2;
    double mass1_mass2_diff = m1 - m2;
    double mass2_mass1_diff = m2 - m1;
    double v1 = first_body->GetVelocity().GetLength();
    double v2 = second_body->GetVelocity().GetLength();
    double theta1 = first_body->GetVelocity().GetAngle();
    double theta2 = second_body->GetVelocity().GetAngle();
    double phi1 = first_contact_normal.GetAngle();
    double phi2 = second_contact_normal.GetAngle();
    double cos_theta1_phi1 = std::cos(theta1 - phi1);
    double cos_theta2_phi1 = std::cos(theta2 - phi1);
    double sin_theta1_phi1 = std::sin(theta1 - phi1);
    double cos_theta1_phi2 = std::cos(theta1 - phi2);
    double cos_theta2_phi2 = std::cos(theta2 - phi2);
    double sin_theta2_phi2 = std::sin(theta2 - phi2);
    double cos_phi1_pi_2 = std::cos(phi1 + (a2de::Math::A2DE_1PI_2));
    double sin_phi1_pi_2 = std::sin(phi1 + (a2de::Math::A2DE_1PI_2));
    double cos_phi2_pi_2 = std::cos(phi2 + (a2de::Math::A2DE_1PI_2));
    double sin_phi2_pi_2 = std::sin(phi2 + (a2de::Math::A2DE_1PI_2));
    double twice_m1v1 = 2.0 * m1 * v1;
    double twice_m2v2 = 2.0 * m2 * v2;
    double cos_phi1 = std::cos(phi1);
    double sin_phi1 = std::sin(phi1);
    double cos_phi2 = std::cos(phi2);
    double sin_phi2 = std::sin(phi2);

    double v1_ratio = ((v1 * cos_theta1_phi1 * mass1_mass2_diff) + (twice_m2v2 * cos_theta2_phi1)) / mass_sum;

    double v1x = (v1_ratio * cos_phi1) + (v1 * sin_theta1_phi1 * cos_phi1_pi_2);
    double v1y = (v1_ratio * sin_phi1) + (v1 * sin_theta1_phi1 * sin_phi1_pi_2);

    a2de::Vector2D v1prime(v1x, v1y);

    double v2_ratio = ((v2 * cos_theta2_phi2 * mass2_mass1_diff) + (twice_m1v1 * cos_theta1_phi2)) / mass_sum;

    double v2x = (v2_ratio * cos_phi2) + (v2 * sin_theta2_phi2 * cos_phi2_pi_2);
    double v2y = (v2_ratio * sin_phi2) + (v2 * sin_theta2_phi2 * sin_phi2_pi_2);

    a2de::Vector2D v2prime(v2x, v2y);

    double first_r = first_body->GetRestitution();
    double second_r = second_body->GetRestitution();

    first_body->SetVelocity(first_r * v1prime);
    second_body->SetVelocity(second_r * v2prime);

}

void World::PositionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body, double /*deltaTime*/) {

    double first_mass = first_body->GetMass();
    double second_mass = second_body->GetMass();

    //If both are zero or infinite mass, do nothing.
    if(a2de::Math::IsEqual(first_mass, 0.0) && a2de::Math::IsEqual(second_mass, 0.0)) return;
    if(a2de::Math::IsEqual(first_mass, a2de::Math::A2DE_INFINITY) && a2de::Math::IsEqual(second_mass, a2de::Math::A2DE_INFINITY)) return;

    a2de::Shape* first_collision_shape = first_body->GetCollisionShape();
    a2de::Shape* second_collision_shape = second_body->GetCollisionShape();

    if(first_collision_shape == nullptr || second_collision_shape == nullptr) return;

    std::vector<ContactData> collision_results(ShapeCollisionSolver(first_body, second_body));

    if(collision_results.empty()) return;

    double mass_sum = first_mass + second_mass;

    a2de::Vector2D first_position = first_body->GetPosition();
    a2de::Vector2D second_position = second_body->GetPosition();

    a2de::Vector2D first_contact_normal = collision_results[0].GetContactNormal();
    a2de::Vector2D first_interpenetration = first_contact_normal * collision_results[0].GetPenetrationAmount() * (first_mass / mass_sum);

    a2de::Vector2D second_contact_normal = collision_results[1].GetContactNormal();
    a2de::Vector2D second_interpenetration = second_contact_normal * collision_results[1].GetPenetrationAmount() * (second_mass / mass_sum);

    first_body->SetPosition((first_position + first_interpenetration));
    second_body->SetPosition((second_position + second_interpenetration));
}

std::vector<ContactData> World::ShapeCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Shape* first_collision_shape = first_body->GetCollisionShape();
    a2de::Shape* second_collision_shape = second_body->GetCollisionShape();
    if(first_collision_shape == nullptr || second_collision_shape == nullptr) return std::vector<ContactData>();

    a2de::Shape::SHAPE_TYPE first_shape_type = first_collision_shape->GetShapeType();
    a2de::Shape::SHAPE_TYPE second_shape_type = second_collision_shape->GetShapeType();

    bool isCircleCircle = first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE && second_shape_type == a2de::Shape::SHAPETYPE_CIRCLE;
    bool isCircleLine = (first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE && second_shape_type == a2de::Shape::SHAPETYPE_LINE) || (first_shape_type == a2de::Shape::SHAPETYPE_LINE && second_shape_type == a2de::Shape::SHAPETYPE_CIRCLE);
    bool isCircleRectangle = (first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE && second_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE) || (first_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE && second_shape_type == a2de::Shape::SHAPETYPE_CIRCLE);
    bool isRectangleLine = (first_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE && second_shape_type == a2de::Shape::SHAPETYPE_LINE) || (first_shape_type == a2de::Shape::SHAPETYPE_LINE && second_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE);
    bool isRectangleRectangle = (first_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE && second_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE);

    std::vector<ContactData> collision_result;
    if(isCircleCircle) {
        collision_result = CircleCircleCollisionSolver(first_body, second_body);
    } else if(isCircleLine) {
        if(first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE) {
            collision_result = CircleLineCollisionSolver(first_body, second_body);
        } else {
            collision_result = CircleLineCollisionSolver(second_body, first_body);
        }
    } else if(isCircleRectangle) {
        if(first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE) {
            collision_result = CircleRectangleCollisionSolver(first_body, second_body);
        } else {
            collision_result = CircleRectangleCollisionSolver(second_body, first_body);
        }
    } else if(isRectangleLine) {
        if(first_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE) {
            collision_result = RectangleLineCollisionSolver(first_body, second_body);
        } else {
            collision_result = RectangleLineCollisionSolver(second_body, first_body);
        }
    } else if (isRectangleRectangle) {
        collision_result = RectangleRectangleCollisionSolver(first_body, second_body);
    } else {
        /* DO NOTHING */
    }
    return collision_result;
}

std::vector<ContactData> World::CircleCircleCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Circle first_shape(*dynamic_cast<a2de::Circle*>(first_body->GetCollisionShape()));
    a2de::Circle second_shape(*dynamic_cast<a2de::Circle*>(second_body->GetCollisionShape()));

    std::vector<ContactData> contact_result;
    if(first_shape.Intersects(second_shape) == false) return contact_result;

    a2de::Vector2D p1(first_shape.GetPosition());
    a2de::Vector2D p2(second_shape.GetPosition());
    double r1 = first_shape.GetRadius();
    double r2 = second_shape.GetRadius();
    a2de::Vector2D second_collision_direction((p2 - p1).Normalize());
    a2de::Vector2D first_collision_direction((p1 - p2).Normalize());

    a2de::Vector2D c1(p1 + second_collision_direction * r1);
    a2de::Vector2D c2(p2 + first_collision_direction * r2);

    double interpenetration_distance((c2 - c1).GetLength());

    contact_result.push_back(ContactData(c1, second_collision_direction, interpenetration_distance, *first_body, *second_body));
    contact_result.push_back(ContactData(c2, first_collision_direction, interpenetration_distance, *second_body, *first_body));


    //a2de::Vector2D first_collision_direction(second_shape.GetPosition() - first_shape.GetPosition());
    //a2de::Vector2D second_collision_direction(first_shape.GetPosition() - second_shape.GetPosition());
    //a2de::Vector2D collision_normalA_distance(first_collision_direction.Normalize() * first_shape.GetRadius());
    //a2de::Vector2D collision_normalB_distance(second_collision_direction.Normalize() * second_shape.GetRadius());

    //double distance_angleA = collision_normalA_distance.GetAngle();
    //double distance_angleB = collision_normalB_distance.GetAngle();
    //double c_normal_aX = first_collision_direction.GetX();
    //double c_normal_aY = first_collision_direction.GetY();
    //double c_normal_bX = second_collision_direction.GetX();
    //double c_normal_bY = second_collision_direction.GetY();
    //a2de::Vector2D collision_pointA(c_normal_aX * std::cos(distance_angleA), c_normal_aY * std::sin(distance_angleA));
    //a2de::Vector2D collision_pointB(c_normal_bX * std::cos(distance_angleB), c_normal_bY * std::sin(distance_angleB));

    //double interpenetration_distanceA = (collision_pointB - collision_pointA).GetLength();
    //double interpenetration_distanceB = (collision_pointA - collision_pointB).GetLength();

    //contact_result.push_back(ContactData(collision_pointA, first_collision_direction, interpenetration_distanceA, *first_body, *second_body));
    //contact_result.push_back(ContactData(collision_pointB, second_collision_direction, interpenetration_distanceB, *second_body, *first_body));

    return contact_result;
}

std::vector<ContactData> World::CircleLineCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Circle first_shape(*dynamic_cast<a2de::Circle*>(first_body->GetCollisionShape()));
    a2de::Line second_shape(*dynamic_cast<a2de::Line*>(second_body->GetCollisionShape()));

    std::vector<ContactData> contact_result;
    if(first_shape.Intersects(second_shape) == false) return contact_result;

    Vector2D line_vector = second_shape.GetPointTwo() - second_shape.GetPointOne();
    double left_angle_distance = std::abs(a2de::Vector2D::GetAngleFrom(line_vector.GetLeftNormal(), first_shape.GetPosition()));
    double right_angle_distance = std::abs(a2de::Vector2D::GetAngleFrom(line_vector.GetRightNormal(), first_shape.GetPosition()));
    double angle_distance = std::min(left_angle_distance, right_angle_distance);

    double x_distance = std::cos(angle_distance) * first_shape.GetRadius();
    double y_distance = std::sin(angle_distance) * first_shape.GetRadius();

    if(left_angle_distance < right_angle_distance) {
        contact_result.push_back(ContactData(a2de::Vector2D(x_distance, y_distance), line_vector.GetLeftNormal(), first_shape.GetRadius() - second_shape.GetDistance(first_shape.GetPosition()), *first_body, *second_body));
    } else {
        contact_result.push_back(ContactData(a2de::Vector2D(x_distance, y_distance), line_vector.GetRightNormal(), first_shape.GetRadius() - second_shape.GetDistance(first_shape.GetPosition()), *first_body, *second_body));
    }

    return contact_result;
}

std::vector<ContactData> World::CircleRectangleCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Circle first_shape(*dynamic_cast<a2de::Circle*>(first_body->GetCollisionShape()));
    a2de::Rectangle second_shape(*dynamic_cast<a2de::Rectangle*>(second_body->GetCollisionShape()));

    std::vector<ContactData> contact_result;
    if(first_shape.Intersects(second_shape) == false) return contact_result;

    double resultTop = Point(first_shape.GetPosition()).GetDistanceSquared(second_shape.GetTop().GetPointOne(), second_shape.GetTop().GetPointTwo());
    double resultLeft = Point(first_shape.GetPosition()).GetDistanceSquared(second_shape.GetLeft().GetPointOne(), second_shape.GetLeft().GetPointTwo());
    double resultRight = Point(first_shape.GetPosition()).GetDistanceSquared(second_shape.GetRight().GetPointOne(), second_shape.GetRight().GetPointTwo());
    double resultBottom = Point(first_shape.GetPosition()).GetDistanceSquared(second_shape.GetBottom().GetPointOne(), second_shape.GetBottom().GetPointTwo());

    a2de::Vector2D contact_normal(second_shape.GetPosition() - first_shape.GetPosition().Normalize());
    a2de::Vector2D contact_point(contact_normal * first_shape.GetRadius());
    double interpenetraction_depth_s = std::min(std::min(resultTop, resultBottom), std::min(resultLeft, resultRight));

    double interpenetraction_depth = std::sqrt(interpenetraction_depth_s);
    contact_result.push_back(ContactData(contact_point, contact_normal, interpenetraction_depth, *first_body, *second_body));

    return contact_result;
}

std::vector<ContactData> World::RectangleLineCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Rectangle first_shape(*dynamic_cast<a2de::Rectangle*>(first_body));
    a2de::Line second_shape(*dynamic_cast<a2de::Line*>(second_body));

    std::vector<ContactData> contact_result;
    if(first_shape.Intersects(second_shape) == false) return contact_result;

    return contact_result;
}

std::vector<ContactData> World::RectangleRectangleCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Rectangle first_shape(*dynamic_cast<a2de::Rectangle*>(first_body->GetCollisionShape()));
    a2de::Rectangle second_shape(*dynamic_cast<a2de::Rectangle*>(second_body->GetCollisionShape()));

    std::vector<ContactData> contact_result;
    if(first_shape.Intersects(second_shape) == false) return contact_result;

    a2de::Vector2D fp(first_shape.GetPosition());
    double fw(first_shape.GetWidth());
    double fh(first_shape.GetHeight());
    a2de::Vector2D fbl(fp + a2de::Vector2D(-fw, fh));
    a2de::Vector2D ftl(fp + a2de::Vector2D(-fw, -fh));
    a2de::Vector2D fbr(fp + a2de::Vector2D(fw, fh));
    a2de::Vector2D ftr(fp + a2de::Vector2D(fw, -fh));
    a2de::Vector2D fln((ftl - fbl).GetLeftNormal().Normalize());
    a2de::Vector2D ftn((ftl - ftr).GetLeftNormal().Normalize());
    a2de::Vector2D frn((fbr - ftr).GetLeftNormal().Normalize());
    a2de::Vector2D fbn((fbl - fbr).GetLeftNormal().Normalize());


    a2de::Vector2D sp(second_shape.GetPosition());
    double sw(second_shape.GetWidth());
    double sh(second_shape.GetHeight());
    a2de::Vector2D sbl(sp + a2de::Vector2D(-sw, sh));
    a2de::Vector2D stl(sp + a2de::Vector2D(-sw, -sh));
    a2de::Vector2D sbr(sp + a2de::Vector2D(sw, sh));
    a2de::Vector2D str(sp + a2de::Vector2D(sw, -sh));
    a2de::Vector2D sln((stl - sbl).GetLeftNormal().Normalize());
    a2de::Vector2D stn((str - stl).GetLeftNormal().Normalize());
    a2de::Vector2D srn((sbr - str).GetLeftNormal().Normalize());
    a2de::Vector2D sbn((sbl - sbr).GetLeftNormal().Normalize());

    a2de::Vector2D contact_point;
    a2de::Vector2D contact_normal = (first_body->GetXPosition() < second_body->GetXPosition() ? frn : /*Right Normal*/
                                    (first_body->GetXPosition() > second_body->GetXPosition() ? fln : /*Left Normal*/ 
                                    (first_body->GetYPosition() < second_body->GetYPosition() ? fbn : /*Bottom Normal*/
                                    (first_body->GetYPosition() > second_body->GetYPosition() ? ftn : /*Top Normal*/
                                    a2de::Vector2D(0.0, 0.0) /*Do nothing*/ ))));
    double penetration_amount;
    a2de::Rectangle overlap_out;
    bool is_overlapping = false;
    first_shape.Overlap(second_shape, overlap_out, is_overlapping);
    double w = overlap_out.GetWidth();
    double h = overlap_out.GetHeight();
    penetration_amount = w >= h ? w : h;
    ContactData m1cd(contact_point, contact_normal, penetration_amount, *first_body, *second_body);
    ContactData m2cd(contact_point, -contact_normal, penetration_amount, *second_body, *first_body);

    contact_result.push_back(m1cd);
    contact_result.push_back(m2cd);

    return contact_result;
}

const a2de::QuadTree<a2de::Vector2D>* World::GetGrid() const {
    return _grid;
}

a2de::QuadTree<a2de::Vector2D>* World::GetGrid() {
    return const_cast<a2de::QuadTree<a2de::Vector2D>*>(static_cast<const World&>(*this).GetGrid());
}

void World::DeallocateWorld() {
    delete _grid;
    _grid = nullptr;

    delete _gh;
    _gh = nullptr;

    delete _dh;
    _dh = nullptr;

    destroy_bitmap(_buffer);
    _buffer = nullptr;

    _objects.clear();
    _cameras.clear();
}



A2DE_END