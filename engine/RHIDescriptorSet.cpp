#include "RHIDescriptorSet.h"

namespace pipeline {
    
    
    kRHIDescriptorSet::kRHIDescriptorSet()
    {
        
    }
    
    
    void kRHIDescriptorSet::Bind() const
    {
        
    }
    
    void kRHIDescriptorSet::Unbind() const
    {
        
    }
    
    
    std::string kRHIDescriptorSet::IDToProperty (int id)
    {
        return "";
    }
    
    bool kRHIDescriptorSet::IsKeywordEnabled (const std::string& keyword)
    {
        return false;
    }
    
    
    kColor kRHIDescriptorSet::GetGlobalColor (const std::string& name)
    {
        return kColor();
    }
    
    kColor kRHIDescriptorSet::GetGlobalColor (int nameID)
    {
        return kColor();
    }
    
    float kRHIDescriptorSet::GetGlobalFloat (int nameID)
    {
        return 0.0f;
    }
    
    float kRHIDescriptorSet::GetGlobalFloat (const std::string& name)
    {
        return 0.0f;
    }
    
    void kRHIDescriptorSet::GetGlobalFloatArray (int nameID, std::vector<float>& values)
    {
        
    }
    
    void kRHIDescriptorSet::GetGlobalFloatArray (const std::string& name, std::vector<float>& values)
    {
        
    }
    
    float* kRHIDescriptorSet::GetGlobalFloatArray (int nameID)
    {
        return NULL;
    }
    
    
    int kRHIDescriptorSet::GetGlobalInt (const std::string& name)
    {
        return 0;
    }
    
    int kRHIDescriptorSet::GetGlobalInt (int nameID)
    {
        return 0;
    }
    
    int kRHIDescriptorSet::GetGlobalIntImpl (int nameID)
    {
        return 0;
    }
    
    
    kMatrix4x4f kRHIDescriptorSet::GetGlobalMatrix (int nameID)
    {
        return kMatrix4x4f();
    }
    
    kMatrix4x4f kRHIDescriptorSet::GetGlobalMatrix (const std::string& name)
    {
        return kMatrix4x4f();
    }
    
    
    void kRHIDescriptorSet::GetGlobalMatrixArray (const std::string& name, std::vector<kMatrix4x4f>& values)
    {
        
    }
    
    kMatrix4x4f* kRHIDescriptorSet::GetGlobalMatrixArray (const std::string& name)
    {
        return NULL;
    }
    
    void kRHIDescriptorSet::GetGlobalMatrixArray (int nameID, std::vector<kMatrix4x4f>& values)
    {
        
    }
    
    kMatrix4x4f* kRHIDescriptorSet::GetGlobalMatrixArray (int nameID)
    {
        return NULL;
    }
    
    
    kTexture* kRHIDescriptorSet::GetGlobalTexture (int nameID)
    {
        return NULL;
    }
    
    kTexture* kRHIDescriptorSet::GetGlobalTexture (const std::string& name)
    {
        return NULL;
    }
    
    kVector4f kRHIDescriptorSet::GetGlobalVector (int nameID)
    {
        return kVector4f();
    }
    
    kVector4f kRHIDescriptorSet::GetGlobalVector (const std::string& name)
    {
        return kVector4f();
    }
    
    void kRHIDescriptorSet::GetGlobalVectorArray (const std::string& name, std::vector<kVector4f>& values)
    {
        
    }
    
    void kRHIDescriptorSet::GetGlobalVectorArray (int nameID, std::vector<kVector4f>& values)
    {
        
    }
    
    kVector4f* kRHIDescriptorSet::GetGlobalVectorArray (int nameID)
    {
        return NULL;
    }
    
    kVector4f* kRHIDescriptorSet::GetGlobalVectorArray (const std::string& name)
    {
        return NULL;
    }
    
    
    int kRHIDescriptorSet::PropertyToID (const std::string& name)
    {
        return 0;
    }
    
    void kRHIDescriptorSet::SetGlobalColor (const std::string& name, const kColor& value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalColor (int nameID, const kColor& value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalFloat (int nameID, float value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalFloat (const std::string& name, float value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalFloatArray (int nameID, std::vector<float>& values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalFloatArray (const std::string& name, std::vector<float>& values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalFloatArray (int nameID, float* values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalFloatArray (const std::string& name, float* values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalInt (const std::string& name, int value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalInt (int nameID, int value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalMatrix (const std::string& name, const kMatrix4x4f& value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalMatrix (int nameID, const kMatrix4x4f& value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalMatrixArray (int nameID, std::vector<kMatrix4x4f>& values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalMatrixArray (const std::string& name, std::vector<kMatrix4x4f>& values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalMatrixArray (const std::string& name, kMatrix4x4f* values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalMatrixArray (int nameID, kMatrix4x4f* values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalTexture (const std::string& name, kTexture* value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalVector (int nameID, const kVector4f& value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalVector (const std::string& name, const kVector4f& value)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalVectorArray (int nameID, std::vector<kVector4f>& values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalVectorArray (const std::string& name, std::vector<kVector4f>& values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalVectorArray (int nameID, kVector4f* values)
    {
        
    }
    
    void kRHIDescriptorSet::SetGlobalVectorArray (const std::string& name, kVector4f* values)
    {
        
    }
    
    
}
