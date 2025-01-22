#include "Material.h"

namespace pipeline {
    
    kMaterial::kMaterial(const kMaterial& source)
    {
        
    }
    
    kMaterial::kMaterial(kShader*shader)
    {
        
    }
    
    
    const kColor& kMaterial::GetColor (const std::string& name)
    {
        return color;
    }
    
    const kColor& kMaterial::GetColor (int nameID)
    {
        return color;
    }
    
    void kMaterial::GetColorArray (int nameID, std::vector<kColor> values)
    {
        
    }
    
    void kMaterial::GetColorArray (const std::string& name, std::vector<kColor> values)
    {
        
    }
    
    
    float kMaterial::GetFloat (const std::string& name)
    {
        return 0.0f;
    }
    
    float kMaterial::GetFloat (int nameID)
    {
        return 0.0f;
    }
    
    void kMaterial::GetFloatArray (int nameID, std::vector<float> values)
    {
        
    }
    
    void kMaterial::GetFloatArray (const std::string& name, std::vector<float> values)
    {
        
    }
    
    
    int kMaterial::GetInt (int nameID)
    {
        return 0;
    }
    
    int kMaterial::GetInt (const std::string& name)
    {
        return 0;
    }
    
    
//    const kMatrix4x4f& kMaterial::GetMatrix (const std::string& name)
//    {
//    }
//
//    const kMatrix4x4f& kMaterial::GetMatrix (int nameID)
//    {
//    }
    
    void kMaterial::GetMatrixArray (const std::string& name, std::vector<kMatrix4x4f> values)
    {
        
    }
    
    void kMaterial::GetMatrixArray (int nameID, std::vector<kMatrix4x4f> values)
    {
        
    }
    
    
    kTexture* kMaterial::GetTexture (int nameID)
    {
        return mainTexture;
    }
    
    kTexture* kMaterial::GetTexture (const std::string& name)
    {
        return mainTexture;
    }
    
    kVector2f kMaterial::GetTextureOffset (int nameID)
    {
        return mainTextureOffset;
    }
    
    kVector2f kMaterial::GetTextureOffset (const std::string& name)
    {
        return mainTextureOffset;
    }
    
    kVector2f kMaterial::GetTextureScale (const std::string& name)
    {
        return mainTextureScale;
    }
    
    kVector2f kMaterial::GetTextureScale (int nameID)
    {
        return mainTextureScale;
    }
    
    
    
//    kVector4f kMaterial::GetVector (const std::string& name)
//    {
//
//    }
//
//    kVector4f kMaterial::GetVector (int nameID)
//    {
//
//    }
    
    void kMaterial::GetVectorArray (int nameID, std::vector<kVector4f> values)
    {
        
    }
    
    void kMaterial::GetVectorArray (const std::string& name, std::vector<kVector4f> values)
    {
        
    }
    
    
    //void SetBuffer (int nameID, ComputeBuffer value);
    //void SetBuffer (const string& name, ComputeBuffer value);
    
    void kMaterial::SetColor (const std::string& name, kColor value)
    {
        
    }
    
    void kMaterial::SetColor (int nameID, kColor value)
    {
        
    }
    
    void kMaterial::SetColorArray (const std::string& name, std::vector<kColor> values)
    {
        
    }
    
    void kMaterial::SetColorArray (int nameID, std::vector<kColor> values)
    {
        
    }
    
    
    void kMaterial::SetFloat (int nameID, float value)
    {
        
    }
    
    void kMaterial::SetFloat (const std::string& name, float value)
    {
        
    }
    
    void kMaterial::SetFloatArray (int nameID, std::vector<float> values)
    {
        
    }
    
    void kMaterial::SetFloatArray (const std::string& name, std::vector<float> values)
    {
        
    }
    
    
    void kMaterial::SetInt (int nameID, int value)
    {
        
    }
    
    void kMaterial::SetInt (const std::string& name, int value)
    {
        
    }
    
    
    void kMaterial::SetMatrix (const std::string& name, const kMatrix4x4f& value)
    {
        
    }
    
    void kMaterial::SetMatrix (int nameID, const kMatrix4x4f& value)
    {
        
    }
    
    void kMaterial::SetMatrixArray (const std::string& name, std::vector<kMatrix4x4f> values)
    {
        
    }
    
    void kMaterial::SetMatrixArray (int nameID, std::vector<kMatrix4x4f> values)
    {
        
    }
    
    
    void kMaterial::SetTexture (const std::string& name, kTexture* value)
    {
        
    }
    
    void kMaterial::SetTexture (int nameID, kTexture* value)
    {
        
    }
    
    void kMaterial::SetTextureOffset (int nameID, kVector2f value)
    {
        
    }
    
    void kMaterial::SetTextureOffset (const std::string& name, kVector2f value)
    {
        
    }
    
    void kMaterial::SetTextureScale (int nameID, kVector2f value)
    {
        
    }
    
    void kMaterial::SetTextureScale (const std::string& name, kVector2f value)
    {
        
    }
    
    
    void kMaterial::SetVector (int nameID, kVector4f value)
    {
        
    }
    
    void kMaterial::SetVector (const std::string& name, kVector4f value)
    {
        
    }
    
    void kMaterial::SetVectorArray (const std::string& name, std::vector<kVector4f> values)
    {
        
    }
    
    void kMaterial::SetVectorArray (int nameID, std::vector<kVector4f> values)
    {
        
    }
    
    
    bool kMaterial::HasProperty (int nameID)
    {
        return false;
    }
    
    bool kMaterial::HasProperty (const std::string& propertyName)
    {
        return false;
    }
    
    void kMaterial::DisableKeyword (const std::string& keyword)
    {
        
    }
    
    void kMaterial::EnableKeyword (const std::string& keyword)
    {
        
    }
    
    
    void kMaterial::CopyPropertiesFromMaterial (const kMaterial& mat)
    {
        
    }
    
    
}
