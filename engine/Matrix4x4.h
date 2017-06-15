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
        void SetAxisX( const Vector3f& v );
        void SetAxisY( const Vector3f& v );
        void SetAxisZ( const Vector3f& v );
        void SetAxis( int axis, const Vector3f& v );
        void SetPosition( const Vector3f& v );
        void SetRow( int row, const Vector4f& v );
        void SetColumn( int col, const Vector4f& v );
        
        void SetTR (const Vector3f& pos, const Quaternionf& q);
        void SetTRS (const Vector3f& pos, const Quaternionf& q, const Vector3f& s);
        
        Vector3f MultiplyVector3 (const Vector3f& inV) const;
        void MultiplyVector3 (const Vector3f& inV, Vector3f& output) const;
        Vector4f MultiplyVector4 (const Vector4f& inV) const;
        void MultiplyVector4 (const Vector4f& inV, Vector4f& output) const;
        Vector3f MultiplyPoint3 (const Vector3f& inV) const;
        void MultiplyPoint3 (const Vector3f& inV, Vector3f& output) const;
        
        Matrix4x4f& SetIdentity ();
        Matrix4x4f& SetPerspective( float fovy, float aspect, float zNear, float zFar );
        Matrix4x4f& SetPerspective( float left, float right, float top, float bottom, float zNear, float zFar );
        // rad = Deg2Rad(fovy/2), contanHalfFOV = cos(rad)/sin(rad)
        Matrix4x4f& SetPerspectiveCotan( float cotanHalfFOV, float zNear, float zFar );
        Matrix4x4f& SetOrtho( float left, float right, float bottom, float top, float zNear, float zFar );
        Matrix4x4f& SetFrustum( float left, float right, float bottom, float top, float nearval, float farval );
    };
}

#endif
