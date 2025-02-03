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

        void setPerspective(float fov, float aspect, float znear, float zfar)
        {
            glm::mat4 currentMatrix = matrices.perspective;
            this->fov = fov;
            this->znear = znear;
            this->zfar = zfar;
            matrices.perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
            if (flipY) {
                matrices.perspective[1][1] *= -1.0f;
            }
            if (matrices.view != currentMatrix) {
                updated = true;
            }
        };

        float getNearClip() const {
            return znear;
        }

        float getFarClip() const {
            return zfar;
        }

        void updateAspectRatio(float aspect)
        {
            glm::mat4 currentMatrix = matrices.perspective;
            matrices.perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
            if (flipY) {
                matrices.perspective[1][1] *= -1.0f;
            }
            if (matrices.view != currentMatrix) {
                updated = true;
            }
        }

        void setPosition(glm::vec3 position)
        {
            this->position = position;
            updateViewMatrix();
        }

        void setRotation(glm::vec3 rotation)
        {
            this->rotation = rotation;
            updateViewMatrix();
        }

        void rotate(glm::vec3 delta)
        {
            this->rotation += delta;
            updateViewMatrix();
        }

        void setTranslation(glm::vec3 translation)
        {
            this->position = translation;
            updateViewMatrix();
        };

        void translate(glm::vec3 delta)
        {
            this->position += delta;
            updateViewMatrix();
        }

        void setRotationSpeed(float rotationSpeed)
        {
            this->rotationSpeed = rotationSpeed;
        }

        void setMovementSpeed(float movementSpeed)
        {
            this->movementSpeed = movementSpeed;
        }

        void updateViewMatrix()
        {
            glm::mat4 currentMatrix = matrices.view;

            glm::mat4 rotM = glm::mat4(1.0f);
            glm::mat4 transM;

            rotM = glm::rotate(rotM, glm::radians(rotation.x * (flipY ? -1.0f : 1.0f)), glm::vec3(1.0f, 0.0f, 0.0f));
            rotM = glm::rotate(rotM, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            rotM = glm::rotate(rotM, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

            glm::vec3 translation = position;
            if (flipY) {
                translation.y *= -1.0f;
            }
            transM = glm::translate(glm::mat4(1.0f), translation);

            if (type == CameraType::firstperson)
            {
                matrices.view = rotM * transM;
            }
            else
            {
                matrices.view = transM * rotM;
            }

            viewPos = glm::vec4(position, 0.0f) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);

            if (matrices.view != currentMatrix) {
                updated = true;
            }
        };

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
        

    public:
        
        //bool            m_Orthographic;
        //
        //float           m_Aspect ;
        //float           m_FieldOfView ;
        //float           m_NearClipPlane ;
        //float           m_FarClipPlane ;
        //
        //float           m_DefaultDepth ;
        //kColor          m_BackGroundColor;
        //
        //kVector3f       m_Position;
        //kVector3f       m_Target;
        //kVector3f       m_Updir;
        //
        //kMatrix4x4f     m_CameraToWorldMatrix;
        //kMatrix4x4f     m_ProjectionMatrix ;
        //kMatrix4x4f     m_WorldToCameraMatrix ;
        //kMatrix4x4f     m_CullingMatrix ;
        //
        //kVector4f       m_ViewportRect ;

        enum CameraType { lookat, firstperson };
        CameraType type = CameraType::lookat;

        float fov;
        float znear, zfar;

        bool updated = true;
        bool flipY = true;

        glm::vec3 rotation = glm::vec3();
        glm::vec3 position = glm::vec3();
        glm::vec4 viewPos = glm::vec4();

        float rotationSpeed = 1.0f;
        float movementSpeed = 1.0f;

        struct
        {
            glm::mat4 perspective;
            glm::mat4 view;
        } matrices;
    };
}
#endif
