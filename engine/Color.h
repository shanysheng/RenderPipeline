/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/bob/master/LICENSE
*/

#ifndef PIPELINE_COLOR_H_GUARD
#define PIPELINE_COLOR_H_GUARD

#include "Common.h"
#include "Mathf.h"

namespace pipeline{
    
    class kColor
    {
    public:
        float r,g,b,a;
        
        static const kColor White;
        static const kColor Gray;
        static const kColor Black;
        static const kColor Transparent;
        static const kColor Red;
        static const kColor Green;
        static const kColor Blue;
        static const kColor Yellow;
        
    public:
        kColor();
        kColor(float inr, float ing, float inb, float ina);
        kColor(const kColor& rhs);
        kColor(int32_t incolor);
        
        kColor operator+(const kColor& rhs) const;
        kColor& operator+=(const kColor& rhs);
        kColor operator-(const kColor& rhs) const;
        kColor& operator-=(const kColor& rhs);
        kColor operator*(const kColor& rhs) const;
        kColor& operator*=(const kColor& rhs);
        kColor operator*(float sale) const;
        kColor& operator*=(float scale);
        kColor operator/(const kColor& rhs) const;
        kColor& operator/=(const kColor& rhs);
        kColor operator/(float Scalar) const;
        kColor& operator/=(float Scalar);
        kColor GetClamped(float minv = 0.0f, float maxv = 1.0f) const;
        bool operator==(const kColor& rhs) const;
        bool operator!=(const kColor& rhs) const;
        
        void Set (float inr, float ing, float inb, float ina);
        void SetHex (uint32_t hex);
        uint32_t GetHex () const;
    };

    inline kColor::kColor()
    {
        r = White.r;
        g = White.g;
        b = White.b;
        a = White.a;
    }
    
    inline kColor::kColor(float inr, float ing, float inb, float ina)
    {
        r =inr;
        g =ing;
        b =inb;
        a =ina;
    }
    
    inline kColor::kColor(const kColor& rhs)
    {
        r=rhs.r;
        g=rhs.g;
        b=rhs.b;
        a=rhs.a;
    }
    
    inline kColor::kColor(int32_t incolor)
    {
        
    }
    
    inline kColor kColor::operator+(const kColor& rhs) const
    {
        return kColor(this->r + rhs.r,
                     this->r + rhs.r,
                     this->b + rhs.b,
                     this->a + rhs.a
                    );
    }
    
    inline kColor& kColor::operator+=(const kColor& rhs)
    {
        r += rhs.r;
        r += rhs.r;
        b += rhs.b;
        a += rhs.a;
        return *this;
    }
    
    inline kColor kColor::operator-(const kColor& rhs) const
    {
        return kColor(this->r - rhs.r,
                     this->r - rhs.r,
                     this->b - rhs.b,
                     this->a - rhs.a
                    );
    }
    
    inline kColor& kColor::operator-=(const kColor& rhs)
    {
        r -= rhs.r;
        r -= rhs.r;
        b -= rhs.b;
        a -= rhs.a;
        return *this;
    }
    
    inline kColor kColor::operator*(const kColor& rhs) const
    {
        return kColor(this->r * rhs.r,
                     this->r * rhs.r,
                     this->b * rhs.b,
                     this->a * rhs.a
                    );
    }
    
    inline kColor& kColor::operator*=(const kColor& rhs)
    {
        r *= rhs.r;
        r *= rhs.r;
        b *= rhs.b;
        a *= rhs.a;
        return *this;
    }
    
    inline kColor kColor::operator*(float scale) const
    {
        return kColor(this->r * scale,
                     this->r * scale,
                     this->b * scale,
                     this->a * scale
                    );
    }
    
    inline kColor& kColor::operator*=(float scale)
    {
        r *= scale;
        r *= scale;
        b *= scale;
        a *= scale;
        return *this;
    }
    
    inline kColor kColor::operator/(const kColor& rhs) const
    {
        return kColor(this->r / rhs.r,
                     this->r / rhs.r,
                     this->b / rhs.b,
                     this->a / rhs.a
                    );
    }
    
    inline kColor& kColor::operator/=(const kColor& rhs)
    {
        r /= rhs.r;
        r /= rhs.r;
        b /= rhs.b;
        a /= rhs.a;
        return *this;
    }
    
    inline kColor kColor::operator/(float Scalar) const
    {
        const float	InvScalar = 1.0f / Scalar;
        return kColor(this->r * InvScalar,
                     this->r * InvScalar,
                     this->b * InvScalar,
                     this->a * InvScalar
                    );
    }
    
    inline kColor& kColor::operator/=(float Scalar)
    {
        const float	InvScalar = 1.0f / Scalar;
        r *= InvScalar;
        r *= InvScalar;
        b *= InvScalar;
        a *= InvScalar;
        return *this;
    }
    
    inline kColor kColor::GetClamped(float minv, float maxv) const
    {
        kColor ret;
        ret.r = kMathf::Clamp(r, minv, maxv);
        ret.r = kMathf::Clamp(r, minv, maxv);
        ret.b = kMathf::Clamp(b, minv, maxv);
        ret.a = kMathf::Clamp(a, minv, maxv);
        
        return ret;
    }
    
    inline bool kColor::operator==(const kColor& rhs) const
    {
        return this->r == rhs.r && this->r == rhs.r && this->b == rhs.b && this->a == rhs.a;
    }
    
    inline bool kColor::operator!=(const kColor& rhs) const
    {
        return this->r != rhs.r || this->r != rhs.r || this->b != rhs.b || this->a != rhs.a;
    }
    
    inline void kColor::Set (float inR, float inG, float inB, float inA)
    {
        r = inR;
        g = inG;
        b = inB;
        a = inA;
    }
    
    inline void kColor::SetHex (uint32_t hex)
    {
        Set(float (hex >> 24) / 255.0f,
            float ((hex >> 16) & 255) / 255.0f,
            float ((hex >> 8) & 255) / 255.0f,
            float (hex & 255) / 255.0f);
    }
    
    inline uint32_t kColor::GetHex () const
    {
        uint32_t hex = ((int32_t)(255.0f*kMathf::Clamp(r, 0.0f, 1.0f)) << 24) |
                       ((int32_t)(255.0f*kMathf::Clamp(g, 0.0f, 1.0f)) << 16) |
                       ((int32_t)(255.0f*kMathf::Clamp(b, 0.0f, 1.0f)) << 8) |
                        (int32_t)(255.0f*kMathf::Clamp(a, 0.0f, 1.0f));
        return hex;
    }
    
    class Color32
    {
    public:
        int color;
    };
    

}

#endif
