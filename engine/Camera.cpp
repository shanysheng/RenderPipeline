#include "Camera.h"

namespace pipeline {
   
    kCamera::kCamera()
    {
        
    }
    
    kCamera::~kCamera()
    {
        
    }
    
    bool kCamera::ViewportToWorld( const kVector2f& pt, kVector3f& start, kVector3f& dir ) const
    {
        return false;
    }
    
    bool kCamera::ViewportToWorld( const kVector2f& pt, kVector3f& worldpt ) const
    {
        return false;
    }
    
    bool kCamera::ViewportToWorld( const kVector2f& pt, kVector3f& worldpt, const kVector3f& planept, const kVector3f& planenormal ) const
    {
        return false;
    }
    
    bool kCamera::WorldToViewport(const kVector3f& point, kVector2f& viewport_pt ) const
    {
        return false;
    }
    
    kRay kCamera::ViewportPointToRay (const kVector3f& position)
    {
        return kRay();
    }
    
    kVector3f kCamera::ViewportToScreenPoint (const kVector3f& position)
    {
        return kVector3f();
    }
    
    kVector3f kCamera::ViewportToWorldPoint (const kVector3f& position)
    {
        return kVector3f();
    }
    
    kVector3f kCamera::WorldToScreenPoint (const kVector3f& position)
    {
        return kVector3f();
    }
    
    kVector3f kCamera::WorldToViewportPoint (const kVector3f& position)
    {
        return kVector3f();
    }
    
    kSGNode* kCamera::RaycastTry (const kRay& ray, float distance, int layerMask)
    {
        return NULL;
    }
    
    kSGNode* kCamera::RaycastTry2D (const kRay& ray, float distance, int layerMask)
    {
        return NULL;
    }
    
    kRay kCamera::ScreenPointToRay (const kVector3f& position)
    {
        return kRay();
    }
    
    kVector3f kCamera::ScreenToViewportPoint (const kVector3f& position)
    {
        return kVector3f();
    }
    
    kVector3f kCamera::ScreenToWorldPoint (const kVector3f& position)
    {
        return kVector3f();
    }
    
    void kCamera::CopyFrom (const kCamera& other)
    {
        
    }
    
    void kCamera::CalculateFrustumCorners (kRect viewport, float z, kVector3f outCorners[])
    {
        
    }
    
    void kCamera::DoClear ()
    {
        
    }
    
    void kCamera::Render ()
    {
        
    }
    
    bool kCamera::RenderToCubemap (kTexture* cubemap)
    {
        return false;
    }
}
