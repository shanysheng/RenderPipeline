#include "Shader.h"

namespace pipeline {
    
    
    Shader::Shader()
    {
        
    }
    
    
    void Shader::Bind() const
    {
        
    }
    
    void Shader::Unbind() const
    {
        
    }
    
    
    std::string Shader::IDToProperty (int id)
    {
        return "";
    }
    
    bool Shader::IsKeywordEnabled (const std::string& keyword)
    {
        return false;
    }
    
    
    Color Shader::GetGlobalColor (const std::string& name)
    {
        return Color();
    }
    
    Color Shader::GetGlobalColor (int nameID)
    {
        return Color();
    }
    
    float Shader::GetGlobalFloat (int nameID)
    {
        return 0.0f;
    }
    
    float Shader::GetGlobalFloat (const std::string& name)
    {
        return 0.0f;
    }
    
    void Shader::GetGlobalFloatArray (int nameID, std::vector<float>& values)
    {
        
    }
    
    void Shader::GetGlobalFloatArray (const std::string& name, std::vector<float>& values)
    {
        
    }
    
    float* Shader::GetGlobalFloatArray (int nameID)
    {
        return NULL;
    }
    
    
    int Shader::GetGlobalInt (const std::string& name)
    {
        return 0;
    }
    
    int Shader::GetGlobalInt (int nameID)
    {
        return 0;
    }
    
    int Shader::GetGlobalIntImpl (int nameID)
    {
        return 0;
    }
    
    
    Matrix4x4f Shader::GetGlobalMatrix (int nameID)
    {
        return Matrix4x4f();
    }
    
    Matrix4x4f Shader::GetGlobalMatrix (const std::string& name)
    {
        return Matrix4x4f();
    }
    
    
    void Shader::GetGlobalMatrixArray (const std::string& name, std::vector<Matrix4x4f>& values)
    {
        
    }
    
    Matrix4x4f* Shader::GetGlobalMatrixArray (const std::string& name)
    {
        return NULL;
    }
    
    void Shader::GetGlobalMatrixArray (int nameID, std::vector<Matrix4x4f>& values)
    {
        
    }
    
    Matrix4x4f* Shader::GetGlobalMatrixArray (int nameID)
    {
        return NULL;
    }
    
    
    Texture* Shader::GetGlobalTexture (int nameID)
    {
        return NULL;
    }
    
    Texture* Shader::GetGlobalTexture (const std::string& name)
    {
        return NULL;
    }
    
    Vector4f Shader::GetGlobalVector (int nameID)
    {
        return Vector4f();
    }
    
    Vector4f Shader::GetGlobalVector (const std::string& name)
    {
        return Vector4f();
    }
    
    void Shader::GetGlobalVectorArray (const std::string& name, std::vector<Vector4f>& values)
    {
        
    }
    
    void Shader::GetGlobalVectorArray (int nameID, std::vector<Vector4f>& values)
    {
        
    }
    
    Vector4f* Shader::GetGlobalVectorArray (int nameID)
    {
        return NULL;
    }
    
    Vector4f* Shader::GetGlobalVectorArray (const std::string& name)
    {
        return NULL;
    }
    
    
    int Shader::PropertyToID (const std::string& name)
    {
        return 0;
    }
    
    void Shader::SetGlobalColor (const std::string& name, const Color& value)
    {
        
    }
    
    void Shader::SetGlobalColor (int nameID, const Color& value)
    {
        
    }
    
    void Shader::SetGlobalFloat (int nameID, float value)
    {
        
    }
    
    void Shader::SetGlobalFloat (const std::string& name, float value)
    {
        
    }
    
    void Shader::SetGlobalFloatArray (int nameID, std::vector<float>& values)
    {
        
    }
    
    void Shader::SetGlobalFloatArray (const std::string& name, std::vector<float>& values)
    {
        
    }
    
    void Shader::SetGlobalFloatArray (int nameID, float* values)
    {
        
    }
    
    void Shader::SetGlobalFloatArray (const std::string& name, float* values)
    {
        
    }
    
    void Shader::SetGlobalInt (const std::string& name, int value)
    {
        
    }
    
    void Shader::SetGlobalInt (int nameID, int value)
    {
        
    }
    
    void Shader::SetGlobalMatrix (const std::string& name, const Matrix4x4f& value)
    {
        
    }
    
    void Shader::SetGlobalMatrix (int nameID, const Matrix4x4f& value)
    {
        
    }
    
    void Shader::SetGlobalMatrixArray (int nameID, std::vector<Matrix4x4f>& values)
    {
        
    }
    
    void Shader::SetGlobalMatrixArray (const std::string& name, std::vector<Matrix4x4f>& values)
    {
        
    }
    
    void Shader::SetGlobalMatrixArray (const std::string& name, Matrix4x4f* values)
    {
        
    }
    
    void Shader::SetGlobalMatrixArray (int nameID, Matrix4x4f* values)
    {
        
    }
    
    void Shader::SetGlobalTexture (const std::string& name, Texture* value)
    {
        
    }
    
    void Shader::SetGlobalVector (int nameID, const Vector4f& value)
    {
        
    }
    
    void Shader::SetGlobalVector (const std::string& name, const Vector4f& value)
    {
        
    }
    
    void Shader::SetGlobalVectorArray (int nameID, std::vector<Vector4f>& values)
    {
        
    }
    
    void Shader::SetGlobalVectorArray (const std::string& name, std::vector<Vector4f>& values)
    {
        
    }
    
    void Shader::SetGlobalVectorArray (int nameID, Vector4f* values)
    {
        
    }
    
    void Shader::SetGlobalVectorArray (const std::string& name, Vector4f* values)
    {
        
    }
    
    
}
