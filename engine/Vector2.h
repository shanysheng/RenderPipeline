/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR2_H_GUARD
#define PIPELINE_VECTOR2_H_GUARD

#include "Common.h"

namespace pipeline{
    
    class Vector2f
    {
    public:
        float x,y;
        
        static const float epsilon;
        static const Vector2f xAxis;
        static const Vector2f yAxis;
        static const Vector2f one;
        static const Vector2f zero;

    public:
        Vector2f();
        Vector2f(float inx, float iny);
        Vector2f(const Vector2f& v);
        
        void Set(float inx, float iny);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        Vector2f operator+(const Vector2f& rhs) const;
        Vector2f operator-(const Vector2f& rhs) const;
        Vector2f operator*(const Vector2f& rhs) const;
        Vector2f operator/(const Vector2f& rhs) const;
        Vector2f operator*(float scale) const;
        Vector2f operator/(float scale) const;
        
        Vector2f& operator += (const Vector2f& rhs);
        Vector2f& operator -= (const Vector2f& rhs);
        Vector2f& operator *=(const Vector2f& rhs);
        Vector2f& operator /=(const Vector2f& rhs);
        Vector2f& operator *= (const float scale);
        Vector2f& operator /= (const float scale);
        
        Vector2f operator -() const;

        // dot product
        float operator|(const Vector2f& rhs) const;
        
        // cross product
        float operator^(const Vector2f& rhs) const;
        
        bool operator == (const Vector2f& rhs)const;
        bool operator != (const Vector2f& rhs)const;
        
        float Length() const;
        void Normalize();

        static float DotProduct(const Vector2f& lhs, const Vector2f& rhs);
        static float CrossProduct(const Vector2f& lhs, const Vector2f& rhs);
        static float DistSquared(const Vector2f& lhs, const Vector2f& rhs);
        static float Distance(const Vector2f& lhs, const Vector2f& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline Vector2f::Vector2f()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }
    
    inline Vector2f::Vector2f(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline Vector2f::Vector2f(const Vector2f& v)
    {
        this->x = v.x;
        this->y = v.y;
    }
    
    inline void Vector2f::Set(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline float* Vector2f::data() { return &x; }
    inline const float* Vector2f::data()const { return &x; }
    inline float& Vector2f::operator[](int i) { return (&x)[i]; }
    inline const float& Vector2f::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline Vector2f Vector2f::operator+(const Vector2f& rhs) const
    {
        return Vector2f(this->x+rhs.x, this->y+rhs.y);
    }
    
    inline Vector2f Vector2f::operator-(const Vector2f& rhs) const
    {
        return Vector2f(this->x-rhs.x, this->y-rhs.y);
    }
    
    inline Vector2f Vector2f::operator*(const Vector2f& rhs) const
    {
        return Vector2f(this->x*rhs.x, this->y*rhs.y);
    }
    
    inline Vector2f Vector2f::operator/(const Vector2f& rhs) const
    {
        return Vector2f(this->x/rhs.x, this->y/rhs.y);
    }
    
    inline Vector2f Vector2f::operator*(float scale) const
    {
        return Vector2f(x*scale, y*scale);
    }
    
    inline Vector2f Vector2f::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return Vector2f(x*tmp, y*tmp);
    }
    
    inline Vector2f& Vector2f::operator += (const Vector2f& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    inline Vector2f& Vector2f::operator -= (const Vector2f& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    
    inline Vector2f& Vector2f::operator *=(const Vector2f& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }
    
    inline Vector2f& Vector2f::operator /=(const Vector2f& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }
    
    inline Vector2f& Vector2f::operator *= (const float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }
    
    inline Vector2f& Vector2f::operator /= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        return *this;
    }
    
    inline Vector2f Vector2f::operator -() const
    {
        return Vector2f(-x, -y);
    }
    
    inline float Vector2f::operator|(const Vector2f& rhs) const
    {
        return this->x*rhs.x + this->y*rhs.y;
    }
    
    inline float Vector2f::operator^(const Vector2f& rhs) const
    {
        return this->x*rhs.y - this->y*rhs.x;
    }
    
    inline bool Vector2f::operator == (const Vector2f& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }
    
    inline bool Vector2f::operator != (const Vector2f& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y;
    }
    
    inline float Vector2f::Length() const
    {
        return std::sqrt(x*x+y*y);
    }
    
    inline void Vector2f::Normalize()
    {
        float scale = 1.0f/Length();
        x *= scale;
        y *= scale;
    }
    
    inline float Vector2f::DotProduct(const Vector2f& lhs, const Vector2f& rhs)
    {
        return lhs | rhs;
    }
    
    inline float Vector2f::CrossProduct(const Vector2f& lhs, const Vector2f& rhs)
    {
        return lhs ^ rhs;
    }
    
    inline float Vector2f::DistSquared(const Vector2f& lhs, const Vector2f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return offsetx*offsetx+offsety*offsety;
    }
    
    inline float Vector2f::Distance(const Vector2f& lhs, const Vector2f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return std::sqrt(offsetx*offsetx+offsety*offsety);
    }
}

#endif
