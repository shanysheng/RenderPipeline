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

        void CopyFrom (const Camera& other);
        void CalculateFrustumCorners (Rect viewport, float z, Vector3f outCorners[]);
  
        void DoClear ();
        void Render ();
        bool RenderToCubemap (Texture* cubemap);

        SGNode* RaycastTry (Ray ray, float distance, int layerMask);
        SGNode* RaycastTry2D (Ray ray, float distance, int layerMask);
        
        Ray ScreenPointToRay (Vector3f position);
        Vector3f ScreenToViewportPoint (Vector3f position);
        Vector3f ScreenToWorldPoint (Vector3f position);
 
        bool ViewportToWorld( const Vector2f& pt, Vector3f& start, Vector3f& dir ) const;
        bool ViewportToWorld( const Vector2f& pt, Vector3f& worldpt ) const;
        bool ViewportToWorld( const Vector2f& pt, Vector3f& worldpt, const Vector3f& planept, const Vector3f& planenormal ) const;
        bool WorldToViewport(const Vector3f& point, Vector2f& viewport_pt ) const;
        
        Ray ViewportPointToRay (Vector3f position);
        Vector3f ViewportToScreenPoint (Vector3f position);
        Vector3f ViewportToWorldPoint (Vector3f position);
        Vector3f WorldToScreenPoint (Vector3f position);
        Vector3f WorldToViewportPoint (Vector3f position);
        
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
