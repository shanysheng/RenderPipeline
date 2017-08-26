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

namespace pipeline {

    class Collider : Component
    {
        //
        // Properties
        //
        //Rigidbody attachedRigidbody ;
        
        //Bounds bounds ;
        
        float contactOffset ;
        
        bool enabled ;
        
        bool isTrigger ;
        
        //PhysicMaterial material ;
        
        //PhysicMaterial sharedMaterial;
        
        
        Vector3f ClosestPoint (Vector3f position);
        
        bool Raycast (Ray ray, out RaycastHit hitInfo, float maxDistance);
    }
    
    class BoxCollider : Collider
    {
        //
        // Properties
        //
        Vector3f center ;
        
        Vector3f size;
        
        
    }
    
    class CapsuleCollider : Collider
    {
        //
        // Properties
        //
        Vector3f center ;
        
        int direction ;
        
        float height ;
        
        float radius;
    }
    
    class SphereCollider : Collider
    {
        //
        // Properties
        //
        Vector3f center ;
        
        float radius ;
    }
    
    class MeshCollider : Collider
    {
        //
        // Properties
        //
        bool convex;
        
        bool inflateMesh ;
        
        Mesh sharedMesh;
        
        float skinWidth ;
    }
}

#endif
