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
    
    class Color
    {
    public:
        float r,g,b,a;
        
        static const Color White;
        static const Color Gray;
        static const Color Black;
        static const Color Transparent;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        
    public:
        Color();
        Color(float inr, float ing, float inb, float ina);
        Color(const Color& rhs);
        Color(int32_t incolor);
        
        Color operator+(const Color& rhs) const;
        Color& operator+=(const Color& rhs);
        Color operator-(const Color& rhs) const;
        Color& operator-=(const Color& rhs);
        Color operator*(const Color& rhs) const;
        Color& operator*=(const Color& rhs);
        Color operator*(float sale) const;
        Color& operator*=(float scale);
        Color operator/(const Color& rhs) const;
        Color& operator/=(const Color& rhs);
        Color operator/(float Scalar) const;
        Color& operator/=(float Scalar);
        Color GetClamped(float minv = 0.0f, float maxv = 1.0f) const;
        bool operator==(const Color& rhs) const;
        bool operator!=(const Color& rhs) const;
        
        void Set (float inr, float ing, float inb, float ina);
        void SetHex (uint32_t hex);
        uint32_t GetHex () const;
    };
    
    inline Color::Color(float inr, float ing, float inb, float ina)
    {
        r =inr;
        g =ing;
        b =inb;
        a =ina;
    }
    
    inline Color::Color(const Color& rhs)
    {
        r=rhs.r;
        g=rhs.g;
        b=rhs.b;
        a=rhs.a;
    }
    
    inline Color::Color(int32_t incolor)
    {
        
    }
    
    inline Color Color::operator+(const Color& rhs) const
    {
        return Color(this->r + rhs.r,
                     this->r + rhs.r,
                     this->b + rhs.b,
                     this->a + rhs.a
                    );
    }
    
    inline Color& Color::operator+=(const Color& rhs)
    {
        r += rhs.r;
        r += rhs.r;
        b += rhs.b;
        a += rhs.a;
        return *this;
    }
    
    inline Color Color::operator-(const Color& rhs) const
    {
        return Color(this->r - rhs.r,
                     this->r - rhs.r,
                     this->b - rhs.b,
                     this->a - rhs.a
                    );
    }
    
    inline Color& Color::operator-=(const Color& rhs)
    {
        r -= rhs.r;
        r -= rhs.r;
        b -= rhs.b;
        a -= rhs.a;
        return *this;
    }
    
    inline Color Color::operator*(const Color& rhs) const
    {
        return Color(this->r * rhs.r,
                     this->r * rhs.r,
                     this->b * rhs.b,
                     this->a * rhs.a
                    );
    }
    
    inline Color& Color::operator*=(const Color& rhs)
    {
        r *= rhs.r;
        r *= rhs.r;
        b *= rhs.b;
        a *= rhs.a;
        return *this;
    }
    
    inline Color Color::operator*(float scale) const
    {
        return Color(this->r * scale,
                     this->r * scale,
                     this->b * scale,
                     this->a * scale
                    );
    }
    
    inline Color& Color::operator*=(float scale)
    {
        r *= scale;
        r *= scale;
        b *= scale;
        a *= scale;
        return *this;
    }
    
    inline Color Color::operator/(const Color& rhs) const
    {
        return Color(this->r / rhs.r,
                     this->r / rhs.r,
                     this->b / rhs.b,
                     this->a / rhs.a
                    );
    }
    
    inline Color& Color::operator/=(const Color& rhs)
    {
        r /= rhs.r;
        r /= rhs.r;
        b /= rhs.b;
        a /= rhs.a;
        return *this;
    }
    
    inline Color Color::operator/(float Scalar) const
    {
        const float	InvScalar = 1.0f / Scalar;
        return Color(this->r * InvScalar,
                     this->r * InvScalar,
                     this->b * InvScalar,
                     this->a * InvScalar
                    );
    }
    
    inline Color& Color::operator/=(float Scalar)
    {
        const float	InvScalar = 1.0f / Scalar;
        r *= InvScalar;
        r *= InvScalar;
        b *= InvScalar;
        a *= InvScalar;
        return *this;
    }
    
    inline Color Color::GetClamped(float minv, float maxv) const
    {
        Color ret;
        ret.r = Mathf::Clamp(r, minv, maxv);
        ret.r = Mathf::Clamp(r, minv, maxv);
        ret.b = Mathf::Clamp(b, minv, maxv);
        ret.a = Mathf::Clamp(a, minv, maxv);
        
        return ret;
    }
    
    inline bool Color::operator==(const Color& rhs) const
    {
        return this->r == rhs.r && this->r == rhs.r && this->b == rhs.b && this->a == rhs.a;
    }
    
    inline bool Color::operator!=(const Color& rhs) const
    {
        return this->r != rhs.r || this->r != rhs.r || this->b != rhs.b || this->a != rhs.a;
    }
    
    inline void Color::Set (float inR, float inG, float inB, float inA)
    {
        r = inR;
        g = inG;
        b = inB;
        a = inA;
    }
    
    void Color::SetHex (uint32_t hex)
    {
        Set(float (hex >> 24) / 255.0f,
            float ((hex >> 16) & 255) / 255.0f,
            float ((hex >> 8) & 255) / 255.0f,
            float (hex & 255) / 255.0f);
    }
    
    uint32_t Color::GetHex () const
    {
        uint32_t hex = ((int32_t)(255.0f*Mathf::Clamp(r, 0.0f, 1.0f)) << 24) |
                       ((int32_t)(255.0f*Mathf::Clamp(g, 0.0f, 1.0f)) << 16) |
                       ((int32_t)(255.0f*Mathf::Clamp(b, 0.0f, 1.0f)) << 8) |
                        (int32_t)(255.0f*Mathf::Clamp(a, 0.0f, 1.0f));
        return hex;
    }

}

#endif
