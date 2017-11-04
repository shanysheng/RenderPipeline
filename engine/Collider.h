/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_COLLIDER_H_GUARD
#define PIPELINE_COLLIDER_H_GUARD

#include "Common.h"
#include "Component.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Ray.h"

namespace pipeline {
    
    class Mesh;

    class Collider : Component
    {
    public:
        float contactOffset ;
        bool enabled ;
        bool isTrigger ;
        
        //Bounds bounds ;
        //Rigidbody attachedRigidbody ;
        //PhysicMaterial material ;
        //PhysicMaterial sharedMaterial;
        
        Vector3f ClosestPoint (Vector3f position);
    };
    
    class BoxCollider : Collider
    {
    public:
        Vector3f center ;
        Vector3f size;
    };
    
    class CapsuleCollider : Collider
    {
    public:
        Vector3f center ;
        int direction ;
        float height ;
        float radius;
    };
    
    class SphereCollider : Collider
    {
    public:
        Vector3f center ;
        float radius ;
    };
    
    class MeshCollider : Collider
    {
    public:
        bool convex;
        bool inflateMesh ;
        Mesh* psharedMesh;
        float skinWidth ;
    };
}

#endif
