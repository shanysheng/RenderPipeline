/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_QUATERNION_H_GUARD
#define PIPELINE_QUATERNION_H_GUARD

#include "Common.h"
#include "Vector3.h"

namespace pipeline{
    
    class Matrix4x4f;

    class Quaternionf
    {
    public:
        float x,y,z,w;
        
    public:
        Quaternionf () ;
        Quaternionf (float inX, float inY, float inZ, float inW);
        //Quaternionf& operator=(const Quaternionf& Other);
        void Set (float inX, float inY, float inZ, float inW);
        void Set (const Quaternionf& aQuat);
  /*
        Quaternionf operator+(const Quaternionf& rhs) const;
        Quaternionf operator+=(const Quaternionf& rhs);
        Quaternionf operator-(const Quaternionf& rhs) const;
        bool IsIdentity(float tolerance) const;
        Quaternionf operator-=(const Quaternionf& rhs);
        Quaternionf operator*(const Quaternionf& rhs) const;
        Quaternionf operator*=(const Quaternionf& rhs);
        Vector3f operator*(const Vector3f& vec) const;
        Matrix4x4f operator*(const Matrix4x4f& mat) const;
        Quaternionf operator*=(const float scale);
        Quaternionf operator*(const float scale) const;
        Quaternionf operator/=(const float scale);
        Quaternionf operator/(const float scale) const;
        bool operator==(const Quaternionf& rhs) const;
        bool operator!=(const Quaternionf& rhs) const;
        
        void Normalize();
        void Inverse ();
        */
        //static Quaternionf identity ();
        //static Quaternionf Normalize(const Quaternionf& q);
        //static Quaternionf Inverse (const Quaternionf& q);
        //static Vector3f QuaternionToEuler (const Quaternionf& quat);
        //static Quaternionf EulerToQuaternion (const Vector3f& euler);
        //static void QuaternionToMatrix (const Quaternionf& q, Matrix4x4f& m);
        //static void MatrixToQuaternion (const Matrix4x4f& m, Quaternionf& q);
    };
    
    inline Quaternionf::Quaternionf ()
    {
        
    }
    
    inline Quaternionf::Quaternionf (float inX, float inY, float inZ, float inW)
    {
        
    }
    
    //inline Quaternionf::Quaternionf& operator=(const Quaternionf& Other)
    //{
    //    
    //}
    
    inline void Quaternionf::Set (float inX, float inY, float inZ, float inW)
    {
        
    }
    
    inline void Quaternionf::Set (const Quaternionf& aQuat)
    {
        
    }
    //
    //
    //inline Quaternionf Quaternionf::operator+(const Quaternionf& rhs) const
    //{
    //    
    //}
    //
    //inline Quaternionf Quaternionf::operator+=(const Quaternionf& rhs)
    //{
    //    
    //}
    //
    //inline Quaternionf Quaternionf::operator-(const Quaternionf& rhs) const
    //{
    //    
    //}
    //
    ////inline bool Quaternionf::Equals(const Quaternionf& rhs) const
    ////{
    ////    
    ////}
    //
    //inline bool Quaternionf::IsIdentity(float tolerance) const
    //{
    //    
    //}
    //
    //inline Quaternionf Quaternionf::operator-=(const Quaternionf& rhs)
    //{
    //    
    //}
    //
    //inline Quaternionf Quaternionf::operator*(const Quaternionf& rhs) const
    //{
    //    
    //}
    //
    //inline Quaternionf Quaternionf::operator*=(const Quaternionf& rhs)
    //{
    //    
    //}
    //
    //inline Vector3f Quaternionf::operator*(const Vector3f& vec) const
    //{
    //    
    //}
    //
    //inline Matrix4x4f Quaternionf::operator*(const Matrix4x4f& mat) const
    //{
    //    
    //}
    //
    //inline Quaternionf Quaternionf::operator*=(const float scale)
    //{
    //    
    //}
    //
    //inline Quaternionf Quaternionf::operator*(const float scale) const
    //{
    //    
    //}
    //
    //inline Quaternionf Quaternionf::operator/=(const float scale)
    //{
    //    
    //}
    //
    //inline Quaternionf Quaternionf::operator/(const float scale) const
    //{
    //    
    //}
    //
    //inline bool Quaternionf::operator==(const Quaternionf& rhs) const
    //{
    //    
    //}
    //
    //inline bool Quaternionf::operator!=(const Quaternionf& rhs) const
    //{
    //    
    //}
    //
    //
    //inline void Quaternionf::Normalize()
    //{
    //    
    //}
    //
    //inline void Quaternionf::Inverse ()
    //{
    //    
    //}
    ///*
    //
    //inline static Quaternionf Quaternionf::identity ()
    //{
    //    
    //}
    //
    //inline static Quaternionf Quaternionf::Normalize(const Quaternionf& q)
    //{
    //    
    //}
    //
    //inline static Quaternionf Quaternionf::Inverse (const Quaternionf& q)
    //{
    //    
    //}
    //
    //inline static Vector3f Quaternionf::QuaternionToEuler (const Quaternionf& quat)
    //{
    //    
    //}
    //
    //inline static Quaternionf Quaternionf::EulerToQuaternion (const Vector3f& euler)
    //{
    //    
    //}
    //
    //inline static void Quaternionf::QuaternionToMatrix (const Quaternionf& q, Matrix4x4f& m)
    //{
    //    
    //}
    //
    //inline static void Quaternionf::MatrixToQuaternion (const Matrix4x4f& m, Quaternionf& q)
    //{
    //    
    //}*/
    //
}
#endif
