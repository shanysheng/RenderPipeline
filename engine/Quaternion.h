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
        Quaternionf& operator=(const Quaternionf& Other);
        void Set (float inX, float inY, float inZ, float inW);
        void Set (const Quaternionf& aQuat);
  
        Quaternionf operator+(const Quaternionf& rhs) const;
        Quaternionf operator+=(const Quaternionf& rhs);
        Quaternionf operator-(const Quaternionf& rhs) const;
        bool Equals(const Quaternionf& rhs) const;
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
        
        static Quaternionf identity ();
        static Quaternionf Normalize(const Quaternionf& q);
        static Quaternionf Inverse (const Quaternionf& q);
        static Vector3f QuaternionToEuler (const Quaternionf& quat);
        static Quaternionf EulerToQuaternion (const Vector3f& euler);
        static void QuaternionToMatrix (const Quaternionf& q, Matrix4x4f& m);
        static void MatrixToQuaternion (const Matrix4x4f& m, Quaternionf& q);
    };
    
    

}
#endif
