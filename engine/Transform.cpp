#include "Transform.h"

namespace pipeline {
    
    
    Transform::Transform()
    {
        
    }
    
    Transform* Transform::Find (const std::string& name)
    {
        return NULL;
    }
    
    Transform* Transform::FindChild (const std::string& name)
    {
        return NULL;
    }
    
    Transform* Transform::GetChild (int index)
    {
        return NULL;
    }
    
    void Transform::DetachChildren ()
    {
        
    }
    
    Vector3f Transform::GetLocalEulerAngles ()
    {
        return Vector3f();
    }
    
    Vector3f Transform::InverseTransformDirection (const Vector3f& direction)
    {
        return Vector3f();
    }
    
    Vector3f Transform::InverseTransformDirection (float x, float y, float z)
    {
        return Vector3f();
    }
    
    Vector3f Transform::InverseTransformPoint (const Vector3f& position)
    {
        return Vector3f();
    }
    
    Vector3f Transform::InverseTransformPoint (float x, float y, float z)
    {
        return Vector3f();
    }
    
    Vector3f Transform::InverseTransformVector (const Vector3f& vector)
    {
        return Vector3f();
    }
    
    Vector3f Transform::InverseTransformVector (float x, float y, float z)
    {
        return Vector3f();
    }
    
    bool Transform::IsChildOf (const Transform& parent)
    {
        return false;
    }
    
    bool Transform::IsNonUniformScaleTransform ()
    {
        return true;
    }
    
    void Transform::LookAt (const Transform& target)
    {
        
    }
    
    void Transform::LookAt (const Vector3f& worldPosition)
    {
        
    }
    
    void Transform::LookAt (const Vector3f& worldPosition, const Vector3f& worldUp)
    {
        
    }
    
    void Transform::LookAt (const Transform& target, const Vector3f& worldUp)
    {
        
    }
    
    void Transform::Rotate (const Vector3f& eulerAngles)
    {
        
    }
    
    void Transform::Rotate (float xAngle, float yAngle, float zAngle)
    {
        
    }
    
    void Transform::Rotate (const Vector3f& axis, float angle)
    {
        
    }
    
    void Transform::RotateAround (const Vector3f& point, const Vector3f& axis, float angle)
    {
        
    }
    
    void Transform::RotateAroundLocal (const Vector3f& axis, float angle)
    {
        
    }
    
    void Transform::SendTransformChangedScale ()
    {
        
    }
    
    void Transform::SetAsFirstSibling ()
    {
        
    }
    
    void Transform::SetAsLastSibling ()
    {
        
    }
    
    
    void Transform::SetLocalEulerHint (const Vector3f& euler)
    {
        
    }
    
    void Transform::SetParent (const Transform& parent, bool worldPositionStays)
    {
        
    }
    
    void Transform::SetParent (const Transform& parent)
    {
        
    }
    
    void Transform::SetPositionAndRotation (const Vector3f& position, Matrix4x4f rotation)
    {
        
    }
    
    void Transform::SetSiblingIndex (int index)
    {
        
    }
    
    
    Vector3f Transform::TransformDirection (const Vector3f& direction)
    {
        return Vector3f();
    }
    
    Vector3f Transform::TransformDirection (float x, float y, float z)
    {
        return Vector3f();
    }
    
    Vector3f Transform::TransformPoint (const Vector3f& position)
    {
        return Vector3f();
    }
    
    Vector3f Transform::TransformPoint (float x, float y, float z)
    {
        return Vector3f();
    }
    
    Vector3f Transform::TransformVector (float x, float y, float z)
    {
        return Vector3f();
    }
    
    Vector3f Transform::TransformVector (const Vector3f& vector)
    {
        return Vector3f();
    }
    
    
    void Transform::Translate (const Vector3f& translation)
    {
        
    }
    
    void Transform::Translate (float x, float y, float z)
    {
        
    }
    
    void Transform::Translate (const Vector3f& translation, const Transform& relativeTo)
    {
        
    }
    
    void Transform::Translate (float x, float y, float z, const Transform& relativeTo)
    {
        
    }
    
}
