#ifndef PIPELINE_RECT_H_GUARD
#define PIPELINE_RECT_H_GUARD

#include "Common.h"

namespace pipeline{
    
    class kRect
    {
    public:
        float x,y;
        
        static const float epsilon;
        static const kRect xAxis;
        static const kRect yAxis;
        static const kRect one;
        static const kRect zero;

    public:
        kRect(float inx, float iny);
        kRect(const kRect& v);
        
        void Set(float inx, float iny);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        kRect operator+(const kRect& rhs) const;
        kRect operator-(const kRect& rhs) const;
        kRect operator*(const kRect& rhs) const;
        kRect operator/(const kRect& rhs) const;
        kRect operator*(float scale) const;
        kRect operator/(float scale) const;
        
        kRect& operator += (const kRect& rhs);
        kRect& operator -= (const kRect& rhs);
        kRect& operator *=(const kRect& rhs);
        kRect& operator /=(const kRect& rhs);
        kRect& operator *= (const float scale);
        kRect& operator /= (const float scale);
        
        kRect operator -() const;

        // dot product
        float operator|(const kRect& rhs) const;
        
        // cross product
        float operator^(const kRect& rhs) const;
        
        bool operator == (const kRect& rhs)const;
        bool operator != (const kRect& rhs)const;
        
        float Length() const;
        void Normalize();

        static float DotProduct(const kRect& lhs, const kRect& rhs);
        static float CrossProduct(const kRect& lhs, const kRect& rhs);
        static float DistSquared(const kRect& lhs, const kRect& rhs);
        static float Distance(const kRect& lhs, const kRect& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline kRect::kRect(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline kRect::kRect(const kRect& v)
    {
        this->x = v.x;
        this->y = v.y;
    }
    
    inline void kRect::Set(float inx, float iny)
    {
        this->x = inx;
        this->y = iny;
    }
    
    inline float* kRect::data() { return &x; }
    inline const float* kRect::data()const { return &x; }
    inline float& kRect::operator[](int i) { return (&x)[i]; }
    inline const float& kRect::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline kRect kRect::operator+(const kRect& rhs) const
    {
        return kRect(this->x+rhs.x, this->y+rhs.y);
    }
    
    inline kRect kRect::operator-(const kRect& rhs) const
    {
        return kRect(this->x-rhs.x, this->y-rhs.y);
    }
    
    inline kRect kRect::operator*(const kRect& rhs) const
    {
        return kRect(this->x*rhs.x, this->y*rhs.y);
    }
    
    inline kRect kRect::operator/(const kRect& rhs) const
    {
        return kRect(this->x/rhs.x, this->y/rhs.y);
    }
    
    inline kRect kRect::operator*(float scale) const
    {
        return kRect(x*scale, y*scale);
    }
    
    inline kRect kRect::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return kRect(x*tmp, y*tmp);
    }
    
    inline kRect& kRect::operator += (const kRect& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    inline kRect& kRect::operator -= (const kRect& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    
    inline kRect& kRect::operator *=(const kRect& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }
    
    inline kRect& kRect::operator /=(const kRect& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }
    
    inline kRect& kRect::operator *= (const float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }
    
    inline kRect& kRect::operator /= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        return *this;
    }
    
    inline kRect kRect::operator -() const
    {
        return kRect(-x, -y);
    }
    
    inline float kRect::operator|(const kRect& rhs) const
    {
        return this->x*rhs.x + this->y*rhs.y;
    }
    
    inline float kRect::operator^(const kRect& rhs) const
    {
        return this->x*rhs.y - this->y*rhs.x;
    }
    
    inline bool kRect::operator == (const kRect& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }
    
    inline bool kRect::operator != (const kRect& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y;
    }
    
    inline float kRect::Length() const
    {
        return std::sqrt(x*x+y*y);
    }
    
    inline void kRect::Normalize()
    {
        float scale = 1.0f/Length();
        x *= scale;
        y *= scale;
    }
    
    inline float kRect::DotProduct(const kRect& lhs, const kRect& rhs)
    {
        return lhs | rhs;
    }
    
    inline float kRect::CrossProduct(const kRect& lhs, const kRect& rhs)
    {
        return lhs ^ rhs;
    }
    
    inline float kRect::DistSquared(const kRect& lhs, const kRect& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return offsetx*offsetx+offsety*offsety;
    }
    
    inline float kRect::Distance(const kRect& lhs, const kRect& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        
        return std::sqrt(offsetx*offsetx+offsety*offsety);
    }
}

#endif
