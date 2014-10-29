#include "CCableForceGenerator.h"


a2de::CableForceGenerator::CableForceGenerator() : ADTForceGenerator(), _length(0.0), _cable_ends(nullptr, nullptr) { /* DO NOTHING */ }

a2de::CableForceGenerator::CableForceGenerator(double cable_length) : ADTForceGenerator(), _length(cable_length), _cable_ends(nullptr, nullptr) { /* DO NOTHING */ }

a2de::CableForceGenerator::~CableForceGenerator() { /* DO NOTHING */ }

void a2de::CableForceGenerator::Draw(BITMAP* dest) {
    if(_cable_ends.first == nullptr && _cable_ends.second == nullptr) return;

    a2de::Vector2D fp(a2de::Math::ToScreenScale(_cable_ends.first->GetBody()->GetPosition()));
    a2de::Vector2D sp(a2de::Math::ToScreenScale(_cable_ends.second->GetBody()->GetPosition()));

    line(dest, fp.GetX(), fp.GetY(), sp.GetX(), sp.GetY(), a2de::Color::YELLOW());
}

void a2de::CableForceGenerator::Update(double /*deltaTime*/) {

    if(_cable_ends.first == nullptr || _cable_ends.second == nullptr) return;

    a2de::RigidBody* first_body(_cable_ends.first->GetBody());
    a2de::RigidBody* second_body(_cable_ends.second->GetBody());
    if(first_body == nullptr || second_body == nullptr) return;

    a2de::Vector2D first_body_position(first_body->GetPosition());
    a2de::Vector2D second_body_position(second_body->GetPosition());

    double obj_distance_squared((first_body_position - second_body_position).GetLengthSquared());
    double length_squared(_length * _length);

    if(a2de::Math::IsEqual(obj_distance_squared, length_squared) || obj_distance_squared < length_squared) return;

    double first_mass = first_body->GetMass();
    double second_mass = second_body->GetMass();
    double mass_sum = first_mass + second_mass;

    if(a2de::Math::IsEqual(mass_sum, 0.0)) return;

    double first_body_ratio_distance(first_mass / mass_sum);
    double second_body_ratio_distance(second_mass / mass_sum);

    a2de::Vector2D first_second_direction(second_body_position - first_body_position);
    a2de::Vector2D second_first_direction(first_body_position - second_body_position);
    double second_first_magnitude(second_first_direction.GetLength());
    double first_second_magnitude(first_second_direction.GetLength());

    double second_magnitude = (_length - std::abs(second_first_magnitude)) * second_body_ratio_distance;
    double first_magnitude = (_length - std::abs(first_second_magnitude)) * first_body_ratio_distance;

    a2de::Vector2D first_impulse(second_first_direction.Normalize() * first_magnitude);
    a2de::Vector2D second_impulse(first_second_direction.Normalize() * second_magnitude);

    first_body->ApplyImpulse(first_impulse);
    second_body->ApplyImpulse(second_impulse);

    first_body->SetPosition(first_body_position + first_impulse);
    second_body->SetPosition(second_body_position + second_impulse);

}

void a2de::CableForceGenerator::AttachFirstEndTo(a2de::Object* body) {
    if(body == nullptr) return;
    _cable_ends.first = body;
}

void a2de::CableForceGenerator::AttachSecondEndTo(a2de::Object* body) {
    if(body == nullptr) return;
    _cable_ends.second = body;
}

void a2de::CableForceGenerator::DetachFirstEnd() {
    _cable_ends.first = nullptr;
}

void a2de::CableForceGenerator::DetachSecondEnd() {
    _cable_ends.second = nullptr;
}
