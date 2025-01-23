#ifndef PIPELINE_APPEARANCE_H_GUARD
#define PIPELINE_APPEARANCE_H_GUARD

#include "Common.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

namespace pipeline {
    
    class kShader;
    class kTexture;
    
    class kMaterial
    {
    public:
        
        kMaterial(const kMaterial& source);
        kMaterial(kShader*shader);
        
        const kColor& GetColor (const std::string& name);
        const kColor& GetColor (int nameID);
        void GetColorArray (int nameID, std::vector<kColor> values);
        void GetColorArray (const std::string& name, std::vector<kColor> values);
        
        float GetFloat (const std::string& name);
        float GetFloat (int nameID);
        void GetFloatArray (int nameID, std::vector<float> values);
        void GetFloatArray (const std::string& name, std::vector<float> values);
        
        int GetInt (int nameID);
        int GetInt (const std::string& name);
        
        const kMatrix4x4f& GetMatrix (const std::string& name);
        const kMatrix4x4f& GetMatrix (int nameID);
        void GetMatrixArray (const std::string& name, std::vector<kMatrix4x4f> values);
        void GetMatrixArray (int nameID, std::vector<kMatrix4x4f> values);
        
        kTexture* GetTexture (int nameID);
        kTexture* GetTexture (const std::string& name);
        kVector2f GetTextureOffset (int nameID);
        kVector2f GetTextureOffset (const std::string& name);
        kVector2f GetTextureScale (const std::string& name);
        kVector2f GetTextureScale (int nameID);
        
        kVector4f GetVector (const std::string& name);
        kVector4f GetVector (int nameID);
        void GetVectorArray (int nameID, std::vector<kVector4f> values);
        void GetVectorArray (const std::string& name, std::vector<kVector4f> values);
        
        //void SetBuffer (int nameID, ComputeBuffer value);
        //void SetBuffer (const string& name, ComputeBuffer value);
        
        void SetColor (const std::string& name, kColor value);
        void SetColor (int nameID, kColor value);
        void SetColorArray (const std::string& name, std::vector<kColor> values);
        void SetColorArray (int nameID, std::vector<kColor> values);
        
        void SetFloat (int nameID, float value);
        void SetFloat (const std::string& name, float value);
        void SetFloatArray (int nameID, std::vector<float> values);
        void SetFloatArray (const std::string& name, std::vector<float> values);
        
        void SetInt (int nameID, int value);
        void SetInt (const std::string& name, int value);
        
        void SetMatrix (const std::string& name, const kMatrix4x4f& value);
        void SetMatrix (int nameID, const kMatrix4x4f& value);
        void SetMatrixArray (const std::string& name, std::vector<kMatrix4x4f> values);
        void SetMatrixArray (int nameID, std::vector<kMatrix4x4f> values);
        
        void SetTexture (const std::string& name, kTexture* value);
        void SetTexture (int nameID, kTexture* value);
        void SetTextureOffset (int nameID, kVector2f value);
        void SetTextureOffset (const std::string& name, kVector2f value);
        void SetTextureScale (int nameID, kVector2f value);
        void SetTextureScale (const std::string& name, kVector2f value);
        
        void SetVector (int nameID, kVector4f value);
        void SetVector (const std::string& name, kVector4f value);
        void SetVectorArray (const std::string& name, std::vector<kVector4f> values);
        void SetVectorArray (int nameID, std::vector<kVector4f> values);
        
        bool HasProperty (int nameID);
        bool HasProperty (const std::string& propertyName);
        void DisableKeyword (const std::string& keyword);
        void EnableKeyword (const std::string& keyword);
        
        void CopyPropertiesFromMaterial (const kMaterial& mat);
        //int FindPass (const string& passName);
    protected:
        kColor color ;
        bool enableInstancing ;
        
        kShader*  shader;
        kTexture* mainTexture;
        kVector2f mainTextureOffset ;
        kVector2f mainTextureScale ;
        
        int passCount ;
        int renderQueue;
    };
}

#endif
