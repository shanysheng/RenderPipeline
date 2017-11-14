/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */

#ifndef PIPELINE_APPEARANCE_H_GUARD
#define PIPELINE_APPEARANCE_H_GUARD

#include "Common.h"
#include "IFeature.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

namespace pipeline {
    
    class Shader;
    class Texture;
    
    class Appearance : public IFeature
    {
    public:
        
        Appearance (const Appearance& source);
        Appearance (Shader*shader);
        
        const Color& GetColor (const std::string& name);
        const Color& GetColor (int nameID);
        void GetColorArray (int nameID, std::vector<Color> values);
        void GetColorArray (const std::string& name, std::vector<Color> values);
        
        float GetFloat (const std::string& name);
        float GetFloat (int nameID);
        void GetFloatArray (int nameID, std::vector<float> values);
        void GetFloatArray (const std::string& name, std::vector<float> values);
        
        int GetInt (int nameID);
        int GetInt (const std::string& name);
        
        const Matrix4x4f& GetMatrix (const std::string& name);
        const Matrix4x4f& GetMatrix (int nameID);
        void GetMatrixArray (const std::string& name, std::vector<Matrix4x4f> values);
        void GetMatrixArray (int nameID, std::vector<Matrix4x4f> values);
        
        Texture* GetTexture (int nameID);
        Texture* GetTexture (const std::string& name);
        Vector2f GetTextureOffset (int nameID);
        Vector2f GetTextureOffset (const std::string& name);
        Vector2f GetTextureScale (const std::string& name);
        Vector2f GetTextureScale (int nameID);
        
        Vector4f GetVector (const std::string& name);
        Vector4f GetVector (int nameID);
        void GetVectorArray (int nameID, std::vector<Vector4f> values);
        void GetVectorArray (const std::string& name, std::vector<Vector4f> values);
        
        //void SetBuffer (int nameID, ComputeBuffer value);
        //void SetBuffer (const string& name, ComputeBuffer value);
        
        void SetColor (const std::string& name, Color value);
        void SetColor (int nameID, Color value);
        void SetColorArray (const std::string& name, std::vector<Color> values);
        void SetColorArray (int nameID, std::vector<Color> values);
        
        void SetFloat (int nameID, float value);
        void SetFloat (const std::string& name, float value);
        void SetFloatArray (int nameID, std::vector<float> values);
        void SetFloatArray (const std::string& name, std::vector<float> values);
        
        void SetInt (int nameID, int value);
        void SetInt (const std::string& name, int value);
        
        void SetMatrix (const std::string& name, const Matrix4x4f& value);
        void SetMatrix (int nameID, const Matrix4x4f& value);
        void SetMatrixArray (const std::string& name, std::vector<Matrix4x4f> values);
        void SetMatrixArray (int nameID, std::vector<Matrix4x4f> values);
        
        void SetTexture (const std::string& name, Texture* value);
        void SetTexture (int nameID, Texture* value);
        void SetTextureOffset (int nameID, Vector2f value);
        void SetTextureOffset (const std::string& name, Vector2f value);
        void SetTextureScale (int nameID, Vector2f value);
        void SetTextureScale (const std::string& name, Vector2f value);
        
        void SetVector (int nameID, Vector4f value);
        void SetVector (const std::string& name, Vector4f value);
        void SetVectorArray (const std::string& name, std::vector<Vector4f> values);
        void SetVectorArray (int nameID, std::vector<Vector4f> values);
        
        bool HasProperty (int nameID);
        bool HasProperty (const std::string& propertyName);
        void DisableKeyword (const std::string& keyword);
        void EnableKeyword (const std::string& keyword);
        
        void CopyPropertiesFromMaterial (const Appearance& mat);
        //int FindPass (const string& passName);
    protected:
        Color color ;
        bool enableInstancing ;
        
        Shader*  shader;
        Texture* mainTexture;
        Vector2f mainTextureOffset ;
        Vector2f mainTextureScale ;
        
        int passCount ;
        int renderQueue;
    };
}

#endif
