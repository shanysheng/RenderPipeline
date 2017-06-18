/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */

#ifndef PIPELINE_APPEARANCE_H_GUARD
#define PIPELINE_APPEARANCE_H_GUARD

#include "Common.h"

namespace pipeline {
    
    class Appearance
    {
    public:
        Color color ;
        bool enableInstancing ;
        
        Texture mainTexture;
        Vector2 mainTextureOffset ;
        Vector2 mainTextureScale ;
        
        int passCount ;
        int renderQueue
        Shader shader
        
        Material (Material source);
        Material (Shader shader);
        
        void CopyPropertiesFromMaterial (Material mat);
        void DisableKeyword (string keyword);
        void EnableKeyword (string keyword);
        int FindPass (string passName);
        
        Color GetColor (string name);
        Color GetColor (int nameID);
        void GetColorArray (int nameID, std::vector<Color> values);
        void GetColorArray (string name, std::vector<Color> values);

        float GetFloat (string name);
        float GetFloat (int nameID);
        void GetFloatArray (int nameID, std::vector<float> values);
        void GetFloatArray (string name, std::vector<float> values);
        int GetInt (int nameID);
        int GetInt (string name);
        
        Matrix4x4 GetMatrix (string name);
        Matrix4x4 GetMatrix (int nameID);
        void GetMatrixArray (string name, std::vector<Matrix4x4> values);
        void GetMatrixArray (int nameID, std::vector<Matrix4x4> values);
        
        Texture GetTexture (int nameID);
        Texture GetTexture (string name);
        Vector2 GetTextureOffset (int nameID);
        Vector2 GetTextureOffset (string name);
        Vector2 GetTextureScale (string name);
        Vector2 GetTextureScale (int nameID);
        Vector4 GetVector (string name);
        Vector4 GetVector (int nameID);
        void GetVectorArray (int nameID, std::vector<Vector4> values);
        void GetVectorArray (string name, std::vector<Vector4> values);
        
        bool HasProperty (int nameID);
        bool HasProperty (string propertyName);
        
        void SetBuffer (int nameID, ComputeBuffer value);
        void SetBuffer (string name, ComputeBuffer value);
        
        void SetColor (string name, Color value);
        void SetColor (int nameID, Color value);
        void SetColorArray (string name, std::vector<Color> values);
        void SetColorArray (string name, Color[] values);
        void SetColorArray (int nameID, Color[] values);
        void SetColorArray (int nameID, std::vector<Color> values);
        
        void SetFloat (int nameID, float value);
        void SetFloat (string name, float value);
        void SetFloatArray (string name, float[] values);
        void SetFloatArray (int nameID, float[] values);
        void SetFloatArray (int nameID, std::vector<float> values);
        void SetFloatArray (string name, std::vector<float> values);
        
        void SetInt (int nameID, int value);
        void SetInt (string name, int value);
        
        void SetMatrix (string name, Matrix4x4 value);
        void SetMatrix (int nameID, Matrix4x4 value);
        void SetMatrixArray (string name, std::vector<Matrix4x4> values);
        void SetMatrixArray (int nameID, std::vector<Matrix4x4> values);
        void SetMatrixArray (string name, Matrix4x4[] values);
        void SetMatrixArray (int nameID, Matrix4x4[] values);
        
        void SetTexture (string name, Texture value);
        void SetTexture (int nameID, Texture value);
        void SetTextureOffset (int nameID, Vector2 value);
        void SetTextureOffset (string name, Vector2 value);
        void SetTextureScale (int nameID, Vector2 value);
        void SetTextureScale (string name, Vector2 value);
        
        void SetVector (int nameID, Vector4 value);
        void SetVector (string name, Vector4 value)
        void SetVectorArray (string name, Vector4[] values);
        void SetVectorArray (string name, std::vector<Vector4> values);
        void SetVectorArray (int nameID, Vector4[] values);
        void SetVectorArray (int nameID, std::vector<Vector4> values);
    };
}

#endif
