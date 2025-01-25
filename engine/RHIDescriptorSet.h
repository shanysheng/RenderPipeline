#ifndef PIPELINE_SHADER_H_GUARD
#define PIPELINE_SHADER_H_GUARD

#include "Common.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Color.h"
#include "Rect.h"
#include "Ray.h"

namespace pipeline {
    
    class kTexture;
    
    class kRHIDescriptorSet
    {
    public:
        kRHIDescriptorSet();
        
        virtual void Bind() const;
        virtual void Unbind() const;
        
        static std::string IDToProperty (int id);
        static bool IsKeywordEnabled (const std::string& keyword);
        
        static kColor GetGlobalColor (const std::string& name);
        static kColor GetGlobalColor (int nameID);
        static float GetGlobalFloat (int nameID);
        static float GetGlobalFloat (const std::string& name);
        static void GetGlobalFloatArray (int nameID, std::vector<float>& values);
        static void GetGlobalFloatArray (const std::string& name, std::vector<float>& values);
        static float* GetGlobalFloatArray (int nameID);
        
        static int GetGlobalInt (const std::string& name);
        static int GetGlobalInt (int nameID);
        static int GetGlobalIntImpl (int nameID);

        static kMatrix4x4f GetGlobalMatrix (int nameID);
        static kMatrix4x4f GetGlobalMatrix (const std::string& name);
        
        static void GetGlobalMatrixArray (const std::string& name, std::vector<kMatrix4x4f>& values);
        static kMatrix4x4f* GetGlobalMatrixArray (const std::string& name);
        static void GetGlobalMatrixArray (int nameID, std::vector<kMatrix4x4f>& values);
        static kMatrix4x4f* GetGlobalMatrixArray (int nameID);
        
        static kTexture* GetGlobalTexture (int nameID);
        static kTexture* GetGlobalTexture (const std::string& name);
        static kVector4f GetGlobalVector (int nameID);
        static kVector4f GetGlobalVector (const std::string& name);
        static void GetGlobalVectorArray (const std::string& name, std::vector<kVector4f>& values);
        static void GetGlobalVectorArray (int nameID, std::vector<kVector4f>& values);
        static kVector4f* GetGlobalVectorArray (int nameID);
        static kVector4f* GetGlobalVectorArray (const std::string& name);

        static int PropertyToID (const std::string& name);
        static void SetGlobalColor (const std::string& name, const kColor& value);
        static void SetGlobalColor (int nameID, const kColor& value);
        static void SetGlobalFloat (int nameID, float value);
        static void SetGlobalFloat (const std::string& name, float value);
        static void SetGlobalFloatArray (int nameID, std::vector<float>& values);
        static void SetGlobalFloatArray (const std::string& name, std::vector<float>& values);
        static void SetGlobalFloatArray (int nameID, float* values);
        static void SetGlobalFloatArray (const std::string& name, float* values);
        static void SetGlobalInt (const std::string& name, int value);
        static void SetGlobalInt (int nameID, int value);
        static void SetGlobalMatrix (const std::string& name, const kMatrix4x4f& value);
        static void SetGlobalMatrix (int nameID, const kMatrix4x4f& value);
        static void SetGlobalMatrixArray (int nameID, std::vector<kMatrix4x4f>& values);
        static void SetGlobalMatrixArray (const std::string& name, std::vector<kMatrix4x4f>& values);
        static void SetGlobalMatrixArray (const std::string& name, kMatrix4x4f* values);
        static void SetGlobalMatrixArray (int nameID, kMatrix4x4f* values);
        static void SetGlobalTexture (const std::string& name, kTexture* value);
        static void SetGlobalVector (int nameID, const kVector4f& value);
        static void SetGlobalVector (const std::string& name, const kVector4f& value);
        static void SetGlobalVectorArray (int nameID, std::vector<kVector4f>& values);
        static void SetGlobalVectorArray (const std::string& name, std::vector<kVector4f>& values);
        static void SetGlobalVectorArray (int nameID, kVector4f* values);
        static void SetGlobalVectorArray (const std::string& name, kVector4f* values);
        
    protected:
        
        //
        // Static Properties
        //
        static int globalMaximumLOD ;
        static const std::string& globalRenderPipeline;
        
        bool isSupported ;
        int maximumLOD;
        int renderQueue;

    };
}

#endif
