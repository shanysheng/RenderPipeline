/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */

#ifndef PIPELINE_APPEARANCE_H_GUARD
#define PIPELINE_APPEARANCE_H_GUARD

#include "Common.h"
#include "IFeature.h"

namespace pipeline {
    
    class Shader;
    class Texture;
    
    class Appearance : public IFeature
    {
    public:
        
        Appearance (const Appearance& source);
        Appearance (Shader*shader);
        
        const Color& GetColor (const string& name);
        const Color& GetColor (int nameID);
        void GetColorArray (int nameID, std::vector<Color> values);
        void GetColorArray (const string& name, std::vector<Color> values);
        
        float GetFloat (const string& name);
        float GetFloat (int nameID);
        void GetFloatArray (int nameID, std::vector<float> values);
        void GetFloatArray (const string& name, std::vector<float> values);
        
        int GetInt (int nameID);
        int GetInt (const string& name);
        
        const Matrix4x4& GetMatrix (const string& name);
        const Matrix4x4& GetMatrix (int nameID);
        void GetMatrixArray (const string& name, std::vector<Matrix4x4> values);
        void GetMatrixArray (int nameID, std::vector<Matrix4x4> values);
        
        Texture GetTexture (int nameID);
        Texture GetTexture (const string& name);
        Vector2 GetTextureOffset (int nameID);
        Vector2 GetTextureOffset (const string& name);
        Vector2 GetTextureScale (const string& name);
        Vector2 GetTextureScale (int nameID);
        
        Vector4 GetVector (const string& name);
        Vector4 GetVector (int nameID);
        void GetVectorArray (int nameID, std::vector<Vector4> values);
        void GetVectorArray (const string& name, std::vector<Vector4> values);
        
        //void SetBuffer (int nameID, ComputeBuffer value);
        //void SetBuffer (const string& name, ComputeBuffer value);
        
        void SetColor (const string& name, Color value);
        void SetColor (int nameID, Color value);
        void SetColorArray (const string& name, std::vector<Color> values);
        void SetColorArray (int nameID, std::vector<Color> values);
        
        void SetFloat (int nameID, float value);
        void SetFloat (const string& name, float value);
        void SetFloatArray (int nameID, std::vector<float> values);
        void SetFloatArray (const string& name, std::vector<float> values);
        
        void SetInt (int nameID, int value);
        void SetInt (const string& name, int value);
        
        void SetMatrix (const string& name, const Matrix4x4& value);
        void SetMatrix (int nameID, const Matrix4x4& value);
        void SetMatrixArray (const string& name, std::vector<Matrix4x4> values);
        void SetMatrixArray (int nameID, std::vector<Matrix4x4> values);
        
        void SetTexture (const string& name, Texture value);
        void SetTexture (int nameID, Texture value);
        void SetTextureOffset (int nameID, Vector2 value);
        void SetTextureOffset (const string& name, Vector2 value);
        void SetTextureScale (int nameID, Vector2 value);
        void SetTextureScale (const string& name, Vector2 value);
        
        void SetVector (int nameID, Vector4 value);
        void SetVector (const string& name, Vector4 value)
        void SetVectorArray (const string& name, std::vector<Vector4> values);
        void SetVectorArray (int nameID, std::vector<Vector4> values);
        
        bool HasProperty (int nameID);
        bool HasProperty (const string& propertyName);
        void DisableKeyword (const string& keyword);
        void EnableKeyword (const string& keyword);
        
        void CopyPropertiesFromMaterial (const Appearance& mat);
        //int FindPass (const string& passName);
    protected:
        Color color ;
        bool enableInstancing ;
        
        Shader*  shader
        Texture* mainTexture;
        Vector2 mainTextureOffset ;
        Vector2 mainTextureScale ;
        
        int passCount ;
        int renderQueue;
    };
}

#endif
