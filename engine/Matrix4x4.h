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
#include "Mathf.h"

namespace pipeline{
    
    // Matrix elements are accessed with m[row][column].
    class kMatrix4x4f
    {
    public:
        float m[16];
        
        static const kMatrix4x4f identity;

    public:
        kMatrix4x4f();
        kMatrix4x4f(const kMatrix4x4f& rhs);
        
        float& Get (int row, int column);
        const float& Get (int row, int column)const;
        float* GetPtr ();
        const float* GetPtr ()const;
        
        kVector3f GetAxisX() const;
        kVector3f GetAxisY() const;
        kVector3f GetAxisZ() const;
        kVector3f GetAxis(int axis) const;
        kVector3f GetPosition() const;
        kVector4f GetRow(int row) const;
        kVector4f GetColumn(int col) const;
        
        void SetAxisX( const kVector3f& vec3);
        void SetAxisY( const kVector3f& vec3);
        void SetAxisZ( const kVector3f& vec3);
        void SetAxis( int axis, const kVector3f& vec3);
        void SetPosition( const kVector3f& vec3);
        void SetRow( int row, const kVector4f& vec3);
        void SetColumn( int col, const kVector4f& vec3);
        

        kMatrix4x4f operator+ (const kMatrix4x4f& rhs) const;
        void operator+=(const kMatrix4x4f& rhs);
        kMatrix4x4f operator* (float scale) const;
        void operator*=(float scale);
        bool operator==(const kMatrix4x4f& rhs) const;
        bool Equals(const kMatrix4x4f& rhs, float tolerance) const;
        bool operator!=(const kMatrix4x4f& rhs) const;
        
        kMatrix4x4f GetTransposed() const;
        float Determinant() const;
        kMatrix4x4f Inverse() const;

        void SetTR (const kVector3f& pos, const kQuaternionf& q);
        void SetTRS (const kVector3f& pos, const kQuaternionf& q, const kVector3f& s);
        
        kVector3f MultiplyVector3 (const kVector3f& inV) const;
        kVector4f MultiplyVector4 (const kVector4f& inV) const;
        kVector3f MultiplyPoint3 (const kVector3f& inV) const;

        void MultiplyVector3 (const kVector3f& inV, kVector3f& output) const;
        void MultiplyVector4 (const kVector4f& inV, kVector4f& output) const;
        void MultiplyPoint3 (const kVector3f& inV, kVector3f& output) const;
        
        kMatrix4x4f& SetIdentity ();
        kMatrix4x4f& SetPerspective( float fovy, float aspect, float zNear, float zFar);
        kMatrix4x4f& SetOrtho( float left, float right, float bottom, float top, float zNear, float zFar);
        kMatrix4x4f& SetFrustum( float left, float right, float bottom, float top, float nearval, float farval);
    };
    
    inline kMatrix4x4f::kMatrix4x4f()
    {
        
    }
    
    inline kMatrix4x4f::kMatrix4x4f(const kMatrix4x4f& rhs)
    {
        
    }
    
    inline float& kMatrix4x4f::Get (int row, int column)
    {
        return m[row + (column*4)];
    }
    
    inline const float& kMatrix4x4f::Get (int row, int column)const
    {
        return m[row + (column*4)];
    }
    
    inline float* kMatrix4x4f::GetPtr ()
    {
        return m;
    }
    
    inline const float* kMatrix4x4f::GetPtr ()const
    {
        return m;
    }
    
    inline kVector3f kMatrix4x4f::GetAxisX() const
    {
        return kVector3f( Get(0,0), Get(1,0), Get(2,0) );
    }
    
    inline kVector3f kMatrix4x4f::GetAxisY() const
    {
        return kVector3f( Get(0,1), Get(1,1), Get(2,1) );
    }
    
    inline kVector3f kMatrix4x4f::GetAxisZ() const
    {
        return kVector3f( Get(0,2), Get(1,2), Get(2,2) );
    }
    
    inline kVector3f kMatrix4x4f::GetAxis(int axis) const
    {
        return kVector3f( Get(0,axis), Get(1,axis), Get(2,axis) );
    }
    
    inline kVector3f kMatrix4x4f::GetPosition() const
    {
        return kVector3f( Get(0,3), Get(1,3), Get(2,3) );
    }
    
    inline kVector4f kMatrix4x4f::GetRow(int row) const
    {
        return kVector4f( Get(row,0), Get(row,1), Get(row,2), Get(row,3) );
    }
    
    inline kVector4f kMatrix4x4f::GetColumn(int col) const
    {
        return kVector4f( Get(0,col), Get(1,col), Get(2,col), Get(3,col) );
    }
    
    inline void kMatrix4x4f::SetAxisX( const kVector3f& v )
    {
        Get(0,0) = v.x;
        Get(1,0) = v.y;
        Get(2,0) = v.z;
    }
    
    inline void kMatrix4x4f::SetAxisY( const kVector3f& v )
    {
        Get(0,1) = v.x;
        Get(1,1) = v.y;
        Get(2,1) = v.z;
    }
    
    inline void kMatrix4x4f::SetAxisZ( const kVector3f& v )
    {
        Get(0,2) = v.x;
        Get(1,2) = v.y;
        Get(2,2) = v.z;
    }
    
    inline void kMatrix4x4f::SetAxis( int axis, const kVector3f& v )
    {
        Get(0,axis) = v.x;
        Get(1,axis) = v.y;
        Get(2,axis) = v.z;
    }
    
    inline void kMatrix4x4f::SetPosition( const kVector3f& v )
    {
        Get(0,3) = v.x;
        Get(1,3) = v.y;
        Get(2,3) = v.z;
    }
    
    inline void kMatrix4x4f::SetRow( int row, const kVector4f& v )
    {
        Get(row,0) = v.x;
        Get(row,1) = v.y;
        Get(row,2) = v.z;
        Get(row,3) = v.w;
    }
    
    inline void kMatrix4x4f::SetColumn( int col, const kVector4f& v )
    {
        Get(0,col) = v.x;
        Get(1,col) = v.y;
        Get(2,col) = v.z;
        Get(3,col) = v.w;
    }
    
    inline kMatrix4x4f kMatrix4x4f::operator+ (const kMatrix4x4f& rhs) const
    {
        kMatrix4x4f ResultMat;
        
        for(int32_t X = 0;X < 4;X++)
        {
            ResultMat.m[X] = m[X]+rhs.m[X];
        }
        
        return ResultMat;
    }
    
    inline void kMatrix4x4f::operator+=(const kMatrix4x4f& rhs)
    {
        *this = *this + rhs;
    }
    
    inline kMatrix4x4f kMatrix4x4f::operator* (float scale) const
    {
        kMatrix4x4f ResultMat;
        for(int32_t X = 0;X < 16;X++)
        {
            ResultMat.m[X] = m[X]*scale;
        }
        
        return ResultMat;
    }
    
    inline void kMatrix4x4f::operator*=(float scale)
    {
        *this = *this*scale;
    }
    
    inline bool kMatrix4x4f::operator==(const kMatrix4x4f& rhs) const
    {
        for(int32_t X = 0;X < 16;X++)
        {
            if(m[X] != rhs.m[X])
            {
                return false;
            }
        }
        
        return true;
    }

    
    inline bool kMatrix4x4f::operator!=(const kMatrix4x4f& rhs) const
    {
        return !(*this == rhs);
    }
    
    inline kMatrix4x4f kMatrix4x4f::GetTransposed() const
    {
        
    }
    
    inline float kMatrix4x4f::Determinant() const
    {
        
    }
    
    inline kMatrix4x4f kMatrix4x4f::Inverse() const
    {
        
    }
    
    inline void kMatrix4x4f::SetTR (const kVector3f& pos, const kQuaternionf& q)
    {
        
    }
    
    inline void kMatrix4x4f::SetTRS (const kVector3f& pos, const kQuaternionf& q, const kVector3f& s)
    {
        
    }
    
    
    inline kVector3f kMatrix4x4f::MultiplyVector3 (const kVector3f& inV) const
    {
        kVector3f res;
        res.x = m[0] * inV.x + m[4] * inV.y + m[ 8] * inV.z;
        res.y = m[1] * inV.x + m[5] * inV.y + m[ 9] * inV.z;
        res.z = m[2] * inV.x + m[6] * inV.y + m[10] * inV.z;
        return res;
    }
    
    inline kVector4f kMatrix4x4f::MultiplyVector4 (const kVector4f& inV) const
    {
        kVector4f res;
        MultiplyVector4(inV, res);
        return res;
    }
    
    inline kVector3f kMatrix4x4f::MultiplyPoint3 (const kVector3f& inV) const
    {
        kVector3f res;
        res.x = m[0] * inV.x + m[4] * inV.y + m[ 8] * inV.z + m[12];
        res.y = m[1] * inV.x + m[5] * inV.y + m[ 9] * inV.z + m[13];
        res.z = m[2] * inV.x + m[6] * inV.y + m[10] * inV.z + m[14];
        return res;
    }
    
    
    inline void kMatrix4x4f::MultiplyVector3 (const kVector3f& inV, kVector3f& output) const
    {
        output.x = m[0] * inV.x + m[4] * inV.y + m[ 8] * inV.z;
        output.y = m[1] * inV.x + m[5] * inV.y + m[ 9] * inV.z;
        output.z = m[2] * inV.x + m[6] * inV.y + m[10] * inV.z;
    }
    
    inline void kMatrix4x4f::MultiplyVector4 (const kVector4f& inV, kVector4f& output) const
    {
        output.x = m[0] * inV.x + m[4] * inV.y + m[ 8] * inV.z + m[12] * inV.w;
        output.y = m[1] * inV.x + m[5] * inV.y + m[ 9] * inV.z + m[13] * inV.w;
        output.z = m[2] * inV.x + m[6] * inV.y + m[10] * inV.z + m[14] * inV.w;
        output.w = m[3] * inV.x + m[7] * inV.y + m[11] * inV.z + m[15] * inV.w;
    }
    
    inline void kMatrix4x4f::MultiplyPoint3 (const kVector3f& inV, kVector3f& output) const
    {
        output.x = m[0] * inV.x + m[4] * inV.y + m[ 8] * inV.z + m[12];
        output.y = m[1] * inV.x + m[5] * inV.y + m[ 9] * inV.z + m[13];
        output.z = m[2] * inV.x + m[6] * inV.y + m[10] * inV.z + m[14];
    }
    
    
    inline kMatrix4x4f& kMatrix4x4f::SetIdentity ()
    {
        Get (0, 0) = 1.0;    Get (0, 1) = 0.0;    Get (0, 2) = 0.0;    Get (0, 3) = 0.0;
        Get (1, 0) = 0.0;    Get (1, 1) = 1.0;    Get (1, 2) = 0.0;    Get (1, 3) = 0.0;
        Get (2, 0) = 0.0;    Get (2, 1) = 0.0;    Get (2, 2) = 1.0;    Get (2, 3) = 0.0;
        Get (3, 0) = 0.0;    Get (3, 1) = 0.0;    Get (3, 2) = 0.0;    Get (3, 3) = 1.0;
        return *this;
    }
    
    inline kMatrix4x4f& kMatrix4x4f::SetPerspective( float fovy, float aspect, float zNear, float zFar)
    {
        float cotangent, deltaZ;
        float radians = kMathf::Deg2Rad (fovy / 2.0f);
        cotangent = cos (radians) / sin (radians);
        deltaZ = zNear - zFar;
        
        Get (0,0) = cotangent / aspect;    Get (0,1) = 0.0F;      Get (0,2) = 0.0F;                    Get (0,3) = 0.0F;
        Get (1,0) = 0.0F;               Get (1,1) = cotangent; Get (1,2) = 0.0F;                    Get (1,3) = 0.0F;
        Get (2,0) = 0.0F;               Get (2,1) = 0.0F;      Get (2,2) = (zFar + zNear) / deltaZ; Get (2,3) = 2.0F * zNear * zFar / deltaZ;
        Get (3,0) = 0.0F;               Get (3,1) = 0.0F;      Get (3,2) = -1.0F;                   Get (3,3) = 0.0F;
        
        return *this;
    }
    
    inline kMatrix4x4f& kMatrix4x4f::SetOrtho( float left, float right, float bottom, float top, float zNear, float zFar)
    {
        SetIdentity ();
        
        float deltax = right - left;
        float deltay = top - bottom;
        float deltaz = zFar - zNear;
        
        Get(0,0) = 2.0F / deltax;
        Get(0,3) = -(right + left) / deltax;
        Get(1,1) = 2.0F / deltay;
        Get(1,3) = -(top + bottom) / deltay;
        Get(2,2) = -2.0F / deltaz;
        Get(2,3) = -(zFar + zNear) / deltaz;
        return *this;
    }
    
    inline kMatrix4x4f& kMatrix4x4f::SetFrustum( float left, float right, float bottom, float top, float nearval, float farval)
    {
        float x, y, a, b, c, d, e;
        
        x =  (2.0F * nearval)        / (right - left);
        y =  (2.0F * nearval)        / (top - bottom);
        a =  (right + left)            / (right - left);
        b =  (top + bottom)            / (top - bottom);
        c = -(farval + nearval)           / (farval - nearval);
        d = -(2.0f * farval * nearval) / (farval - nearval);
        e = -1.0f;
        
        Get (0,0) = x;    Get (0,1) = 0.0;  Get (0,2) = a;   Get (0,3) = 0.0;
        Get (1,0) = 0.0;  Get (1,1) = y;    Get (1,2) = b;   Get (1,3) = 0.0;
        Get (2,0) = 0.0;  Get (2,1) = 0.0;  Get (2,2) = c;   Get (2,3) = d;
        Get (3,0) = 0.0;  Get (3,1) = 0.0;  Get (3,2) = e;    Get (3,3) = 0.0;
        return *this;
    }
    
}

#endif
