#include "Appearance.h"

namespace pipeline {
    
    Appearance::Appearance (const Appearance& source)
    {
        
    }
    
    Appearance::Appearance (Shader*shader)
    {
        
    }
    
    
    const Color& Appearance::GetColor (const std::string& name)
    {
        return color;
    }
    
    const Color& Appearance::GetColor (int nameID)
    {
        return color;
    }
    
    void Appearance::GetColorArray (int nameID, std::vector<Color> values)
    {
        
    }
    
    void Appearance::GetColorArray (const std::string& name, std::vector<Color> values)
    {
        
    }
    
    
    float Appearance::GetFloat (const std::string& name)
    {
        return 0.0f;
    }
    
    float Appearance::GetFloat (int nameID)
    {
        return 0.0f;
    }
    
    void Appearance::GetFloatArray (int nameID, std::vector<float> values)
    {
        
    }
    
    void Appearance::GetFloatArray (const std::string& name, std::vector<float> values)
    {
        
    }
    
    
    int Appearance::GetInt (int nameID)
    {
        return 0;
    }
    
    int Appearance::GetInt (const std::string& name)
    {
        return 0;
    }
    
    
//    const Matrix4x4f& Appearance::GetMatrix (const std::string& name)
//    {
//    }
//
//    const Matrix4x4f& Appearance::GetMatrix (int nameID)
//    {
//    }
    
    void Appearance::GetMatrixArray (const std::string& name, std::vector<Matrix4x4f> values)
    {
        
    }
    
    void Appearance::GetMatrixArray (int nameID, std::vector<Matrix4x4f> values)
    {
        
    }
    
    
    Texture* Appearance::GetTexture (int nameID)
    {
        return mainTexture;
    }
    
    Texture* Appearance::GetTexture (const std::string& name)
    {
        return mainTexture;
    }
    
    Vector2f Appearance::GetTextureOffset (int nameID)
    {
        return mainTextureOffset;
    }
    
    Vector2f Appearance::GetTextureOffset (const std::string& name)
    {
        return mainTextureOffset;
    }
    
    Vector2f Appearance::GetTextureScale (const std::string& name)
    {
        return mainTextureScale;
    }
    
    Vector2f Appearance::GetTextureScale (int nameID)
    {
        return mainTextureScale;
    }
    
    
    
//    Vector4f Appearance::GetVector (const std::string& name)
//    {
//
//    }
//
//    Vector4f Appearance::GetVector (int nameID)
//    {
//
//    }
    
    void Appearance::GetVectorArray (int nameID, std::vector<Vector4f> values)
    {
        
    }
    
    void Appearance::GetVectorArray (const std::string& name, std::vector<Vector4f> values)
    {
        
    }
    
    
    //void SetBuffer (int nameID, ComputeBuffer value);
    //void SetBuffer (const string& name, ComputeBuffer value);
    
    void Appearance::SetColor (const std::string& name, Color value)
    {
        
    }
    
    void Appearance::SetColor (int nameID, Color value)
    {
        
    }
    
    void Appearance::SetColorArray (const std::string& name, std::vector<Color> values)
    {
        
    }
    
    void Appearance::SetColorArray (int nameID, std::vector<Color> values)
    {
        
    }
    
    
    void Appearance::SetFloat (int nameID, float value)
    {
        
    }
    
    void Appearance::SetFloat (const std::string& name, float value)
    {
        
    }
    
    void Appearance::SetFloatArray (int nameID, std::vector<float> values)
    {
        
    }
    
    void Appearance::SetFloatArray (const std::string& name, std::vector<float> values)
    {
        
    }
    
    
    void Appearance::SetInt (int nameID, int value)
    {
        
    }
    
    void Appearance::SetInt (const std::string& name, int value)
    {
        
    }
    
    
    void Appearance::SetMatrix (const std::string& name, const Matrix4x4f& value)
    {
        
    }
    
    void Appearance::SetMatrix (int nameID, const Matrix4x4f& value)
    {
        
    }
    
    void Appearance::SetMatrixArray (const std::string& name, std::vector<Matrix4x4f> values)
    {
        
    }
    
    void Appearance::SetMatrixArray (int nameID, std::vector<Matrix4x4f> values)
    {
        
    }
    
    
    void Appearance::SetTexture (const std::string& name, Texture* value)
    {
        
    }
    
    void Appearance::SetTexture (int nameID, Texture* value)
    {
        
    }
    
    void Appearance::SetTextureOffset (int nameID, Vector2f value)
    {
        
    }
    
    void Appearance::SetTextureOffset (const std::string& name, Vector2f value)
    {
        
    }
    
    void Appearance::SetTextureScale (int nameID, Vector2f value)
    {
        
    }
    
    void Appearance::SetTextureScale (const std::string& name, Vector2f value)
    {
        
    }
    
    
    void Appearance::SetVector (int nameID, Vector4f value)
    {
        
    }
    
    void Appearance::SetVector (const std::string& name, Vector4f value)
    {
        
    }
    
    void Appearance::SetVectorArray (const std::string& name, std::vector<Vector4f> values)
    {
        
    }
    
    void Appearance::SetVectorArray (int nameID, std::vector<Vector4f> values)
    {
        
    }
    
    
    bool Appearance::HasProperty (int nameID)
    {
        return false;
    }
    
    bool Appearance::HasProperty (const std::string& propertyName)
    {
        return false;
    }
    
    void Appearance::DisableKeyword (const std::string& keyword)
    {
        
    }
    
    void Appearance::EnableKeyword (const std::string& keyword)
    {
        
    }
    
    
    void Appearance::CopyPropertiesFromMaterial (const Appearance& mat)
    {
        
    }
    
    
}
