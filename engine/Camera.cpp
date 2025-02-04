#include "Camera.h"

namespace pipeline {
   
    kCamera::kCamera()
    {
        m_Fov = 60.0f;
        m_Aspect = 1.33f;
        m_Near = 0.1f;
        m_Far = 100.0f;

        m_Target = glm::vec3();
        m_Position = glm::vec3(1.0f, 1.0f, 1.0f);
        m_Updir = glm::vec3(0.0f, 1.0f, 0.0f);

        m_ModelMat = glm::mat4(1.0f);
    }
    
    kCamera::~kCamera()
    {
        
    }

    void kCamera::LookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {

        m_Position = eye;
        m_Target = target;
        m_Updir = up;
        m_Forward = glm::normalize(m_Target - m_Position);
        
        m_ViewMat = glm::lookAt(eye, target, up);

    }

    void kCamera::Perspective(float fov, float aspect, float znear, float zfar)
    {
        this->m_Fov = fov;
        this->m_Near = znear;
        this->m_Far = zfar;
        this->m_Aspect = aspect;

        m_ProjMat = glm::perspective(glm::radians(fov), aspect, znear, zfar);

        // The NDC x,y coordinates of Vulkan if from [-1,-1] top left corner to [1,1] 
        // bottom right corner of your screen. Like I imagine a bitmap image to go from 
        // top to bottom, left to right. I may be weird in that sense. OpenGL is from 
        // [-1,-1] bottom left corner, to [1,1] top right corner.
        // 
        // GLM was originally designed for OpenGL, where the Y coordinate of the clip 
        // coordinates is inverted. The easiest way to compensate for that is to flip 
        // the sign on the scaling factor of the Y axis in the projection matrix. If 
        // you don't do this, then the image will be rendered upside down. 
        m_ProjMat[1][1] *= -1.0f;
    };

    void kCamera::SetAspect(float aspect)
    {
        this->m_Aspect = aspect;
        m_ProjMat = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
        m_ProjMat[1][1] *= -1.0f;
    }

    void kCamera::RotateModel(float xoffset, float yoffset)
    {
        glm::vec3 sidedir = glm::cross(m_Forward, m_Updir);

        m_ModelMat = glm::rotate(m_ModelMat, glm::radians(yoffset), sidedir);
        m_ModelMat = glm::rotate(m_ModelMat, glm::radians(xoffset), m_Updir);

        UpdateViewMatrix();
    }

    void kCamera::Zoom(float speed)
    {
        this->m_Position += m_Forward * speed;
        this->m_Target += m_Forward * speed;
        UpdateViewMatrix();
    }

    void kCamera::Pan(float xoffset, float yoffset)
    {
        glm::vec3 sidedir = glm::cross( m_Forward, m_Updir);
        glm::vec3 cameraup = glm::cross(sidedir, m_Forward);

        this->m_Position += sidedir * xoffset;
        this->m_Target += sidedir * xoffset;
        this->m_Position -= cameraup * yoffset;
        this->m_Target -= cameraup * yoffset;
        UpdateViewMatrix();
    }

    void kCamera::UpdateViewMatrix()
    {
        glm::mat4 rotM = m_ModelMat;
        glm::mat4 viewmat = glm::lookAt(m_Position, m_Target, m_Updir);
        

        m_ViewMat = viewmat * rotM;

        // for debug
        glm::quat rotateQuat = m_ModelMat;
        glm::vec3 rotation = glm::eulerAngles(rotateQuat);
        std::cout <<"pos:" << m_Position.x << "," << m_Position.y << "," << m_Position.z << ", rot:" << rotation.x << "," << rotation.y << "," << rotation.z << std::endl;
    };

    //const kMatrix4x4f& kCamera::LookAt(const kVector3f& eye, const kVector3f& center, const kVector3f& up) {

    //}

    //const kMatrix4x4f& kCamera::Perspective(float fovy, float aspect, float zNear, float zFar) {

    //}

    //
    //bool kCamera::ViewportToWorld( const kVector2f& pt, kVector3f& start, kVector3f& dir ) const
    //{
    //    return false;
    //}
    //
    //bool kCamera::ViewportToWorld( const kVector2f& pt, kVector3f& worldpt ) const
    //{
    //    return false;
    //}
    //
    //bool kCamera::ViewportToWorld( const kVector2f& pt, kVector3f& worldpt, const kVector3f& planept, const kVector3f& planenormal ) const
    //{
    //    return false;
    //}
    //
    //bool kCamera::WorldToViewport(const kVector3f& point, kVector2f& viewport_pt ) const
    //{
    //    return false;
    //}
    //
    //kRay kCamera::ViewportPointToRay (const kVector3f& position)
    //{
    //    return kRay();
    //}
    //
    //kVector3f kCamera::ViewportToScreenPoint (const kVector3f& position)
    //{
    //    return kVector3f();
    //}
    //
    //kVector3f kCamera::ViewportToWorldPoint (const kVector3f& position)
    //{
    //    return kVector3f();
    //}
    //
    //kVector3f kCamera::WorldToScreenPoint (const kVector3f& position)
    //{
    //    return kVector3f();
    //}
    //
    //kVector3f kCamera::WorldToViewportPoint (const kVector3f& position)
    //{
    //    return kVector3f();
    //}
    //
    //kSGNode* kCamera::RaycastTry (const kRay& ray, float distance, int layerMask)
    //{
    //    return NULL;
    //}
    //
    //kSGNode* kCamera::RaycastTry2D (const kRay& ray, float distance, int layerMask)
    //{
    //    return NULL;
    //}
    //
    //kRay kCamera::ScreenPointToRay (const kVector3f& position)
    //{
    //    return kRay();
    //}
    //
    //kVector3f kCamera::ScreenToViewportPoint (const kVector3f& position)
    //{
    //    return kVector3f();
    //}
    //
    //kVector3f kCamera::ScreenToWorldPoint (const kVector3f& position)
    //{
    //    return kVector3f();
    //}
    //
    //void kCamera::CopyFrom (const kCamera& other)
    //{
    //    
    //}
    //
    //void kCamera::CalculateFrustumCorners (kRect viewport, float z, kVector3f outCorners[])
    //{
    //    
    //}
    //
    //void kCamera::DoClear ()
    //{
    //    
    //}
    //
    //void kCamera::Render ()
    //{
    //    
    //}
    //
    //bool kCamera::RenderToCubemap (kTexture* cubemap)
    //{
    //    return false;
    //}
}
