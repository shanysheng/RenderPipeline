/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_CAMERA_H_GUARD
#define PIPELINE_CAMERA_H_GUARD

#include "Common.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Color.h"
#include "Rect.h"
#include "Ray.h"

namespace pipeline {
    
    class SGNode;
    class RenderTarget;
    class Texture;
    
    class Camera
    {
    public:
        Camera();
        ~Camera();

 
        bool ViewportToWorld( const Vector2f& pt, Vector3f& start, Vector3f& dir ) const;
        bool ViewportToWorld( const Vector2f& pt, Vector3f& worldpt ) const;
        bool ViewportToWorld( const Vector2f& pt, Vector3f& worldpt, const Vector3f& planept, const Vector3f& planenormal ) const;
        bool WorldToViewport(const Vector3f& point, Vector2f& viewport_pt ) const;
        
        Ray ViewportPointToRay (const Vector3f& position);
        Vector3f ViewportToScreenPoint (const Vector3f& position);
        Vector3f ViewportToWorldPoint (const Vector3f& position);
        Vector3f WorldToScreenPoint (const Vector3f& position);
        Vector3f WorldToViewportPoint (const Vector3f& position);
        
        SGNode* RaycastTry (const Ray& ray, float distance, int layerMask);
        SGNode* RaycastTry2D (const Ray& ray, float distance, int layerMask);
        
        Ray ScreenPointToRay (const Vector3f& position);
        Vector3f ScreenToViewportPoint (const Vector3f& position);
        Vector3f ScreenToWorldPoint (const Vector3f& position);
        
        
        void CopyFrom (const Camera& other);
        void CalculateFrustumCorners (Rect viewport, float z, Vector3f outCorners[]);
        
        void DoClear ();
        void Render ();
        bool RenderToCubemap (Texture* cubemap);
        

    public:
        
        bool m_Orthographic;
        
        float m_Aspect ;
        float m_FieldOfView ;
        float m_NearClipPlane ;
        float m_FarClipPlane ;
        
        float m_DefaultDepth ;
        Color m_BackGroundColor;
        
        Vector3f    m_Position;
        Vector3f    m_Target;
        Vector3f    m_Updir;
        
        Matrix4x4f m_CameraToWorldMatrix;
        Matrix4x4f m_ProjectionMatrix ;
        Matrix4x4f m_WorldToCameraMatrix ;
        Matrix4x4f m_CullingMatrix ;
        
        Vector4f m_ViewportRect ;
        RenderTarget* targetTexture ;
    };
}
#endif
