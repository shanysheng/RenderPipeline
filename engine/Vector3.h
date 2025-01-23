#ifndef PIPELINE_VECTOR3_H_GUARD
#define PIPELINE_VECTOR3_H_GUARD

#include "Common.h"

namespace pipeline{
    
    class kVector3f
    {
    public:
        float x,y,z;
        
        static const float epsilon;
        static const kVector3f xAxis;
        static const kVector3f yAxis;
        static const kVector3f one;
        static const kVector3f zero;
        
    public:
        kVector3f();
        kVector3f(float inx, float iny, float inz);
        kVector3f(const kVector3f& v);
        
        void Set(float inx, float iny, float inz);
        
        float* data ();
        const float* data ()const;
        float& operator[](int i);
        const float& operator[](int i)const;
        
        // component-wise multiplication
        kVector3f operator+(const kVector3f& rhs) const;
        kVector3f operator-(const kVector3f& rhs) const;
        kVector3f operator*(const kVector3f& rhs) const;
        kVector3f operator/(const kVector3f& rhs) const;
        kVector3f operator*(float scale) const;
        kVector3f operator/(float scale) const;
        
        kVector3f& operator += (const kVector3f& rhs);
        kVector3f& operator -= (const kVector3f& rhs);
        kVector3f& operator *=(const kVector3f& rhs);
        kVector3f& operator /=(const kVector3f& rhs);
        kVector3f& operator *= (const float scale);
        kVector3f& operator /= (const float scale);
        
        kVector3f operator -() const;
        
        // dot product
        float operator|(const kVector3f& rhs) const;
        
        // cross product
        kVector3f operator^(const kVector3f& rhs) const;
        
        bool operator == (const kVector3f& rhs)const;
        bool operator != (const kVector3f& rhs)const;
        
        float Length() const;
        void Normalize();
        
        static float DotProduct(const kVector3f& lhs, const kVector3f& rhs);
        static kVector3f CrossProduct(const kVector3f& lhs, const kVector3f& rhs);
        static float DistSquared(const kVector3f& lhs, const kVector3f& rhs);
        static float Distance(const kVector3f& lhs, const kVector3f& rhs);
    };
    
    //-----------------------------------------------------------------------------------
    inline kVector3f::kVector3f()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    }

    inline kVector3f::kVector3f(float inx, float iny, float inz)
    {
        this->x = inx;
        this->y = iny;
        this->z = inz;
    }
    
    inline kVector3f::kVector3f(const kVector3f& v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }
    
    inline void kVector3f::Set(float inx, float iny, float inz)
    {
        this->x = inx;
        this->y = iny;
        this->z = inz;
    }
    
    inline float* kVector3f::data() { return &x; }
    inline const float* kVector3f::data()const { return &x; }
    inline float& kVector3f::operator[](int i) { return (&x)[i]; }
    inline const float& kVector3f::operator[](int i)const { return (&x)[i]; }
    
    // component-wise multiplication
    inline kVector3f kVector3f::operator+(const kVector3f& rhs) const
    {
        return kVector3f(this->x+rhs.x, this->y+rhs.y, this->z+rhs.z);
    }
    
    inline kVector3f kVector3f::operator-(const kVector3f& rhs) const
    {
        return kVector3f(this->x-rhs.x, this->y-rhs.y, this->z-rhs.z);
    }
    
    inline kVector3f kVector3f::operator*(const kVector3f& rhs) const
    {
        return kVector3f(this->x*rhs.x, this->y*rhs.y, this->z*rhs.z);
    }
    
    inline kVector3f kVector3f::operator/(const kVector3f& rhs) const
    {
        return kVector3f(this->x/rhs.x, this->y/rhs.y, this->z/rhs.z);
    }
    
    inline kVector3f kVector3f::operator*(float scale) const
    {
        return kVector3f(x*scale, y*scale, z*scale);
    }
    
    inline kVector3f kVector3f::operator/(float scale) const
    {
        const float tmp = 1.f/scale;
        return kVector3f(x*tmp, y*tmp, z*tmp);
    }
    
    inline kVector3f& kVector3f::operator += (const kVector3f& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }
    
    inline kVector3f& kVector3f::operator -= (const kVector3f& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }
    
    inline kVector3f& kVector3f::operator *=(const kVector3f& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        return *this;
    }
    
    inline kVector3f& kVector3f::operator /=(const kVector3f& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;
        this->z /= rhs.z;
        return *this;
    }
    
    inline kVector3f& kVector3f::operator *= (const float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }
    
    inline kVector3f& kVector3f::operator /= (const float scale)
    {
        const float tmp = 1.f/scale;
        x *= tmp;
        y *= tmp;
        z *= tmp;
        return *this;
    }
    
    inline kVector3f kVector3f::operator -() const
    {
        return kVector3f(-x, -y, -z);
    }
    
    inline float kVector3f::operator|(const kVector3f& rhs) const
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    
    inline kVector3f kVector3f::operator^(const kVector3f& rhs) const
    {
        return kVector3f (y * rhs.z - z * rhs.y,
                         z * rhs.x - x * rhs.z,
                         x * rhs.y - y * rhs.x);
    }
    
    inline bool kVector3f::operator == (const kVector3f& rhs)const
    {
        return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
    }
    
    inline bool kVector3f::operator != (const kVector3f& rhs)const
    {
        return this->x != rhs.x || this->y != rhs.y || this->z != rhs.z;
    }
    
    inline float kVector3f::Length() const
    {
        return std::sqrt(x*x+y*y+z*z);
    }
    
    inline void kVector3f::Normalize()
    {
        float scale = 1.0f/Length();
        x *= scale;
        y *= scale;
        z *= scale;
    }
    
    inline float kVector3f::DotProduct(const kVector3f& lhs, const kVector3f& rhs)
    {
        return lhs | rhs;
    }
    
    inline kVector3f kVector3f::CrossProduct(const kVector3f& lhs, const kVector3f& rhs)
    {
        return lhs ^ rhs;
    }
    
    inline float kVector3f::DistSquared(const kVector3f& lhs, const kVector3f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        float offsetz = lhs.z-rhs.z;
        
        return offsetx*offsetx+offsety*offsety+offsetz*offsetz;
    }
    
    inline float kVector3f::Distance(const kVector3f& lhs, const kVector3f& rhs)
    {
        float offsetx = lhs.x-rhs.x;
        float offsety = lhs.y-rhs.y;
        float offsetz = lhs.z-rhs.z;

        return std::sqrt(offsetx*offsetx+offsety*offsety+offsetz*offsetz);
    }
}

#endif
