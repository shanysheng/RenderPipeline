/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_TRANSFORM_H_GUARD
#define PIPELINE_TRANSFORM_H_GUARD

#include "Common.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

namespace pipeline {

    class Transform
    {
    public:

        Transform();
        
        Transform* Find (const std::string& name);
        Transform* FindChild (const std::string& name);
        Transform* GetChild (int index);
        void DetachChildren ();

        Vector3f GetLocalEulerAngles ();
        Vector3f InverseTransformDirection (const Vector3f& direction);
        Vector3f InverseTransformDirection (float x, float y, float z);
        Vector3f InverseTransformPoint (const Vector3f& position);
        Vector3f InverseTransformPoint (float x, float y, float z);
        Vector3f InverseTransformVector (const Vector3f& vector);
        Vector3f InverseTransformVector (float x, float y, float z);

        bool IsChildOf (const Transform& parent);
        bool IsNonUniformScaleTransform ();
        
        void LookAt (const Transform& target);
        void LookAt (const Vector3f& worldPosition);
        void LookAt (const Vector3f& worldPosition, const Vector3f& worldUp);
        void LookAt (const Transform& target, const Vector3f& worldUp);
        
        void Rotate (const Vector3f& eulerAngles);
        void Rotate (float xAngle, float yAngle, float zAngle);
        void Rotate (const Vector3f& axis, float angle);
        
        void RotateAround (const Vector3f& point, const Vector3f& axis, float angle);
        void RotateAroundLocal (const Vector3f& axis, float angle);
        void SendTransformChangedScale ();
        
        void SetAsFirstSibling ();
        void SetAsLastSibling ();
        
        void SetLocalEulerHint (const Vector3f& euler);
        void SetParent (const Transform& parent, bool worldPositionStays);
        void SetParent (const Transform& parent);
        void SetPositionAndRotation (const Vector3f& position, Matrix4x4f rotation);
        void SetSiblingIndex (int index);
        
        Vector3f TransformDirection (const Vector3f& direction);
        Vector3f TransformDirection (float x, float y, float z);
        Vector3f TransformPoint (const Vector3f& position);
        Vector3f TransformPoint (float x, float y, float z);
        Vector3f TransformVector (float x, float y, float z);
        Vector3f TransformVector (const Vector3f& vector);
        
        void Translate (const Vector3f& translation);
        void Translate (float x, float y, float z);
        void Translate (const Vector3f& translation, const Transform& relativeTo);
        void Translate (float x, float y, float z, const Transform& relativeTo);
        
    protected:
        //
        // Properties
        //
        int childCount ;
        
        Vector3f eulerAngles ;
        Vector3f forward ;
        bool hasChanged ;
        int hierarchyCapacity ;
        int hierarchyCount ;
        
        Vector3f localEulerAngles ;
        Vector3f localPosition ;
        Matrix4x4f localRotation ;
        Vector3f localScale ;
        
        Matrix4x4f localToWorldMatrix;
        Vector3f lossyScale;
        
        
        Vector3f up ;
        Vector3f right ;
        
        Matrix4x4f rotation ;
        Vector3f position ;
        
        Matrix4x4f worldToLocalMatrix ;
    };
}

#endif
