/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_RAY_H_GUARD
#define PIPELINE_RAY_H_GUARD

#include "Common.h"

namespace pipeline{
    
    class Ray
    {
    public:
        float x,y;
        
        static const float epsilon;
        static const Ray xAxis;
        static const Ray yAxis;
        static const Ray one;
        static const Ray zero;

    public:
        Ray(float inx, float iny);
        Ray(const Ray& v);
        
        void Set(float inx, float iny);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        Ray operator+(const Ray& rhs) const;
        Ray operator-(const Ray& rhs) const;
        Ray operator*(const Ray& rhs) const;
        Ray operator/(const Ray& rhs) const;
        Ray operator*(float scale) const;
        Ray operator/(float scale) const;
        
        Ray& operator += (const Ray& rhs);
        Ray& operator -= (const Ray& rhs);
        Ray& operator *=(const Ray& rhs);
        Ray& operator /=(const Ray& rhs);
        Ray& operator *= (const float scale);
        Ray& operator /= (const float scale);
        
        Ray operator -() const;

        // dot product
        float operator|(const Ray& rhs) const;
        
        // cross product
        float operator^(const Ray& rhs) const;
        
        bool operator == (const Ray& rhs)const;
        bool operator != (const Ray& rhs)const;
        
        float Length() const;
        void Normalize();

        static float DotProduct(const Ray& lhs, const Ray& rhs);
        static float CrossProduct(const Ray& lhs, const Ray& rhs);
        static float DistSquared(const Ray& lhs, const Ray& rhs);
        static float Distance(const Ray& lhs, const Ray& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline Ray::Ray(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline Ray::Ray(const Ray& v)
    {
        this->x = v.x;
        this->y = v.y;
    }
    
    inline void Ray::Set(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline float* Ray::data() { return &x; }
    inline const float* Ray::data()const { return &x; }
    inline float& Ray::operator[](int i) { return (&x)[i]; }
    inline const float& Ray::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline Ray Ray::operator+(const Ray& rhs) const
    {
        return Ray(this->x+rhs.x, this->y+rhs.y);
    }
    
    inline Ray Ray::operator-(const Ray& rhs) const
    {
        return Ray(this->x-rhs.x, this->y-rhs.y);
    }
    
    inline Ray Ray::operator*(const Ray& rhs) const
    {
        return Ray(this->x*rhs.x, this->y*rhs.y);
    }
    
    inline Ray Ray::operator/(const Ray& rhs) const
    {
        return Ray(this->x/rhs.x, this->y/rhs.y);
    }
    
    inline Ray Ray::operator*(float scale) const
    {
        return Ray(x*scale, y*scale);
    }
    
    inline Ray Ray::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return Ray(x*tmp, y*tmp);
    }
    
    inline Ray& Ray::operator += (const Ray& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    inline Ray& Ray::operator -= (const Ray& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    
    inline Ray& Ray::operator *=(const Ray& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }
    
    inline Ray& Ray::operator /=(const Ray& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }
    
    inline Ray& Ray::operator *= (const float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }
    
    inline Ray& Ray::operator /= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        return *this;
    }
    
    inline Ray Ray::operator -() const
    {
        return Ray(-x, -y);
    }
    
    inline float Ray::operator|(const Ray& rhs) const
    {
        return this->x*rhs.x + this->y*rhs.y;
    }
    
    inline float Ray::operator^(const Ray& rhs) const
    {
        return this->x*rhs.y - this->y*rhs.x;
    }
    
    inline bool Ray::operator == (const Ray& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }
    
    inline bool Ray::operator != (const Ray& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y;
    }
    
    inline float Ray::Length() const
    {
        return std::sqrt(x*x+y*y);
    }
    
    inline void Ray::Normalize()
    {
        float scale = 1.0f/Length();
        x *= scale;
        y *= scale;
    }
    
    inline float Ray::DotProduct(const Ray& lhs, const Ray& rhs)
    {
        return lhs | rhs;
    }
    
    inline float Ray::CrossProduct(const Ray& lhs, const Ray& rhs)
    {
        return lhs ^ rhs;
    }
    
    inline float Ray::DistSquared(const Ray& lhs, const Ray& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return offsetx*offsetx+offsety*offsety;
    }
    
    inline float Ray::Distance(const Ray& lhs, const Ray& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return std::sqrt(offsetx*offsetx+offsety*offsety);
    }
}

#endif
