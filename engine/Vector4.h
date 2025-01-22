/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR4_H_GUARD
#define PIPELINE_VECTOR4_H_GUARD

#include "Common.h"

namespace pipeline{
    
    
    class kVector4f
    {
    public:
        float x,y,z,w;
        
        static const float epsilon;
        static const kVector4f xAxis;
        static const kVector4f yAxis;
        static const kVector4f one;
        static const kVector4f zero;
        
    public:
        kVector4f();
        kVector4f(float inx, float iny, float inz, float inw);
        kVector4f(const kVector4f& v);
        
        void Set(float inx, float iny, float inz, float inw);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        kVector4f operator+(const kVector4f& rhs) const;
        kVector4f operator-(const kVector4f& rhs) const;
        kVector4f operator*(const kVector4f& rhs) const;
        kVector4f operator/(const kVector4f& rhs) const;
        kVector4f operator*(float scale) const;
        kVector4f operator/(float scale) const;
        
        kVector4f& operator += (const kVector4f& rhs);
        kVector4f& operator -= (const kVector4f& rhs);
        kVector4f& operator *=(const kVector4f& rhs);
        kVector4f& operator /=(const kVector4f& rhs);
        kVector4f& operator *= (const float scale);
        kVector4f& operator /= (const float scale);
        
        kVector4f operator -() const;
        
        // cross product
        kVector4f operator^(const kVector4f& rhs) const;
        
        bool operator == (const kVector4f& rhs)const;
        bool operator != (const kVector4f& rhs)const;
        
        float Length3() const;
        void Normalize();
        
        static float DotProduct3(const kVector4f& lhs, const kVector4f& rhs);
        static float DotProduct(const kVector4f& lhs, const kVector4f& rhs);
        static kVector4f CrossProduct(const kVector4f& lhs, const kVector4f& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline kVector4f::kVector4f()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
        this->w = 0.0f;
    }
    
    inline kVector4f::kVector4f(float inx, float iny, float inz, float inw)
    {
        this->x = inx;
        this->y = iny;
        this->z = inz;
        this->w = inw;
    }
    
    inline kVector4f::kVector4f(const kVector4f& v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = v.w;
    }
    
    inline void kVector4f::Set(float inx, float iny, float inz, float inw)
    {
        this->x = inx;
        this->y = iny;
        this->z = inz;
        this->w = inw;
    }
    
    inline float* kVector4f::data() { return &x; }
    inline const float* kVector4f::data()const { return &x; }
    inline float& kVector4f::operator[](int i) { return (&x)[i]; }
    inline const float& kVector4f::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline kVector4f kVector4f::operator+(const kVector4f& rhs) const
    {
        return kVector4f(this->x+rhs.x, this->y+rhs.y, this->z+rhs.z, this->w+rhs.w);
    }
    
    inline kVector4f kVector4f::operator-(const kVector4f& rhs) const
    {
        return kVector4f(this->x-rhs.x, this->y-rhs.y, this->z-rhs.z, this->w-rhs.w);
    }
    
    inline kVector4f kVector4f::operator*(const kVector4f& rhs) const
    {
        return kVector4f(this->x*rhs.x, this->y*rhs.y, this->x*rhs.z, this->w*rhs.w);
    }
    
    inline kVector4f kVector4f::operator/(const kVector4f& rhs) const
    {
        return kVector4f(this->x/rhs.x, this->y/rhs.y, this->z/rhs.z, this->w/rhs.w);
    }
    
    inline kVector4f kVector4f::operator*(float scale) const
    {
        return kVector4f(x*scale, y*scale, z*scale, w*scale);
    }
    
    inline kVector4f kVector4f::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return kVector4f(x*tmp, y*tmp, z*tmp, w*tmp);
    }
    
    inline kVector4f& kVector4f::operator += (const kVector4f& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        this->w += rhs.w;
        return *this;
    }
    
    inline kVector4f& kVector4f::operator -= (const kVector4f& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        this->w -= rhs.w;
        return *this;
    }
    
    inline kVector4f& kVector4f::operator *=(const kVector4f& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        this->w *= rhs.w;
        return *this;
    }
    
    inline kVector4f& kVector4f::operator /=(const kVector4f& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        this->z /= rhs.z;
        this->w /= rhs.w;
        return *this;
    }
    
    inline kVector4f& kVector4f::operator *= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        return *this;
    }
    
    inline kVector4f& kVector4f::operator /= (const float scale)
    {
        x /= scale;
        y /= scale;
        return *this;
    }
    
    inline kVector4f kVector4f::operator -() const
    {
        return kVector4f(-x, -y, -z, -w);
    }
    
    inline kVector4f kVector4f::operator^(const kVector4f& rhs) const
    {
        return kVector4f(
                        y * rhs.z - z * rhs.y,
                        z * rhs.x - x * rhs.z,
                        x * rhs.y - y * rhs.x,
                        0.0f
                       );
    }
    
    inline bool kVector4f::operator == (const kVector4f& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w;
    }
    
    inline bool kVector4f::operator != (const kVector4f& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y || this->z != rhs.z || this->w != rhs.w;
    }
    
    inline float kVector4f::Length3() const
    {
        return std::sqrt(x*x+y*y+z*z);
    }
    
    inline void kVector4f::Normalize()
    {
        float scale = 1.0f/Length3();
        x *= scale;
        y *= scale;
        z *= scale;
    }
    
    inline float kVector4f::DotProduct3(const kVector4f& lhs, const kVector4f& rhs)
    {
        return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z;
    }
    
    inline float kVector4f::DotProduct(const kVector4f& lhs, const kVector4f& rhs)
    {
        return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z+lhs.w*rhs.w;
    }
    
    inline kVector4f kVector4f::CrossProduct(const kVector4f& lhs, const kVector4f& rhs)
    {
        return lhs ^ rhs;
    }
    
}

#endif
