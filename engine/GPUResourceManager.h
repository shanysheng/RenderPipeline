/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_GPURESOURCEMANAGER_H_GUARD
#define PIPELINE_GPURESOURCEMANAGER_H_GUARD

#include "Common.h"

namespace pipeline {
    
    
    class GeometryBuffer;
    class Shader;
    class Texture;

    
    class CGPUResourceManipulator
    {
    public:
        CGPUResourceManipulator(void);
        virtual ~CGPUResourceManipulator(void);
        
        CGcontext GetCGContext();
        virtual void ClearResources();
        int32_t	TotoalMemoryCost() const;
        uint32_t FreeUnusedResource( SceneModel::IFeature * );
        
        
        IGPUResource*					GiveResource ( SceneModel::IFeature * );
        CImageTextureGPUResource*		GiveResource ( SceneModel::IImageEntity * );
        CImageTextureGPUResource*		GiveResource ( SceneModel::CImageTexture * );
        CCubeMapTextureGPUResource*		GiveResource ( SceneModel::CComposedCubeMapTexture *);
        GeometryBuffer*				GiveResource ( SceneModel::CIndexedTriangleSet * );
        
        CMovieTextureGPUResource*		GiveResource ( SceneModel::CMovieTexture * );
        CSkinShapeBufferGPUResource*	GiveResource ( SceneModel::CSkinShape*);
        
        // deprecated
        CCgProgramGPUResource*			GiveResource ( SceneModel::CShaderProgram * );
        
        bool UpdateResource(SceneModel::IFeature *pFeature);
        bool UpdateResource(SceneModel::CMovieTexture *pMovieTexture);
        bool UpdateResource(SceneModel::CImageTexture *pImageTexture);

        int32_t	EstimateMemoryCost( SceneModel::IFeature* );
        int32_t	EstimateMemoryCost( SceneModel::CImageTexture * );
        int32_t	EstimateMemoryCost( SceneModel::CMovieTexture * );
        int32_t	EstimateMemoryCost( SceneModel::CComposedCubeMapTexture * );
        int32_t	EstimateMemoryCost( SceneModel::CIndexedTriangleSet * );
        int32_t	EstimateMemoryCost( SceneModel::CShaderProgram * );
        int32_t	EstimateMemoryCost( SceneModel::CSkinShape*);
        
    protected:
        int		GetImageDataType( SceneModel::IImageEntity* pEntity);
        int		GetImageDataInternalFormat( SceneModel::IImageEntity* pEntity);
        
        void	BuildImageTexture(GLuint target, SceneModel::IImageEntity* pImageEntity);
        void    BuildSubImageTexture(GLuint target, SceneModel::IImageEntity* pImageEntity);
        
        void	CreateGPUResource(CImageTextureGPUResource* &pGPUResource, SceneModel::CImageTexture* pImageTexture);
        void	CreateGPUResource(CMovieTextureGPUResource* &pGPUResource, SceneModel::CMovieTexture* pMovieTexture);
        void	CreateGPUResource(CCubeMapTextureGPUResource* &pGPUResource, SceneModel::CComposedCubeMapTexture* pCubemapTexture);
        void	CreateGPUResource(GeometryBuffer* &pGPUResource, SceneModel::CIndexedTriangleSet* pIndexTriangleSet);
        void	CreateGPUResource(CSkinShapeBufferGPUResource*&pGPUResource,SceneModel::CSkinShape*pSkinShape);
        
        uint32_t GetGeometryBufferSize(const SceneModel::CIndexedTriangleSet* pGeometry);
        uint32_t GetGeometryBufferSize(const SceneModel::CSkinShape* pGeometry);
        
    protected:
        CGcontext           m_CGContext;
        
        int32_t64														m_TotalMemory;
        std::map<SceneModel::IFeature*, IGPUResource* >				m_Resources;
        
        SceneModel::SceneStorage::TPool<CCgProgramGPUResource>		m_CGGPUResourcePool;
        SceneModel::SceneStorage::TPool<GeometryBuffer>			m_VBUfferGPUResourcePool;
        SceneModel::SceneStorage::TPool<CImageTextureGPUResource>	m_ImageGPUResourcePool;
        SceneModel::SceneStorage::TPool<CMovieTextureGPUResource>	m_MovieGPUResourcePool;
        SceneModel::SceneStorage::TPool<CCubeMapTextureGPUResource>	m_CubeMapGPUResourcePool;
        
    private:
        bool _CheckArrayNoZero(GLuint*begin,GLuint*end);
    };
}

#endif
