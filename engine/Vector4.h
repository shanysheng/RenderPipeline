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
        Vector4f(float x, float y);
        Vector4f(const Vector4f& v);
        
        void Set(float inx, float iny);
        
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
        
        // dot product
        float operator|(const Vector4f& V) const;
        
        // cross product
        float operator^(const Vector4f& V) const;
        
        bool operator == (const Vector4f& rhs)const;
        bool operator != (const Vector4f& rhs)const;
        
        float Length() const;
        void Normalize();
        
        static float DotProduct(const Vector4f& lhs, const Vector4f& rhs);
        static float CrossProduct(const Vector4f& lhs, const Vector4f& rhs);
        static float DistSquared(const Vector4f& lhs, const Vector4f& rhs);
        static float Distance(const Vector4f& lhs, const Vector4f& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline Vector4f::Vector4f(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline Vector4f::Vector4f(const Vector4f& v)
    {
        this->x = v.x;
        this->y = v.y;
    }
    
    inline void Vector4f::Set(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline float* Vector4f::data() { return &x; }
    inline const float* Vector4f::data()const { return &x; }
    inline float& Vector4f::operator[](int i) { return (&x)[i]; }
    inline const float& Vector4f::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline Vector4f Vector4f::operator+(const Vector4f& rhs) const
    {
        return Vector4f(this->x+rhs.x, this->y+rhs.y);
    }
    
    inline Vector4f Vector4f::operator-(const Vector4f& rhs) const
    {
        return Vector4f(this->x-rhs.x, this->y-rhs.y);
    }
    
    inline Vector4f Vector4f::operator*(const Vector4f& rhs) const
    {
        return Vector4f(this->x*rhs.x, this->y*rhs.y);
    }
    
    inline Vector4f Vector4f::operator/(const Vector4f& rhs) const
    {
        return Vector4f(this->x/rhs.x, this->y/rhs.y);
    }
    
    inline Vector4f Vector4f::operator*(float scale) const
    {
        return Vector4f(x*scale, y*scale);
    }
    
    inline Vector4f Vector4f::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return Vector4f(x*tmp, y*tmp);
    }
    
    inline Vector4f& Vector4f::operator += (const Vector4f& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    inline Vector4f& Vector4f::operator -= (const Vector4f& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    
    inline Vector4f& Vector4f::operator *=(const Vector4f& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }
    
    inline Vector4f& Vector4f::operator /=(const Vector4f& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
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
        return Vector4f(-x, -y);
    }
    
    inline float Vector4f::operator|(const Vector4f& rhs) const
    {
        return this->x*rhs.x + this->y*rhs.y;
    }
    
    inline float Vector4f::operator^(const Vector4f& rhs) const
    {
        return this->x*rhs.y - this->y*rhs.x;
    }
    
    inline bool Vector4f::operator == (const Vector4f& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }
    
    inline bool Vector4f::operator != (const Vector4f& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y;
    }
    
    inline float Vector4f::Length() const
    {
        return std::sqrt(x*x+y*y);
    }
    
    inline void Vector4f::Normalize()
    {
        float scale = 1.0f/Length();
        x *= scale;
        y *= scale;
    }
    
    inline float Vector4f::DotProduct(const Vector4f& lhs, const Vector4f& rhs)
    {
        return lhs | rhs;
    }
    
    inline float Vector4f::CrossProduct(const Vector4f& lhs, const Vector4f& rhs)
    {
        return lhs ^ rhs;
    }
    
    inline float Vector4f::DistSquared(const Vector4f& lhs, const Vector4f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.x-rhs.y;
        return offsetx*offsetx+offsety*offsety;
    }
    
    inline float Vector4f::Distance(const Vector4f& lhs, const Vector4f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.x-rhs.y;
        return std::sqrt(offsetx*offsetx+offsety*offsety);
    }
}

#endif
