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
        
        Transform parent;
        
        
        Vector3f position ;
        
        Vector3f right ;
        
        Transform root ;
        Matrix4x4f rotation ;
        
        Vector3f up ;
        
        Matrix4x4f worldToLocalMatrix ;
        
        void DetachChildren ();
        
  
        Transform Find (const std::string& name);
        
        Transform FindChild (const std::string& name);
        
        Transform GetChild (int index);
        
        
        Vector3f GetLocalEulerAngles (RotationOrder order);
        
        Vector3f InverseTransformDirection (Vector3f direction);
        
        Vector3f InverseTransformDirection (float x, float y, float z);
        
        Vector3f InverseTransformPoint (Vector3f position);
        
        Vector3f InverseTransformPoint (float x, float y, float z);
        
        Vector3f InverseTransformVector (Vector3f vector);
        
        Vector3f InverseTransformVector (float x, float y, float z);
        bool IsChildOf (Transform parent);
        
        bool IsNonUniformScaleTransform ();
        
        void LookAt (Transform target);
        void LookAt (Vector3f worldPosition);
        
        void LookAt (Vector3f worldPosition, Vector3f worldUp);
        
        void LookAt (Transform target, Vector3f worldUp);
        
        void Rotate (Vector3f eulerAngles, Space relativeTo);
        void Rotate (Vector3f eulerAngles);
        void Rotate (float xAngle, float yAngle, float zAngle);
        
        void Rotate (float xAngle, float yAngle, float zAngle, Space relativeTo);
        void Rotate (Vector3f axis, float angle);
        
        void Rotate (Vector3f axis, float angle, Space relativeTo);
        
        void RotateAround (Vector3f point, Vector3f axis, float angle);
        void RotateAroundLocal (Vector3f axis, float angle);
        void SendTransformChangedScale ();
        
        void SetAsFirstSibling ();
        
        void SetAsLastSibling ();
        
        void SetLocalEulerAngles (Vector3f euler, RotationOrder order);
        
        void SetLocalEulerHint (Vector3f euler);
        void SetParent (Transform parent, bool worldPositionStays);
        
        void SetParent (Transform parent);
        
        void SetPositionAndRotation (Vector3f position, Matrix4x4f rotation);
        void SetSiblingIndex (int index);
        
        Vector3f TransformDirection (Vector3f direction);
        
        Vector3f TransformDirection (float x, float y, float z);
        
        Vector3f TransformPoint (Vector3f position);
        
        Vector3f TransformPoint (float x, float y, float z);
        
        Vector3f TransformVector (float x, float y, float z);
        
        Vector3f TransformVector (Vector3f vector);
        
        void Translate (Vector3f translation);
        
        void Translate (Vector3f translation, [DefaultValue ("Space.Self")] Space relativeTo);
        
        void Translate (float x, float y, float z);
        
        void Translate (float x, float y, float z, [DefaultValue ("Space.Self")] Space relativeTo);
        
        void Translate (Vector3f translation, Transform relativeTo);
        
        void Translate (float x, float y, float z, Transform relativeTo);
    };
}

#endif
