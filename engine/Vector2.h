/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_VECTOR2_H_GUARD
#define PIPELINE_VECTOR2_H_GUARD

#include "Common.h"

namespace pipeline{
    
    class kVector2f
    {
    public:
        float x,y;
        
        static const float epsilon;
        static const kVector2f xAxis;
        static const kVector2f yAxis;
        static const kVector2f one;
        static const kVector2f zero;

    public:
        kVector2f();
        kVector2f(float inx, float iny);
        kVector2f(const kVector2f& v);
        
        void Set(float inx, float iny);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        kVector2f operator+(const kVector2f& rhs) const;
        kVector2f operator-(const kVector2f& rhs) const;
        kVector2f operator*(const kVector2f& rhs) const;
        kVector2f operator/(const kVector2f& rhs) const;
        kVector2f operator*(float scale) const;
        kVector2f operator/(float scale) const;
        
        kVector2f& operator += (const kVector2f& rhs);
        kVector2f& operator -= (const kVector2f& rhs);
        kVector2f& operator *=(const kVector2f& rhs);
        kVector2f& operator /=(const kVector2f& rhs);
        kVector2f& operator *= (const float scale);
        kVector2f& operator /= (const float scale);
        
        kVector2f operator -() const;

        // dot product
        float operator|(const kVector2f& rhs) const;
        
        // cross product
        float operator^(const kVector2f& rhs) const;
        
        bool operator == (const kVector2f& rhs)const;
        bool operator != (const kVector2f& rhs)const;
        
        float Length() const;
        void Normalize();

        static float DotProduct(const kVector2f& lhs, const kVector2f& rhs);
        static float CrossProduct(const kVector2f& lhs, const kVector2f& rhs);
        static float DistSquared(const kVector2f& lhs, const kVector2f& rhs);
        static float Distance(const kVector2f& lhs, const kVector2f& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline kVector2f::kVector2f()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }
    
    inline kVector2f::kVector2f(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline kVector2f::kVector2f(const kVector2f& v)
    {
        this->x = v.x;
        this->y = v.y;
    }
    
    inline void kVector2f::Set(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline float* kVector2f::data() { return &x; }
    inline const float* kVector2f::data()const { return &x; }
    inline float& kVector2f::operator[](int i) { return (&x)[i]; }
    inline const float& kVector2f::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline kVector2f kVector2f::operator+(const kVector2f& rhs) const
    {
        return kVector2f(this->x+rhs.x, this->y+rhs.y);
    }
    
    inline kVector2f kVector2f::operator-(const kVector2f& rhs) const
    {
        return kVector2f(this->x-rhs.x, this->y-rhs.y);
    }
    
    inline kVector2f kVector2f::operator*(const kVector2f& rhs) const
    {
        return kVector2f(this->x*rhs.x, this->y*rhs.y);
    }
    
    inline kVector2f kVector2f::operator/(const kVector2f& rhs) const
    {
        return kVector2f(this->x/rhs.x, this->y/rhs.y);
    }
    
    inline kVector2f kVector2f::operator*(float scale) const
    {
        return kVector2f(x*scale, y*scale);
    }
    
    inline kVector2f kVector2f::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return kVector2f(x*tmp, y*tmp);
    }
    
    inline kVector2f& kVector2f::operator += (const kVector2f& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    inline kVector2f& kVector2f::operator -= (const kVector2f& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    
    inline kVector2f& kVector2f::operator *=(const kVector2f& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }
    
    inline kVector2f& kVector2f::operator /=(const kVector2f& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }
    
    inline kVector2f& kVector2f::operator *= (const float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }
    
    inline kVector2f& kVector2f::operator /= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        return *this;
    }
    
    inline kVector2f kVector2f::operator -() const
    {
        return kVector2f(-x, -y);
    }
    
    inline float kVector2f::operator|(const kVector2f& rhs) const
    {
        return this->x*rhs.x + this->y*rhs.y;
    }
    
    inline float kVector2f::operator^(const kVector2f& rhs) const
    {
        return this->x*rhs.y - this->y*rhs.x;
    }
    
    inline bool kVector2f::operator == (const kVector2f& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }
    
    inline bool kVector2f::operator != (const kVector2f& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y;
    }
    
    inline float kVector2f::Length() const
    {
        return std::sqrt(x*x+y*y);
    }
    
    inline void kVector2f::Normalize()
    {
        float scale = 1.0f/Length();
        x *= scale;
        y *= scale;
    }
    
    inline float kVector2f::DotProduct(const kVector2f& lhs, const kVector2f& rhs)
    {
        return lhs | rhs;
    }
    
    inline float kVector2f::CrossProduct(const kVector2f& lhs, const kVector2f& rhs)
    {
        return lhs ^ rhs;
    }
    
    inline float kVector2f::DistSquared(const kVector2f& lhs, const kVector2f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return offsetx*offsetx+offsety*offsety;
    }
    
    inline float kVector2f::Distance(const kVector2f& lhs, const kVector2f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return std::sqrt(offsetx*offsetx+offsety*offsety);
    }
}

#endif
