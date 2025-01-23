#ifndef PIPELINE_QUATERNION_H_GUARD
#define PIPELINE_QUATERNION_H_GUARD

#include "Common.h"
#include "Vector3.h"

namespace pipeline{
    
    class kMatrix4x4f;

    class kQuaternionf
    {
    public:
        float x,y,z,w;
        
    public:
        kQuaternionf () ;
        kQuaternionf (float inX, float inY, float inZ, float inW);
        //kQuaternionf& operator=(const kQuaternionf& Other);
        void Set (float inX, float inY, float inZ, float inW);
        void Set (const kQuaternionf& aQuat);
  /*
        kQuaternionf operator+(const kQuaternionf& rhs) const;
        kQuaternionf operator+=(const kQuaternionf& rhs);
        kQuaternionf operator-(const kQuaternionf& rhs) const;
        bool IsIdentity(float tolerance) const;
        kQuaternionf operator-=(const kQuaternionf& rhs);
        kQuaternionf operator*(const kQuaternionf& rhs) const;
        kQuaternionf operator*=(const kQuaternionf& rhs);
        kVector3f operator*(const kVector3f& vec) const;
        kMatrix4x4f operator*(const kMatrix4x4f& mat) const;
        kQuaternionf operator*=(const float scale);
        kQuaternionf operator*(const float scale) const;
        kQuaternionf operator/=(const float scale);
        kQuaternionf operator/(const float scale) const;
        bool operator==(const kQuaternionf& rhs) const;
        bool operator!=(const kQuaternionf& rhs) const;
        
        void Normalize();
        void Inverse ();
        */
        //static kQuaternionf identity ();
        //static kQuaternionf Normalize(const kQuaternionf& q);
        //static kQuaternionf Inverse (const kQuaternionf& q);
        //static kVector3f QuaternionToEuler (const kQuaternionf& quat);
        //static kQuaternionf EulerToQuaternion (const kVector3f& euler);
        //static void QuaternionToMatrix (const kQuaternionf& q, kMatrix4x4f& m);
        //static void MatrixToQuaternion (const kMatrix4x4f& m, kQuaternionf& q);
    };
    
    inline kQuaternionf::kQuaternionf ()
    {
        
    }
    
    inline kQuaternionf::kQuaternionf (float inX, float inY, float inZ, float inW)
    {
        
    }
    
    //inline kQuaternionf::kQuaternionf& operator=(const kQuaternionf& Other)
    //{
    //    
    //}
    
    inline void kQuaternionf::Set (float inX, float inY, float inZ, float inW)
    {
        
    }
    
    inline void kQuaternionf::Set (const kQuaternionf& aQuat)
    {
        
    }
    //
    //
    //inline kQuaternionf kQuaternionf::operator+(const kQuaternionf& rhs) const
    //{
    //    
    //}
    //
    //inline kQuaternionf kQuaternionf::operator+=(const kQuaternionf& rhs)
    //{
    //    
    //}
    //
    //inline kQuaternionf kQuaternionf::operator-(const kQuaternionf& rhs) const
    //{
    //    
    //}
    //
    ////inline bool kQuaternionf::Equals(const kQuaternionf& rhs) const
    ////{
    ////    
    ////}
    //
    //inline bool kQuaternionf::IsIdentity(float tolerance) const
    //{
    //    
    //}
    //
    //inline kQuaternionf kQuaternionf::operator-=(const kQuaternionf& rhs)
    //{
    //    
    //}
    //
    //inline kQuaternionf kQuaternionf::operator*(const kQuaternionf& rhs) const
    //{
    //    
    //}
    //
    //inline kQuaternionf kQuaternionf::operator*=(const kQuaternionf& rhs)
    //{
    //    
    //}
    //
    //inline kVector3f kQuaternionf::operator*(const kVector3f& vec) const
    //{
    //    
    //}
    //
    //inline kMatrix4x4f kQuaternionf::operator*(const kMatrix4x4f& mat) const
    //{
    //    
    //}
    //
    //inline kQuaternionf kQuaternionf::operator*=(const float scale)
    //{
    //    
    //}
    //
    //inline kQuaternionf kQuaternionf::operator*(const float scale) const
    //{
    //    
    //}
    //
    //inline kQuaternionf kQuaternionf::operator/=(const float scale)
    //{
    //    
    //}
    //
    //inline kQuaternionf kQuaternionf::operator/(const float scale) const
    //{
    //    
    //}
    //
    //inline bool kQuaternionf::operator==(const kQuaternionf& rhs) const
    //{
    //    
    //}
    //
    //inline bool kQuaternionf::operator!=(const kQuaternionf& rhs) const
    //{
    //    
    //}
    //
    //
    //inline void kQuaternionf::Normalize()
    //{
    //    
    //}
    //
    //inline void kQuaternionf::Inverse ()
    //{
    //    
    //}
    ///*
    //
    //inline static kQuaternionf kQuaternionf::identity ()
    //{
    //    
    //}
    //
    //inline static kQuaternionf kQuaternionf::Normalize(const kQuaternionf& q)
    //{
    //    
    //}
    //
    //inline static kQuaternionf kQuaternionf::Inverse (const kQuaternionf& q)
    //{
    //    
    //}
    //
    //inline static kVector3f kQuaternionf::QuaternionToEuler (const kQuaternionf& quat)
    //{
    //    
    //}
    //
    //inline static kQuaternionf kQuaternionf::EulerToQuaternion (const kVector3f& euler)
    //{
    //    
    //}
    //
    //inline static void kQuaternionf::QuaternionToMatrix (const kQuaternionf& q, kMatrix4x4f& m)
    //{
    //    
    //}
    //
    //inline static void kQuaternionf::MatrixToQuaternion (const kMatrix4x4f& m, kQuaternionf& q)
    //{
    //    
    //}*/
    //
}
#endif
