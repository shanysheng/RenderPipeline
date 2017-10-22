/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_GEOMETRY_H_GUARD
#define PIPELINE_GEOMETRY_H_GUARD

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
    
    enum InternalVertexChannelType
    {
        Float,
        Color = 2
    };
    
    class Geometry
    {
        int subMeshCount ;
        
        Matrix4x4f[] bindposes;
        BoneWeight[] boneWeights ;

        int blendShapeCount ;
        Bounds bounds;
        
        Color[] colors ;
        Color32[] colors32 ;
        Vector3f[] normals ;
        Vector4[] tangents;
        int[] triangles ;
        Vector2[] uv ;
        Vector2[] uv2;
        Vector2[] uv3;
        Vector2[] uv4 ;
        
        int vertexBufferCount;
        int vertexCount ;
        Vector3f[] vertices ;
        
        Geometry ()
        {
        }
 
        Create ();
        
        void AddBlendShapeFrame (const std::string& shapeName, float frameWeight, Vector3f[] deltaVertices, Vector3f[] deltaNormals, Vector3f[] deltaTangents);
        
        void CombineMeshes (CombineInstance[] combine, bool mergeSubMeshes);
        void MarkDynamic ();
        void Optimize ();
        void Clear ();
        
        void PrepareUserBuffer<T> (std::vector<T> buffer, int capacity);
        
        bool HasChannel (Mesh.InternalShaderChannel channel);
        int GetBindposeCount ();
        void GetBindposes (std::vector<Matrix4x4f> bindposes);
        void GetBindposesNonAllocImpl (object values);
        int GetBlendShapeFrameCount (int shapeIndex);
        void GetBlendShapeFrameVertices (int shapeIndex, int frameIndex, Vector3f[] deltaVertices, Vector3f[] deltaNormals, Vector3f[] deltaTangents);
        float GetBlendShapeFrameWeight (int shapeIndex, int frameIndex);
        int GetBlendShapeIndex (const std::string& blendShapeName);
        const std::string& GetBlendShapeName (int shapeIndex);
        void GetBoneWeights (std::vector<BoneWeight> boneWeights);
        
        void GetColors (std::vector<Color32> colors);
        void GetColors (std::vector<Color> colors);
        uint GetIndexCount (int submesh);
        uint GetIndexStart (int submesh);
        int[] GetIndices (int submesh);
        void GetIndices (std::vector<int> indices, int submesh);
        void GetNormals (std::vector<Vector3f> normals);
        void GetTangents (std::vector<Vector4> tangents);
        int[] GetTriangles (int submesh);
        void GetTriangles (std::vector<int> triangles, int submesh);
        void GetUVs (int channel, std::vector<Vector4> uvs);
        void GetUVs (int channel, std::vector<Vector2> uvs);
        void GetUVs (int channel, std::vector<Vector3f> uvs);
        void GetVertices (std::vector<Vector3f> vertices)
        
        void RecalculateBounds ();
        void RecalculateNormals ();
        void RecalculateTangents ();
        
        void SetSizedArrayForChannel();
        
        void SetColors (std::vector<Color> inColors);
        void SetColors (std::vector<Color32> inColors);
        void SetIndices (int[] indices, MeshTopology topology, int submesh);
        void SetNormals (std::vector<Vector3f> inNormals);
        void SetTangents (std::vector<Vector4> inTangents);
        void SetTriangles (int[] triangles, int submesh);
        void SetTriangles (std::vector<int> triangles, int submesh);
        void SetUVs (int channel, std::vector<Vector2> uvs);
        void SetUVs (int channel, std::vector<Vector3f> uvs);
        void SetUVs (int channel, std::vector<Vector4> uvs);
        void SetVertices (std::vector<Vector3f> inVertices);

        void UploadMeshData (bool markNoLogerReadable);
    };
}

#endif
