#ifndef A2DE_CTRANSFORM_H
#define A2DE_CTRANSFORM_H

#include "../a2de_vals.h"
#include "CMatrix4x4.h"
#include "CVector3D.h"

#include <vector>

A2DE_BEGIN

class Transform {
public:

    Transform();
    Transform(Transform* parent);
    Transform(const Transform& other);
    Transform& operator=(const Transform& rhs);
    virtual ~Transform();

    void SetParent(Transform* parent);
    void AddChild(Transform* child);
    void RemoveChild(Transform* child);

    Transform* FirstChild();
    Transform* LastChild();
    Transform* NextChild();
    Transform* PreviousChild();
    Transform* GetChild(std::size_t index);

    std::size_t GetChildCount() const;
    std::size_t GetChildCount();

    void SetPosition(const a2de::Vector3D& position);
    const a2de::Vector3D& GetPosition() const;
    a2de::Vector3D& GetPosition();

    void SetRotation(const a2de::Vector3D& rotation);
    const a2de::Vector3D& GetRotation() const;
    a2de::Vector3D& GetRotation();

    void SetScale(const a2de::Vector3D& scale);
    const a2de::Vector3D& GetScale() const;
    a2de::Vector3D& GetScale();

    a2de::Matrix4x4 GetLocalTransform() const;
    a2de::Matrix4x4 GetLocalTransform();

protected:

private:
    a2de::Vector3D _position;
    a2de::Vector3D _scale;
    a2de::Vector3D _rotation;
    std::size_t _curChildIndex;
    Transform* _parent;
    std::vector<Transform*> _children;    
};

A2DE_END

#endif