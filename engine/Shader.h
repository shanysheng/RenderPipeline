/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_SHADER_H_GUARD
#define PIPELINE_SHADER_H_GUARD

#include "

namespace pipeline {
    
    class Shader
    {
    public:
        
        
        virtual void Bind(  ) const;
        virtual void Bind() const;
        virtual void Unbind() const;
        
        //
        // Static Properties
        //
        static int globalMaximumLOD ;
        
        static const std::string& globalRenderPipeline;
        
        DisableBatchingType disableBatching ;
        
        bool isSupported ;
        
        int maximumLOD;
        
        int renderQueue
        
        static Color GetGlobalColor (const std::string& name);
        
        static Color GetGlobalColor (int nameID);
        
        static float GetGlobalFloat (int nameID);
        
        static float GetGlobalFloat (const std::string& name)
        ;
        
        static void GetGlobalFloatArray (int nameID, std::vector<float> values);
        
        static void GetGlobalFloatArray (const std::string& name, std::vector<float> values);
        static float[] GetGlobalFloatArray (int nameID)
        
        static int GetGlobalInt (const std::string& name);
        
        static int GetGlobalInt (int nameID);
        
        
        private static int GetGlobalIntImpl (int nameID);
        
        static Matrix4x4f GetGlobalMatrix (int nameID);
        
        static Matrix4x4f GetGlobalMatrix (const std::string& name);
        
        static void GetGlobalMatrixArray (const std::string& name, std::vector<Matrix4x4f> values);
        static Matrix4x4f[] GetGlobalMatrixArray (const std::string& name);
        static void GetGlobalMatrixArray (int nameID, std::vector<Matrix4x4f> values);
        
        static Matrix4x4f[] GetGlobalMatrixArray (int nameID);
        
        
        static Texture GetGlobalTexture (int nameID);
        
        static Texture GetGlobalTexture (const std::string& name);
        
        static Vector4 GetGlobalVector (int nameID);
        
        static Vector4 GetGlobalVector (const std::string& name);
        
        static void GetGlobalVectorArray (const std::string& name, std::vector<Vector4> values);
        
        static void GetGlobalVectorArray (int nameID, std::vector<Vector4> values);
        
        static Vector4[] GetGlobalVectorArray (int nameID);
        
        static Vector4[] GetGlobalVectorArray (const std::string& name);
        static const std::string& IDToProperty (int id);
      
        
        
        static bool IsKeywordEnabled (const std::string& keyword);
        
    
        static int PropertyToID (const std::string& name);
        
        
        
        static void SetGlobalBuffer (const std::string& name, ComputeBuffer buffer);
        
        static void SetGlobalColor (const std::string& name, Color value);
        
        static void SetGlobalColor (int nameID, Color value);
        
        static void SetGlobalFloat (int nameID, float value);
        
        static void SetGlobalFloat (const std::string& name, float value);
        
        static void SetGlobalFloatArray (int nameID, std::vector<float> values);
        
        static void SetGlobalFloatArray (const std::string& name, std::vector<float> values);
        
        static void SetGlobalFloatArray (int nameID, float[] values);
        
        static void SetGlobalFloatArray (const std::string& name, float[] values);
        static void SetGlobalInt (const std::string& name, int value);
        static void SetGlobalInt (int nameID, int value);
        
        static void SetGlobalMatrix (const std::string& name, Matrix4x4f value);
        
        static void SetGlobalMatrix (int nameID, Matrix4x4f value);
        
        static void SetGlobalMatrixArray (int nameID, std::vector<Matrix4x4f> values);
        static void SetGlobalMatrixArray (const std::string& name, std::vector<Matrix4x4f> values);
        
        static void SetGlobalMatrixArray (const std::string& name, Matrix4x4f[] values);
        static void SetGlobalMatrixArray (int nameID, Matrix4x4f[] values);
        static void SetGlobalTexture (const std::string& name, Texture value);
        
        static void SetGlobalVector (int nameID, Vector4 value);
        
        static void SetGlobalVector (const std::string& name, Vector4 value);
        
        static void SetGlobalVectorArray (int nameID, std::vector<Vector4> values);
        
        static void SetGlobalVectorArray (const std::string& name, std::vector<Vector4> values);
        
        static void SetGlobalVectorArray (int nameID, Vector4[] values);
        static void SetGlobalVectorArray (const std::string& name, Vector4[] values);
    };
}

#endif
