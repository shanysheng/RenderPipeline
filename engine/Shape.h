/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_SHAPE_H_GUARD
#define PIPELINE_SHAPE_H_GUARD

namespace pipeline {
    
    class Shape
    {
    public:
        
        bool isVisible ;
        
        bool isPartOfStaticBatch ;
        int staticBatchIndex ;

        int lightmapIndex ;
        Vector4 lightmapScaleOffset ;
       
        Material material ;
        Material[] materials ;
        
        bool receiveShadows ;
        ReflectionProbeUsage reflectionProbeUsage ;
        ShadowCastingMode shadowCastingMode ;

        Material sharedMaterial;
        Material[] sharedMaterials ;

        int sortingGroupID ;
        int sortingGroupOrder;
        int sortingLayerID ;
        string sortingLayerName;
        int sortingOrder ;
        
        Bounds bounds ;
        Transform staticBatchRootTransform;
        
        Matrix4x4f localToWorldMatrix ;
        Matrix4x4f worldToLocalMatrix;
        
        void GetClosestReflectionProbes (std::vector<ReflectionProbeBlendInfo> result);
       
        void RenderNow (int material);
        void SetPropertyBlock (MaterialPropertyBlock properties);
        void SetStaticBatchInfo (int firstSubMesh, int subMeshCount);
    };
}

#endif
