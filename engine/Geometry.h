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
        Vertex,
        Normal,
        Color,
        TexCoord0,
        TexCoord1,
        TexCoord2,
        TexCoord3,
        Tangent
    };
    
    struct BoneWeight
    {
        
    };
    
    class Geometry
    {
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
        
        Geometry ()
        {
        }
        
        
        void AddBlendShapeFrame (const std::string& shapeName, float frameWeight, Vector3f deltaVertices[], Vector3f deltaNormals[], Vector3f deltaTangents[]);
        
        void MarkDynamic ();
        void Optimize ();
        void Clear ();
        
        
        bool HasChannel (InternalShaderChannel channel);
        int GetBindposeCount ();
        void GetBindposes (std::vector<Matrix4x4f> bindposes);
        int GetBlendShapeFrameCount (int shapeIndex);
        void GetBlendShapeFrameVertices (int shapeIndex, int frameIndex, Vector3f deltaVertices[], Vector3f deltaNormals[], Vector3f deltaTangents[]);
        float GetBlendShapeFrameWeight (int shapeIndex, int frameIndex);
        int GetBlendShapeIndex (const std::string& blendShapeName);
        const std::string& GetBlendShapeName (int shapeIndex);
        void GetBoneWeights (std::vector<BoneWeight> boneWeights);
        
        void GetColors (std::vector<Color32> colors);
        //void GetColors (std::vector<Color> colors);
        uint32_t GetIndexCount (int submesh);
        uint32_t GetIndexStart (int submesh);
        int* GetIndices (int submesh);
        void GetIndices (std::vector<int> indices, int submesh);
        void GetNormals (std::vector<Vector3f> normals);
        void GetTangents (std::vector<Vector4f> tangents);
        int* GetTriangles (int submesh);
        void GetTriangles (std::vector<int> triangles, int submesh);
        void GetUVs (int channel, std::vector<Vector4f> uvs);
        void GetUVs (int channel, std::vector<Vector2f> uvs);
        void GetUVs (int channel, std::vector<Vector3f> uvs);
        void GetVertices (std::vector<Vector3f> vertices);
        
        void RecalculateBounds ();
        void RecalculateNormals ();
        void RecalculateTangents ();
        
        void SetSizedArrayForChannel();
        
        //void SetColors (std::vector<Color> inColors);
        void SetColors (std::vector<Color32> inColors);
        void SetIndices (int indices[], int topology, int submesh);
        void SetNormals (std::vector<Vector3f> inNormals);
        void SetTangents (std::vector<Vector4f> inTangents);
        void SetTriangles (int triangles[], int submesh);
        void SetTriangles (std::vector<int> triangles, int submesh);
        void SetUVs (int channel, std::vector<Vector2f> uvs);
        void SetUVs (int channel, std::vector<Vector3f> uvs);
        void SetUVs (int channel, std::vector<Vector4f> uvs);
        void SetVertices (std::vector<Vector3f> inVertices);
        
        void UploadMeshData (bool markNoLogerReadable);
    };
}

#endif
