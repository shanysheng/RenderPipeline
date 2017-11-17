#include "Geometry.h"

namespace pipeline {
    
    
    Geometry::Geometry ()
    {
        
    }
    
    Geometry::~Geometry()
    {
        
    }
    
    int  Geometry::GetBindposeCount ()
    {
        return 0;
    }
    
    void Geometry::GetBindposes (std::vector<Matrix4x4f>& bindposes)
    {
        
    }
    
    
    const std::string Geometry::GetBlendShapeName (int shapeIndex)
    {
        return "";
    }
    
    int  Geometry::GetBlendShapeIndex (const std::string& blendShapeName)
    {
        return 0;
    }
    
    
    int  Geometry::GetBlendShapeFrameCount (int shapeIndex)
    {
        return 0;
    }
    
    void Geometry::GetBlendShapeFrameVertices (int shapeIndex, int frameIndex,
                                     Vector3f deltaVertices[],
                                     Vector3f deltaNormals[],
                                     Vector3f deltaTangents[])
    {
        
    }
    
    void Geometry::AddBlendShapeFrame (const std::string& shapeName,
                             float frameWeight,
                             Vector3f deltaVertices[],
                             Vector3f deltaNormals[],
                             Vector3f deltaTangents[])
    {
        
    }
    
    float Geometry::GetBlendShapeFrameWeight (int shapeIndex, int frameIndex)
    {
        return 0.0f;
    }
    
    void Geometry::GetBoneWeights (std::vector<BoneWeight>& boneWeights)
    {
        
    }
    
    bool Geometry::HasChannel (InternalShaderChannel channel)
    {
        return false;
    }
    
    
    uint32_t Geometry::GetIndexCount (int submesh)
    {
        return 0;
    }
    
    uint32_t Geometry::GetIndexStart (int submesh)
    {
        return 0;
    }
    
    int* Geometry::GetIndices (int submesh)
    {
        return NULL;
    }
    
    void Geometry::GetIndices (std::vector<int>& indices, int submesh)
    {
        
    }
    
    void Geometry::GetColors (std::vector<Color32>& colors)
    {
        
    }
    
    void Geometry::GetColors (std::vector<Color>& colors)
    {
        
    }
    
    void Geometry::GetNormals (std::vector<Vector3f>& normals)
    {
        
    }
    
    void Geometry::GetTangents (std::vector<Vector4f>& tangents)
    {
        
    }
    
    void Geometry::GetUVs (int channel, std::vector<Vector4f>& uvs)
    {
        
    }
    
    void Geometry::GetUVs (int channel, std::vector<Vector2f>& uvs)
    {
        
    }
    
    void Geometry::GetUVs (int channel, std::vector<Vector3f>& uvs)
    {
        
    }
    
    void Geometry::GetVertices (std::vector<Vector3f>& vertices)
    {
        
    }
    
    void Geometry::RecalculateBounds ()
    {
        
    }
    
    void Geometry::RecalculateNormals ()
    {
        
    }
    
    void Geometry::RecalculateTangents ()
    {
        
    }
    
    void Geometry::SetIndices (int indices[], int topology, int submesh)
    {
        
    }
    
    void Geometry::SetIndices (const std::vector<int>& triangles, int submesh)
    {
        
    }
    
    void Geometry::SetColors (const std::vector<Color>& inColors)
    {
        
    }
    
    void Geometry::SetColors (const std::vector<Color32>& inColors)
    {
        
    }
    
    void Geometry::SetNormals (const std::vector<Vector3f>& inNormals)
    {
        
    }
    
    void Geometry::SetTangents (const std::vector<Vector4f>& inTangents)
    {
        
    }
    
    void Geometry::SetTriangles (int triangles[], int submesh)
    {
        
    }
    
    void Geometry::SetUVs (int channel, const std::vector<Vector2f>& uvs)
    {
        
    }
    
    void Geometry::SetUVs (int channel, const std::vector<Vector3f>& uvs)
    {
        
    }
    
    void Geometry::SetUVs (int channel, const std::vector<Vector4f>& uvs)
    {
        
    }
    
    void Geometry::SetVertices (const std::vector<Vector3f>& inVertices)
    {
        
    }
    
    void Geometry::UploadMeshData (bool markNoLogerReadable)
    {
        
    }
}
