/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR4_H_GUARD
#define PIPELINE_VECTOR4_H_GUARD

#include "Common.h"

namespace pipeline{
    
    
    class Vector4f
    {
    public:
        float x,y,z,w;
        
        static const float epsilon;
        static const Vector4f xAxis;
        static const Vector4f yAxis;
        static const Vector4f one;
        static const Vector4f zero;
        
    public:
        Vector4f();
        Vector4f(float inx, float iny, float inz, float inw);
        Vector4f(const Vector4f& v);
        
        void Set(float inx, float iny, float inz, float inw);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        Vector4f operator+(const Vector4f& rhs) const;
        Vector4f operator-(const Vector4f& rhs) const;
        Vector4f operator*(const Vector4f& rhs) const;
        Vector4f operator/(const Vector4f& rhs) const;
        Vector4f operator*(float scale) const;
        Vector4f operator/(float scale) const;
        
        Vector4f& operator += (const Vector4f& rhs);
        Vector4f& operator -= (const Vector4f& rhs);
        Vector4f& operator *=(const Vector4f& rhs);
        Vector4f& operator /=(const Vector4f& rhs);
        Vector4f& operator *= (const float scale);
        Vector4f& operator /= (const float scale);
        
        Vector4f operator -() const;
        
        // cross product
        Vector4f operator^(const Vector4f& rhs) const;
        
        bool operator == (const Vector4f& rhs)const;
        bool operator != (const Vector4f& rhs)const;
        
        float Length3() const;
        void Normalize();
        
        static float DotProduct3(const Vector4f& lhs, const Vector4f& rhs);
        static float DotProduct(const Vector4f& lhs, const Vector4f& rhs);
        static Vector4f CrossProduct(const Vector4f& lhs, const Vector4f& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline Vector4f::Vector4f()
    {
        
    }
    
    inline Vector4f::Vector4f(float inx, float iny, float inz, float inw)
    {
        this->x = inx;
        this->y = iny;
        this->z = inz;
        this->w = inw;
    }
    
    inline Vector4f::Vector4f(const Vector4f& v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = v.w;
    }
    
    inline void Vector4f::Set(float inx, float iny, float inz, float inw)
    {
        this->x = inx;
        this->y = iny;
        this->z = inz;
        this->w = inw;
    }
    
    inline float* Vector4f::data() { return &x; }
    inline const float* Vector4f::data()const { return &x; }
    inline float& Vector4f::operator[](int i) { return (&x)[i]; }
    inline const float& Vector4f::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline Vector4f Vector4f::operator+(const Vector4f& rhs) const
    {
        return Vector4f(this->x+rhs.x, this->y+rhs.y, this->z+rhs.z, this->w+rhs.w);
    }
    
    inline Vector4f Vector4f::operator-(const Vector4f& rhs) const
    {
        return Vector4f(this->x-rhs.x, this->y-rhs.y, this->z-rhs.z, this->w-rhs.w);
    }
    
    inline Vector4f Vector4f::operator*(const Vector4f& rhs) const
    {
        return Vector4f(this->x*rhs.x, this->y*rhs.y, this->x*rhs.z, this->w*rhs.w);
    }
    
    inline Vector4f Vector4f::operator/(const Vector4f& rhs) const
    {
        return Vector4f(this->x/rhs.x, this->y/rhs.y, this->z/rhs.z, this->w/rhs.w);
    }
    
    inline Vector4f Vector4f::operator*(float scale) const
    {
        return Vector4f(x*scale, y*scale, z*scale, w*scale);
    }
    
    inline Vector4f Vector4f::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return Vector4f(x*tmp, y*tmp, z*tmp, w*tmp);
    }
    
    inline Vector4f& Vector4f::operator += (const Vector4f& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        this->w += rhs.w;
        return *this;
    }
    
    inline Vector4f& Vector4f::operator -= (const Vector4f& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        this->w -= rhs.w;
        return *this;
    }
    
    inline Vector4f& Vector4f::operator *=(const Vector4f& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        this->w *= rhs.w;
        return *this;
    }
    
    inline Vector4f& Vector4f::operator /=(const Vector4f& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        this->z /= rhs.z;
        this->w /= rhs.w;
        return *this;
    }
    
    inline Vector4f& Vector4f::operator *= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        return *this;
    }
    
    inline Vector4f& Vector4f::operator /= (const float scale)
    {
        x /= scale;
        y /= scale;
        return *this;
    }
    
    inline Vector4f Vector4f::operator -() const
    {
        return Vector4f(-x, -y, -z, -w);
    }
    
    inline Vector4f Vector4f::operator^(const Vector4f& rhs) const
    {
        return Vector4f(
                        y * rhs.z - z * rhs.y,
                        z * rhs.x - x * rhs.z,
                        x * rhs.y - y * rhs.x,
                        0.0f
                       );
    }
    
    inline bool Vector4f::operator == (const Vector4f& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w;
    }
    
    inline bool Vector4f::operator != (const Vector4f& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y || this->z != rhs.z || this->w != rhs.w;
    }
    
    inline float Vector4f::Length3() const
    {
        return std::sqrt(x*x+y*y+z*z);
    }
    
    inline void Vector4f::Normalize()
    {
        float scale = 1.0f/Length3();
        x *= scale;
        y *= scale;
        z *= scale;
    }
    
    inline float Vector4f::DotProduct3(const Vector4f& lhs, const Vector4f& rhs)
    {
        return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z;
    }
    
    inline float Vector4f::DotProduct(const Vector4f& lhs, const Vector4f& rhs)
    {
        return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z+lhs.w*rhs.w;
    }
    
    inline Vector4f Vector4f::CrossProduct(const Vector4f& lhs, const Vector4f& rhs)
    {
        return lhs ^ rhs;
    }
    
}

#endif
