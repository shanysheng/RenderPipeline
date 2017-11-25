/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_MATRIX4X4_H_GUARD
#define PIPELINE_MATRIX4X4_H_GUARD

#include "Common.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

namespace pipeline{
    
    // Matrix elements are accessed with m[row][column].
    class Matrix4x4f
    {
    public:
        float m[16];
        
        static const Matrix4x4f identity;

    public:
        Matrix4x4f();
        Matrix4x4f(const Matrix4x4f& rhs);
        
        Matrix4x4f operator* (const Matrix4x4f& rhs) const;
        void operator*=(const Matrix4x4f& rhs);
        Matrix4x4f operator+ (const Matrix4x4f& rhs) const;
        void operator+=(const Matrix4x4f& rhs);
        Matrix4x4f operator* (float scale) const;
        void operator*=(float scale);
        inline bool operator==(const Matrix4x4f& rhs) const;
        inline bool Equals(const Matrix4x4f& rhs, float tolerance) const;
        inline bool operator!=(const Matrix4x4f& rhs) const;
        Vector4f TransformVector4f(const Vector4f& vec4) const;
        Vector4f TransformPosition(const Vector3f& vec3) const;
        Vector3f InverseTransformPosition(const Vector3f& vec3) const;
        Vector4f TransformVector(const Vector3f& vec3) const;
        Vector3f InverseTransformVector(const Vector3f& vec3) const;
        Matrix4x4f GetTransposed() const;
        inline float Determinant() const;
        Matrix4x4f Inverse() const;
        
        void SetAxisX( const Vector3f& vec3);
        void SetAxisY( const Vector3f& vec3);
        void SetAxisZ( const Vector3f& vec3);
        void SetAxis( int axis, const Vector3f& vec3);
        void SetPosition( const Vector3f& vec3);
        void SetRow( int row, const Vector4f& vec3);
        void SetColumn( int col, const Vector4f& vec3);
        
        void SetTR (const Vector3f& pos, const Quaternionf& q);
        void SetTRS (const Vector3f& pos, const Quaternionf& q, const Vector3f& s);
        
        Vector3f MultiplyVector3 (const Vector3f& inV) const;
        Vector4f MultiplyVector4 (const Vector4f& inV) const;
        Vector3f MultiplyPoint3 (const Vector3f& inV) const;

        void MultiplyVector3 (const Vector3f& inV, Vector3f& output) const;
        void MultiplyVector4 (const Vector4f& inV, Vector4f& output) const;
        void MultiplyPoint3 (const Vector3f& inV, Vector3f& output) const;
        
        Matrix4x4f& SetIdentity ();
        Matrix4x4f& SetPerspective( float fovy, float aspect, float zNear, float zFar);
        Matrix4x4f& SetPerspective( float left, float right, float top, float bottom, float zNear, float zFar);
        Matrix4x4f& SetOrtho( float left, float right, float bottom, float top, float zNear, float zFar);
        Matrix4x4f& SetFrustum( float left, float right, float bottom, float top, float nearval, float farval);
    };
    
    inline Matrix4x4f::Matrix4x4f()
    {
        
    }
    
    inline Matrix4x4f::Matrix4x4f(const Matrix4x4f& rhs)
    {
        
    }
    
    
    inline Matrix4x4f Matrix4x4f::operator* (const Matrix4x4f& rhs) const
    {
        
    }
    
    inline void Matrix4x4f::operator*=(const Matrix4x4f& rhs)
    {
        
    }
    
    inline Matrix4x4f Matrix4x4f::operator+ (const Matrix4x4f& rhs) const
    {
        
    }
    
    inline void Matrix4x4f::operator+=(const Matrix4x4f& rhs)
    {
        
    }
    
    inline Matrix4x4f Matrix4x4f::operator* (float scale) const
    {
        
    }
    
    inline void Matrix4x4f::operator*=(float scale)
    {
        
    }
    
    inline bool Matrix4x4f::operator==(const Matrix4x4f& rhs) const
    {
        
    }
    
    inline bool Matrix4x4f::Equals(const Matrix4x4f& rhs, float tolerance) const
    {
        
    }
    
    inline bool Matrix4x4f::operator!=(const Matrix4x4f& rhs) const
    {
        
    }
    
    inline Vector4f Matrix4x4f::TransformVector4f(const Vector4f& vec4) const
    {
        
    }
    
    inline Vector4f Matrix4x4f::TransformPosition(const Vector3f& vec3) const
    {
        
    }
    
    inline Vector3f Matrix4x4f::InverseTransformPosition(const Vector3f& vec3) const
    {
        
    }
    
    inline Vector4f Matrix4x4f::TransformVector(const Vector3f& vec3) const
    {
        
    }
    
    inline Vector3f Matrix4x4f::InverseTransformVector(const Vector3f& vec3) const
    {
        
    }
    
    inline Matrix4x4f Matrix4x4f::GetTransposed() const
    {
        
    }
    
    inline float Matrix4x4f::Determinant() const
    {
        
    }
    
    inline Matrix4x4f Matrix4x4f::Inverse() const
    {
        
    }
    
    
    inline void Matrix4x4f::SetAxisX( const Vector3f& vec3)
    {
        
    }
    
    inline void Matrix4x4f::SetAxisY( const Vector3f& vec3)
    {
        
    }
    
    inline void Matrix4x4f::SetAxisZ( const Vector3f& vec3)
    {
        
    }
    
    inline void Matrix4x4f::SetAxis( int axis, const Vector3f& vec3)
    {
        
    }
    
    inline void Matrix4x4f::SetPosition( const Vector3f& vec3)
    {
        
    }
    
    inline void Matrix4x4f::SetRow( int row, const Vector4f& vec3)
    {
        
    }
    
    inline void Matrix4x4f::SetColumn( int col, const Vector4f& vec3)
    {
        
    }
    
    
    inline void Matrix4x4f::SetTR (const Vector3f& pos, const Quaternionf& q)
    {
        
    }
    
    inline void Matrix4x4f::SetTRS (const Vector3f& pos, const Quaternionf& q, const Vector3f& s)
    {
        
    }
    
    
    inline Vector3f Matrix4x4f::MultiplyVector3 (const Vector3f& inV) const
    {
        
    }
    
    inline Vector4f Matrix4x4f::MultiplyVector4 (const Vector4f& inV) const
    {
        
    }
    
    inline Vector3f Matrix4x4f::MultiplyPoint3 (const Vector3f& inV) const
    {
        
    }
    
    
    inline void Matrix4x4f::MultiplyVector3 (const Vector3f& inV, Vector3f& output) const
    {
        
    }
    
    inline void Matrix4x4f::MultiplyVector4 (const Vector4f& inV, Vector4f& output) const
    {
        
    }
    
    inline void Matrix4x4f::MultiplyPoint3 (const Vector3f& inV, Vector3f& output) const
    {
        
    }
    
    
    inline Matrix4x4f& Matrix4x4f::SetIdentity ()
    {
        
    }
    
    inline Matrix4x4f& Matrix4x4f::SetPerspective( float fovy, float aspect, float zNear, float zFar)
    {
        
    }
    
    inline Matrix4x4f& Matrix4x4f::SetPerspective( float left, float right, float top, float bottom, float zNear, float zFar)
    {
        
    }
    
    inline Matrix4x4f& Matrix4x4f::SetOrtho( float left, float right, float bottom, float top, float zNear, float zFar)
    {
        
    }
    
    inline Matrix4x4f& Matrix4x4f::SetFrustum( float left, float right, float bottom, float top, float nearval, float farval)
    {
        
    }
    
}

#endif
