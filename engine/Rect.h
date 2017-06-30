/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_RECT_H_GUARD
#define PIPELINE_RECT_H_GUARD

#include "Common.h"

namespace pipeline{
    
    class Rect
    {
    public:
        float x,y;
        
        static const float epsilon;
        static const Rect xAxis;
        static const Rect yAxis;
        static const Rect one;
        static const Rect zero;

    public:
        Rect(float inx, float iny);
        Rect(const Rect& v);
        
        void Set(float inx, float iny);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        Rect operator+(const Rect& rhs) const;
        Rect operator-(const Rect& rhs) const;
        Rect operator*(const Rect& rhs) const;
        Rect operator/(const Rect& rhs) const;
        Rect operator*(float scale) const;
        Rect operator/(float scale) const;
        
        Rect& operator += (const Rect& rhs);
        Rect& operator -= (const Rect& rhs);
        Rect& operator *=(const Rect& rhs);
        Rect& operator /=(const Rect& rhs);
        Rect& operator *= (const float scale);
        Rect& operator /= (const float scale);
        
        Rect operator -() const;

        // dot product
        float operator|(const Rect& rhs) const;
        
        // cross product
        float operator^(const Rect& rhs) const;
        
        bool operator == (const Rect& rhs)const;
        bool operator != (const Rect& rhs)const;
        
        float Length() const;
        void Normalize();

        static float DotProduct(const Rect& lhs, const Rect& rhs);
        static float CrossProduct(const Rect& lhs, const Rect& rhs);
        static float DistSquared(const Rect& lhs, const Rect& rhs);
        static float Distance(const Rect& lhs, const Rect& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline Rect::Rect(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline Rect::Rect(const Rect& v)
    {
        this->x = v.x;
        this->y = v.y;
    }
    
    inline void Rect::Set(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline float* Rect::data() { return &x; }
    inline const float* Rect::data()const { return &x; }
    inline float& Rect::operator[](int i) { return (&x)[i]; }
    inline const float& Rect::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline Rect Rect::operator+(const Rect& rhs) const
    {
        return Rect(this->x+rhs.x, this->y+rhs.y);
    }
    
    inline Rect Rect::operator-(const Rect& rhs) const
    {
        return Rect(this->x-rhs.x, this->y-rhs.y);
    }
    
    inline Rect Rect::operator*(const Rect& rhs) const
    {
        return Rect(this->x*rhs.x, this->y*rhs.y);
    }
    
    inline Rect Rect::operator/(const Rect& rhs) const
    {
        return Rect(this->x/rhs.x, this->y/rhs.y);
    }
    
    inline Rect Rect::operator*(float scale) const
    {
        return Rect(x*scale, y*scale);
    }
    
    inline Rect Rect::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return Rect(x*tmp, y*tmp);
    }
    
    inline Rect& Rect::operator += (const Rect& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    inline Rect& Rect::operator -= (const Rect& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    
    inline Rect& Rect::operator *=(const Rect& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }
    
    inline Rect& Rect::operator /=(const Rect& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }
    
    inline Rect& Rect::operator *= (const float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }
    
    inline Rect& Rect::operator /= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        return *this;
    }
    
    inline Rect Rect::operator -() const
    {
        return Rect(-x, -y);
    }
    
    inline float Rect::operator|(const Rect& rhs) const
    {
        return this->x*rhs.x + this->y*rhs.y;
    }
    
    inline float Rect::operator^(const Rect& rhs) const
    {
        return this->x*rhs.y - this->y*rhs.x;
    }
    
    inline bool Rect::operator == (const Rect& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }
    
    inline bool Rect::operator != (const Rect& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y;
    }
    
    inline float Rect::Length() const
    {
        return std::sqrt(x*x+y*y);
    }
    
    inline void Rect::Normalize()
    {
        float scale = 1.0f/Length();
        x *= scale;
        y *= scale;
    }
    
    inline float Rect::DotProduct(const Rect& lhs, const Rect& rhs)
    {
        return lhs | rhs;
    }
    
    inline float Rect::CrossProduct(const Rect& lhs, const Rect& rhs)
    {
        return lhs ^ rhs;
    }
    
    inline float Rect::DistSquared(const Rect& lhs, const Rect& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return offsetx*offsetx+offsety*offsety;
    }
    
    inline float Rect::Distance(const Rect& lhs, const Rect& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return std::sqrt(offsetx*offsetx+offsety*offsety);
    }
}

#endif
