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
    
    class kSGNode;
    class kRenderTarget;
    class kTexture;
    
    class kCamera
    {
    public:
        kCamera();
        ~kCamera();
 
        bool ViewportToWorld( const kVector2f& pt, kVector3f& start, kVector3f& dir ) const;
        bool ViewportToWorld( const kVector2f& pt, kVector3f& worldpt ) const;
        bool ViewportToWorld( const kVector2f& pt, kVector3f& worldpt, const kVector3f& planept, const kVector3f& planenormal ) const;
        bool WorldToViewport(const kVector3f& point, kVector2f& viewport_pt ) const;
        
        kRay ViewportPointToRay (const kVector3f& position);
        kVector3f ViewportToScreenPoint (const kVector3f& position);
        kVector3f ViewportToWorldPoint (const kVector3f& position);
        kVector3f WorldToScreenPoint (const kVector3f& position);
        kVector3f WorldToViewportPoint (const kVector3f& position);
        
        kSGNode* RaycastTry (const kRay& ray, float distance, int layerMask);
        kSGNode* RaycastTry2D (const kRay& ray, float distance, int layerMask);
        
        kRay ScreenPointToRay (const kVector3f& position);
        kVector3f ScreenToViewportPoint (const kVector3f& position);
        kVector3f ScreenToWorldPoint (const kVector3f& position);
        
        
        void CopyFrom (const kCamera& other);
        void CalculateFrustumCorners (kRect viewport, float z, kVector3f outCorners[]);
        
        void DoClear ();
        void Render ();
        bool RenderToCubemap (kTexture* cubemap);
        

    public:
        
        bool m_Orthographic;
        
        float m_Aspect ;
        float m_FieldOfView ;
        float m_NearClipPlane ;
        float m_FarClipPlane ;
        
        float m_DefaultDepth ;
        kColor m_BackGroundColor;
        
        kVector3f    m_Position;
        kVector3f    m_Target;
        kVector3f    m_Updir;
        
        kMatrix4x4f m_CameraToWorldMatrix;
        kMatrix4x4f m_ProjectionMatrix ;
        kMatrix4x4f m_WorldToCameraMatrix ;
        kMatrix4x4f m_CullingMatrix ;
        
        kVector4f m_ViewportRect ;
        kRenderTarget* targetTexture ;
    };
}
#endif
