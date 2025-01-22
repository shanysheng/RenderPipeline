/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_RAY_H_GUARD
#define PIPELINE_RAY_H_GUARD

#include "Common.h"

namespace pipeline{
    
    class kRay
    {
    public:
        float x,y;
        
        static const float epsilon;
        static const kRay xAxis;
        static const kRay yAxis;
        static const kRay one;
        static const kRay zero;

    public:
        kRay();
        kRay(float inx, float iny);
        kRay(const kRay& v);
        
        void Set(float inx, float iny);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        kRay operator+(const kRay& rhs) const;
        kRay operator-(const kRay& rhs) const;
        kRay operator*(const kRay& rhs) const;
        kRay operator/(const kRay& rhs) const;
        kRay operator*(float scale) const;
        kRay operator/(float scale) const;
        
        kRay& operator += (const kRay& rhs);
        kRay& operator -= (const kRay& rhs);
        kRay& operator *=(const kRay& rhs);
        kRay& operator /=(const kRay& rhs);
        kRay& operator *= (const float scale);
        kRay& operator /= (const float scale);
        
        kRay operator -() const;

        // dot product
        float operator|(const kRay& rhs) const;
        
        // cross product
        float operator^(const kRay& rhs) const;
        
        bool operator == (const kRay& rhs)const;
        bool operator != (const kRay& rhs)const;
        
        float Length() const;
        void Normalize();

        static float DotProduct(const kRay& lhs, const kRay& rhs);
        static float CrossProduct(const kRay& lhs, const kRay& rhs);
        static float DistSquared(const kRay& lhs, const kRay& rhs);
        static float Distance(const kRay& lhs, const kRay& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline kRay::kRay()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }
    
    inline kRay::kRay(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline kRay::kRay(const kRay& v)
    {
        this->x = v.x;
        this->y = v.y;
    }
    
    inline void kRay::Set(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline float* kRay::data() { return &x; }
    inline const float* kRay::data()const { return &x; }
    inline float& kRay::operator[](int i) { return (&x)[i]; }
    inline const float& kRay::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline kRay kRay::operator+(const kRay& rhs) const
    {
        return kRay(this->x+rhs.x, this->y+rhs.y);
    }
    
    inline kRay kRay::operator-(const kRay& rhs) const
    {
        return kRay(this->x-rhs.x, this->y-rhs.y);
    }
    
    inline kRay kRay::operator*(const kRay& rhs) const
    {
        return kRay(this->x*rhs.x, this->y*rhs.y);
    }
    
    inline kRay kRay::operator/(const kRay& rhs) const
    {
        return kRay(this->x/rhs.x, this->y/rhs.y);
    }
    
    inline kRay kRay::operator*(float scale) const
    {
        return kRay(x*scale, y*scale);
    }
    
    inline kRay kRay::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return kRay(x*tmp, y*tmp);
    }
    
    inline kRay& kRay::operator += (const kRay& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    inline kRay& kRay::operator -= (const kRay& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    
    inline kRay& kRay::operator *=(const kRay& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }
    
    inline kRay& kRay::operator /=(const kRay& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }
    
    inline kRay& kRay::operator *= (const float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }
    
    inline kRay& kRay::operator /= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        return *this;
    }
    
    inline kRay kRay::operator -() const
    {
        return kRay(-x, -y);
    }
    
    inline float kRay::operator|(const kRay& rhs) const
    {
        return this->x*rhs.x + this->y*rhs.y;
    }
    
    inline float kRay::operator^(const kRay& rhs) const
    {
        return this->x*rhs.y - this->y*rhs.x;
    }
    
    inline bool kRay::operator == (const kRay& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }
    
    inline bool kRay::operator != (const kRay& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y;
    }
    
    inline float kRay::Length() const
    {
        return std::sqrt(x*x+y*y);
    }
    
    inline void kRay::Normalize()
    {
        float scale = 1.0f/Length();
        x *= scale;
        y *= scale;
    }
    
    inline float kRay::DotProduct(const kRay& lhs, const kRay& rhs)
    {
        return lhs | rhs;
    }
    
    inline float kRay::CrossProduct(const kRay& lhs, const kRay& rhs)
    {
        return lhs ^ rhs;
    }
    
    inline float kRay::DistSquared(const kRay& lhs, const kRay& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return offsetx*offsetx+offsety*offsety;
    }
    
    inline float kRay::Distance(const kRay& lhs, const kRay& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return std::sqrt(offsetx*offsetx+offsety*offsety);
    }
}

#endif
