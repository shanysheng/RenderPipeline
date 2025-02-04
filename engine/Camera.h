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

        float GetFov() const { return m_Fov; }
        float GetAspect() const { return m_Aspect; }
        float GetNear() const { return m_Near; }
        float GetFar() const { return m_Far; }

        const glm::vec3& GetViewPos() const { return m_Position; }
        const glm::mat4& GetModelMat() const { return m_ModelMat; }
        const glm::mat4& GetViewMat() const { return m_ViewMat; }
        const glm::mat4& GetProjMat() const { return m_ProjMat; }

        void LookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
        void Perspective(float fov, float aspect, float znear, float zfar);

        void SetAspect(float aspect);

        void Zoom(float speed);
        void Pan(float xoffset, float yoffset);

        void RotateModel(float xoffset, float yoffset);

    protected:
        void UpdateViewMatrix();

        //const kMatrix4x4f& LookAt(const kVector3f& eye, const kVector3f& center, const kVector3f& up);
        //const kMatrix4x4f& Perspective(float fovy, float aspect, float zNear, float zFar);

        //bool ViewportToWorld( const kVector2f& pt, kVector3f& start, kVector3f& dir ) const;
        //bool ViewportToWorld( const kVector2f& pt, kVector3f& worldpt ) const;
        //bool ViewportToWorld( const kVector2f& pt, kVector3f& worldpt, const kVector3f& planept, const kVector3f& planenormal ) const;
        //bool WorldToViewport(const kVector3f& point, kVector2f& viewport_pt ) const;
        //
        //kRay ViewportPointToRay (const kVector3f& position);
        //kVector3f ViewportToScreenPoint (const kVector3f& position);
        //kVector3f ViewportToWorldPoint (const kVector3f& position);
        //kVector3f WorldToScreenPoint (const kVector3f& position);
        //kVector3f WorldToViewportPoint (const kVector3f& position);
        //
        //kSGNode* RaycastTry (const kRay& ray, float distance, int layerMask);
        //kSGNode* RaycastTry2D (const kRay& ray, float distance, int layerMask);
        //
        //kRay ScreenPointToRay (const kVector3f& position);
        //kVector3f ScreenToViewportPoint (const kVector3f& position);
        //kVector3f ScreenToWorldPoint (const kVector3f& position);
        //
        //
        //void CopyFrom (const kCamera& other);
        //void CalculateFrustumCorners (kRect viewport, float z, kVector3f outCorners[]);
        //
        //void DoClear ();
        //void Render ();
        //bool RenderToCubemap (kTexture* cubemap);
        

    protected:
        
        //bool            m_Orthographic;
        //
        //float           m_DefaultDepth ;
        //kColor          m_BackGroundColor;
        //
        //kMatrix4x4f     m_WorldToCameraMatrix ;
        //kMatrix4x4f     m_CullingMatrix ;
        //
        //kVector4f       m_ViewportRect ;


        float m_Fov, m_Aspect;
        float m_Near, m_Far;

        glm::vec3 m_Position;
        glm::vec3 m_Target;
        glm::vec3 m_Forward;
        glm::vec3 m_Updir;

        glm::mat4 m_ModelMat;
        glm::mat4 m_ViewMat;
        glm::mat4 m_ProjMat;
    };
}
#endif
