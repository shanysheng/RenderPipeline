/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR3_H_GUARD
#define PIPELINE_VECTOR3_H_GUARD

#include "Common.h"

namespace pipeline{
    
    class Vector3f
    {
    public:
        float x,y,z;
        
        static const float epsilon;
        static const Vector3f xAxis;
        static const Vector3f yAxis;
        static const Vector3f one;
        static const Vector3f zero;
        
    public:
        Vector3f(float x, float y);
        Vector3f(const Vector3f& v);
        
        void Set(float inx, float iny);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        Vector3f operator+(const Vector3f& rhs) const;
        Vector3f operator-(const Vector3f& rhs) const;
        Vector3f operator*(const Vector3f& rhs) const;
        Vector3f operator/(const Vector3f& rhs) const;
        Vector3f operator*(float scale) const;
        Vector3f operator/(float scale) const;
        
        Vector3f& operator += (const Vector3f& rhs);
        Vector3f& operator -= (const Vector3f& rhs);
        Vector3f& operator *=(const Vector3f& rhs);
        Vector3f& operator /=(const Vector3f& rhs);
        Vector3f& operator *= (const float scale);
        Vector3f& operator /= (const float scale);
        
        Vector3f operator -() const;
        
        // dot product
        float operator|(const Vector3f& V) const;
        
        // cross product
        float operator^(const Vector3f& V) const;
        
        bool operator == (const Vector3f& rhs)const;
        bool operator != (const Vector3f& rhs)const;
        
        float Length() const;
        void Normalize();
        
        static float DotProduct(const Vector3f& lhs, const Vector3f& rhs);
        static float CrossProduct(const Vector3f& lhs, const Vector3f& rhs);
        static float DistSquared(const Vector3f& lhs, const Vector3f& rhs);
        static float Distance(const Vector3f& lhs, const Vector3f& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline Vector3f::Vector3f(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline Vector3f::Vector3f(const Vector3f& v)
    {
        this->x = v.x;
        this->y = v.y;
    }
    
    inline void Vector3f::Set(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline float* Vector3f::data() { return &x; }
    inline const float* Vector3f::data()const { return &x; }
    inline float& Vector3f::operator[](int i) { return (&x)[i]; }
    inline const float& Vector3f::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline Vector3f Vector3f::operator+(const Vector3f& rhs) const
    {
        return Vector3f(this->x+rhs.x, this->y+rhs.y);
    }
    
    inline Vector3f Vector3f::operator-(const Vector3f& rhs) const
    {
        return Vector3f(this->x-rhs.x, this->y-rhs.y);
    }
    
    inline Vector3f Vector3f::operator*(const Vector3f& rhs) const
    {
        return Vector3f(this->x*rhs.x, this->y*rhs.y);
    }
    
    inline Vector3f Vector3f::operator/(const Vector3f& rhs) const
    {
        return Vector3f(this->x/rhs.x, this->y/rhs.y);
    }
    
    inline Vector3f Vector3f::operator*(float scale) const
    {
        return Vector3f(x*scale, y*scale);
    }
    
    inline Vector3f Vector3f::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return Vector3f(x*tmp, y*tmp);
    }
    
    inline Vector3f& Vector3f::operator += (const Vector3f& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    inline Vector3f& Vector3f::operator -= (const Vector3f& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    
    inline Vector3f& Vector3f::operator *=(const Vector3f& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }
    
    inline Vector3f& Vector3f::operator /=(const Vector3f& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }
    
    inline Vector3f& Vector3f::operator *= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        return *this;
    }
    
    inline Vector3f& Vector3f::operator /= (const float scale)
    {
        x /= scale;
        y /= scale;
        return *this;
    }
    
    inline Vector3f Vector3f::operator -() const
    {
        return Vector3f(-x, -y);
    }
    
    inline float Vector3f::operator|(const Vector3f& rhs) const
    {
        return this->x*rhs.x + this->y*rhs.y;
    }
    
    inline float Vector3f::operator^(const Vector3f& rhs) const
    {
        return this->x*rhs.y - this->y*rhs.x;
    }
    
    inline bool Vector3f::operator == (const Vector3f& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }
    
    inline bool Vector3f::operator != (const Vector3f& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y;
    }
    
    inline float Vector3f::Length() const
    {
        return std::sqrt(x*x+y*y);
    }
    
    inline void Vector3f::Normalize()
    {
        float scale = 1.0f/Length();
        x *= scale;
        y *= scale;
    }
    
    inline float Vector3f::DotProduct(const Vector3f& lhs, const Vector3f& rhs)
    {
        return lhs | rhs;
    }
    
    inline float Vector3f::CrossProduct(const Vector3f& lhs, const Vector3f& rhs)
    {
        return lhs ^ rhs;
    }
    
    inline float Vector3f::DistSquared(const Vector3f& lhs, const Vector3f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.x-rhs.y;
        return offsetx*offsetx+offsety*offsety;
    }
    
    inline float Vector3f::Distance(const Vector3f& lhs, const Vector3f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.x-rhs.y;
        return std::sqrt(offsetx*offsetx+offsety*offsety);
    }
}

#endif
