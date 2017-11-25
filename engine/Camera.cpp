#include "Camera.h"

namespace pipeline {
   
    Camera::Camera()
    {
        
    }
    
    Camera::~Camera()
    {
        
    }
    
    bool Camera::ViewportToWorld( const Vector2f& pt, Vector3f& start, Vector3f& dir ) const
    {
        return false;
    }
    
    bool Camera::ViewportToWorld( const Vector2f& pt, Vector3f& worldpt ) const
    {
        return false;
    }
    
    bool Camera::ViewportToWorld( const Vector2f& pt, Vector3f& worldpt, const Vector3f& planept, const Vector3f& planenormal ) const
    {
        return false;
    }
    
    bool Camera::WorldToViewport(const Vector3f& point, Vector2f& viewport_pt ) const
    {
        return false;
    }
    
    Ray Camera::ViewportPointToRay (const Vector3f& position)
    {
        return Ray();
    }
    
    Vector3f Camera::ViewportToScreenPoint (const Vector3f& position)
    {
        return Vector3f();
    }
    
    Vector3f Camera::ViewportToWorldPoint (const Vector3f& position)
    {
        return Vector3f();
    }
    
    Vector3f Camera::WorldToScreenPoint (const Vector3f& position)
    {
        return Vector3f();
    }
    
    Vector3f Camera::WorldToViewportPoint (const Vector3f& position)
    {
        return Vector3f();
    }
    
    SGNode* Camera::RaycastTry (const Ray& ray, float distance, int layerMask)
    {
        return NULL;
    }
    
    SGNode* Camera::RaycastTry2D (const Ray& ray, float distance, int layerMask)
    {
        return NULL;
    }
    
    Ray Camera::ScreenPointToRay (const Vector3f& position)
    {
        return Ray();
    }
    
    Vector3f Camera::ScreenToViewportPoint (const Vector3f& position)
    {
        return Vector3f();
    }
    
    Vector3f Camera::ScreenToWorldPoint (const Vector3f& position)
    {
        return Vector3f();
    }
    
    void Camera::CopyFrom (const Camera& other)
    {
        
    }
    
    void Camera::CalculateFrustumCorners (Rect viewport, float z, Vector3f outCorners[])
    {
        
    }
    
    void Camera::DoClear ()
    {
        
    }
    
    void Camera::Render ()
    {
        
    }
    
    bool Camera::RenderToCubemap (Texture* cubemap)
    {
        return false;
    }
}
