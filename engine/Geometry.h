/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */

#ifndef PIPELINE_GEOMETRY_H_GUARD
#define PIPELINE_GEOMETRY_H_GUARD

#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Bound.h"

namespace pipeline {
    
    //
    // Nested Types
    //
    enum InternalShaderChannel
    {
        ShaderChannel_Vertex,
        ShaderChannel_Normal,
        ShaderChannel_Color,
        ShaderChannel_TexCoord0,
        ShaderChannel_TexCoord1,
        ShaderChannel_TexCoord2,
        ShaderChannel_TexCoord3,
        ShaderChannel_Tangent
    };
    
    struct BoneWeight
    {
        
    };
    
    class Geometry
    {
    public:
        
        Geometry ();
        ~Geometry();
        
        

        
        
        int  GetBindposeCount ();
        void GetBindposes (std::vector<Matrix4x4f>& bindposes);
        
        const std::string GetBlendShapeName (int shapeIndex);
        int  GetBlendShapeIndex (const std::string& blendShapeName);

        int  GetBlendShapeFrameCount (int shapeIndex);
        void GetBlendShapeFrameVertices (int shapeIndex, int frameIndex,
                                         Vector3f deltaVertices[],
                                         Vector3f deltaNormals[],
                                         Vector3f deltaTangents[]);
        void AddBlendShapeFrame (const std::string& shapeName,
                                 float frameWeight,
                                 Vector3f deltaVertices[],
                                 Vector3f deltaNormals[],
                                 Vector3f deltaTangents[]);
        
        float GetBlendShapeFrameWeight (int shapeIndex, int frameIndex);
        void GetBoneWeights (std::vector<BoneWeight>& boneWeights);
        
        bool HasChannel (InternalShaderChannel channel);

        uint32_t GetIndexCount (int submesh);
        uint32_t GetIndexStart (int submesh);
        int* GetIndices (int submesh);
        void GetIndices (std::vector<int>& indices, int submesh);
        void GetColors (std::vector<Color32>& colors);
        void GetColors (std::vector<Color>& colors);
        void GetNormals (std::vector<Vector3f>& normals);
        void GetTangents (std::vector<Vector4f>& tangents);
        void GetUVs (int channel, std::vector<Vector4f>& uvs);
        void GetUVs (int channel, std::vector<Vector2f>& uvs);
        void GetUVs (int channel, std::vector<Vector3f>& uvs);
        void GetVertices (std::vector<Vector3f>& vertices);
        
        void RecalculateBounds ();
        void RecalculateNormals ();
        void RecalculateTangents ();
        
        void SetIndices (int indices[], int topology, int submesh);
        void SetIndices (const std::vector<int>& triangles, int submesh);
        void SetColors (const std::vector<Color>& inColors);
        void SetColors (const std::vector<Color32>& inColors);
        void SetNormals (const std::vector<Vector3f>& inNormals);
        void SetTangents (const std::vector<Vector4f>& inTangents);
        void SetTriangles (int triangles[], int submesh);
        void SetUVs (int channel, const std::vector<Vector2f>& uvs);
        void SetUVs (int channel, const std::vector<Vector3f>& uvs);
        void SetUVs (int channel, const std::vector<Vector4f>& uvs);
        void SetVertices (const std::vector<Vector3f>& inVertices);
        
        void UploadMeshData (bool markNoLogerReadable);
        
    protected:
        int subMeshCount ;
        
        Matrix4x4f* bindposes;
        BoneWeight* boneWeights ;
        
        int blendShapeCount ;
        Bound bounds;
        
        //Color*      colors ;
        Color32*    colors32 ;
        Vector3f*   normals ;
        Vector4f*   tangents;
        Vector2f*   uv ;
        Vector2f*   uv2;
        Vector2f*   uv3;
        Vector2f*   uv4 ;
        
        int*         triangles ;
        
        int vertexBufferCount;
        int vertexCount ;
        Vector3f* vertices ;
    };
}

#endif
