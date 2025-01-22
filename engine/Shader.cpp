#include "Shader.h"

namespace pipeline {
    
    
    kShader::kShader()
    {
        
    }
    
    
    void kShader::Bind() const
    {
        
    }
    
    void kShader::Unbind() const
    {
        
    }
    
    
    std::string kShader::IDToProperty (int id)
    {
        return "";
    }
    
    bool kShader::IsKeywordEnabled (const std::string& keyword)
    {
        return false;
    }
    
    
    kColor kShader::GetGlobalColor (const std::string& name)
    {
        return kColor();
    }
    
    kColor kShader::GetGlobalColor (int nameID)
    {
        return kColor();
    }
    
    float kShader::GetGlobalFloat (int nameID)
    {
        return 0.0f;
    }
    
    float kShader::GetGlobalFloat (const std::string& name)
    {
        return 0.0f;
    }
    
    void kShader::GetGlobalFloatArray (int nameID, std::vector<float>& values)
    {
        
    }
    
    void kShader::GetGlobalFloatArray (const std::string& name, std::vector<float>& values)
    {
        
    }
    
    float* kShader::GetGlobalFloatArray (int nameID)
    {
        return NULL;
    }
    
    
    int kShader::GetGlobalInt (const std::string& name)
    {
        return 0;
    }
    
    int kShader::GetGlobalInt (int nameID)
    {
        return 0;
    }
    
    int kShader::GetGlobalIntImpl (int nameID)
    {
        return 0;
    }
    
    
    kMatrix4x4f kShader::GetGlobalMatrix (int nameID)
    {
        return kMatrix4x4f();
    }
    
    kMatrix4x4f kShader::GetGlobalMatrix (const std::string& name)
    {
        return kMatrix4x4f();
    }
    
    
    void kShader::GetGlobalMatrixArray (const std::string& name, std::vector<kMatrix4x4f>& values)
    {
        
    }
    
    kMatrix4x4f* kShader::GetGlobalMatrixArray (const std::string& name)
    {
        return NULL;
    }
    
    void kShader::GetGlobalMatrixArray (int nameID, std::vector<kMatrix4x4f>& values)
    {
        
    }
    
    kMatrix4x4f* kShader::GetGlobalMatrixArray (int nameID)
    {
        return NULL;
    }
    
    
    kTexture* kShader::GetGlobalTexture (int nameID)
    {
        return NULL;
    }
    
    kTexture* kShader::GetGlobalTexture (const std::string& name)
    {
        return NULL;
    }
    
    kVector4f kShader::GetGlobalVector (int nameID)
    {
        return kVector4f();
    }
    
    kVector4f kShader::GetGlobalVector (const std::string& name)
    {
        return kVector4f();
    }
    
    void kShader::GetGlobalVectorArray (const std::string& name, std::vector<kVector4f>& values)
    {
        
    }
    
    void kShader::GetGlobalVectorArray (int nameID, std::vector<kVector4f>& values)
    {
        
    }
    
    kVector4f* kShader::GetGlobalVectorArray (int nameID)
    {
        return NULL;
    }
    
    kVector4f* kShader::GetGlobalVectorArray (const std::string& name)
    {
        return NULL;
    }
    
    
    int kShader::PropertyToID (const std::string& name)
    {
        return 0;
    }
    
    void kShader::SetGlobalColor (const std::string& name, const kColor& value)
    {
        
    }
    
    void kShader::SetGlobalColor (int nameID, const kColor& value)
    {
        
    }
    
    void kShader::SetGlobalFloat (int nameID, float value)
    {
        
    }
    
    void kShader::SetGlobalFloat (const std::string& name, float value)
    {
        
    }
    
    void kShader::SetGlobalFloatArray (int nameID, std::vector<float>& values)
    {
        
    }
    
    void kShader::SetGlobalFloatArray (const std::string& name, std::vector<float>& values)
    {
        
    }
    
    void kShader::SetGlobalFloatArray (int nameID, float* values)
    {
        
    }
    
    void kShader::SetGlobalFloatArray (const std::string& name, float* values)
    {
        
    }
    
    void kShader::SetGlobalInt (const std::string& name, int value)
    {
        
    }
    
    void kShader::SetGlobalInt (int nameID, int value)
    {
        
    }
    
    void kShader::SetGlobalMatrix (const std::string& name, const kMatrix4x4f& value)
    {
        
    }
    
    void kShader::SetGlobalMatrix (int nameID, const kMatrix4x4f& value)
    {
        
    }
    
    void kShader::SetGlobalMatrixArray (int nameID, std::vector<kMatrix4x4f>& values)
    {
        
    }
    
    void kShader::SetGlobalMatrixArray (const std::string& name, std::vector<kMatrix4x4f>& values)
    {
        
    }
    
    void kShader::SetGlobalMatrixArray (const std::string& name, kMatrix4x4f* values)
    {
        
    }
    
    void kShader::SetGlobalMatrixArray (int nameID, kMatrix4x4f* values)
    {
        
    }
    
    void kShader::SetGlobalTexture (const std::string& name, kTexture* value)
    {
        
    }
    
    void kShader::SetGlobalVector (int nameID, const kVector4f& value)
    {
        
    }
    
    void kShader::SetGlobalVector (const std::string& name, const kVector4f& value)
    {
        
    }
    
    void kShader::SetGlobalVectorArray (int nameID, std::vector<kVector4f>& values)
    {
        
    }
    
    void kShader::SetGlobalVectorArray (const std::string& name, std::vector<kVector4f>& values)
    {
        
    }
    
    void kShader::SetGlobalVectorArray (int nameID, kVector4f* values)
    {
        
    }
    
    void kShader::SetGlobalVectorArray (const std::string& name, kVector4f* values)
    {
        
    }
    
    
}
