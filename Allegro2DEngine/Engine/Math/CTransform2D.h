#ifndef A2DE_CTRANSFORM2D_H
#define A2DE_CTRANSFORM2D_H

#include "../a2de_vals.h"
#include "CMatrix3x3.h"
#include "CVector2D.h"

#include <vector>

A2DE_BEGIN

class Transform2D {
public:
    Transform2D();
    Transform2D(Transform2D* parent);
    Transform2D(const Transform2D& other);
    Transform2D& operator=(const Transform2D& rhs);
    virtual ~Transform2D();

    void SetParent(Transform2D* parent);
    void AddChild(Transform2D* child);
    void RemoveChild(Transform2D* child);

    Transform2D* FirstChild();
    Transform2D* LastChild();
    Transform2D* NextChild();
    Transform2D* PreviousChild();
    Transform2D* GetChild(std::size_t index);

    std::vector<Transform2D*>::size_type GetChildCount() const;
    std::vector<Transform2D*>::size_type GetChildCount();

    void SetPosition(const a2de::Vector2D& position);
    const a2de::Vector2D& GetPosition() const;
    a2de::Vector2D& GetPosition();

    void SetRotation(double rotation);
    double GetRotation() const;
    double GetRotation();

    void SetScale(const a2de::Vector2D& scale);
    const a2de::Vector2D& GetScale() const;
    a2de::Vector2D& GetScale();

    a2de::Matrix3x3 GetLocalTransform() const;
    a2de::Matrix3x3 GetLocalTransform();

    a2de::Matrix3x3 RotateAround(const a2de::Vector2D& point);
protected:

private:
    a2de::Vector2D _position;
    a2de::Vector2D _scale;
    double _rotation;
    std::size_t _curChildIndex;
    Transform2D* _parent;
    std::vector<Transform2D*> _children;
};

A2DE_END

#endif