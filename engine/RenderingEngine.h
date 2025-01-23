#ifndef PIPELINE_RENDERINGENGINE_H_GUARD
#define PIPELINE_RENDERINGENGINE_H_GUARD


#include "Common.h"

namespace pipeline {
    
    class IPreRender;
    class IRenderTarget;
    
    class kSGNode;
    class kScene;
    class kCamera;


    class kRenderQueueManager;
    class kCameraManager;
    class kRenderTargetManager;
    class kPreRenderManager;
    class kGPUResourceManager;
    class kRenderPipelineManager;
    
    class kWinInfo
    {
    public:
    };
    
    
    class kRenderingEngine
    {
    public:
        kRenderingEngine(void);
        virtual ~kRenderingEngine(void);
        
        virtual int Configure( const std::string& ConfigFileName );
        virtual int Initialize( const kWinInfo& WinInfo );
        virtual void Finalize();
        
        int OpenSceneModel( const std::string& SceneModelName, int ActiveSceneGraph =0 );
        void CloseSceneModel();
        
        void SetRenderTraverseRoot( const std::vector<kSGNode*>& roots );
        void SetCamera(kCamera& Camera );
        void GetCamera(kCamera& Camera );
        
        void ClearScreen(float r = 0.0f, float g = 0.3f, float b = 0.9f, float a = 0.0f);
        void DoRendering();
        void SwapBuffers();
        
        
    protected:

        kRenderQueueManager*					GetRenderQueueManager()		{return m_pRenderQueueMgr;}
        kCameraManager*							GetCameraManager()			{return m_pCameraMgr;}
        kRenderTargetManager*					GetRenderTargetManager()	{return m_pRenderTargetMgr;}
        kPreRenderManager*						GetPreRenderManager()		{return m_pPreRenderMgr;}
        kGPUResourceManager*				    GetGPUResourceManager()	{return m_pGPUResourceMpr;}
        kRenderPipelineManager*					GetRenderPipelineManager()	{return m_pRenderPipelineMgr;}
        
    protected:
        
        virtual int RegisterPreRenderPrototypes();
        virtual int RegisterRenderPipelinePrototypes();
        
        // user override functions
        virtual int OnConfigure();
        virtual int OnRegisterPreRenderPrototypes();
        virtual int OnRegisterRenderPipelinePrototypes();
        
        virtual void UpdateSynClockMillSecondTime();
        virtual void UpdateFrameIndex();
        
    protected:
        
        kWinInfo								m_WinInfo;
        
        kGPUResourceManager*				m_pGPUResourceMpr;
        
        kRenderQueueManager*   					m_pRenderQueueMgr;
        kCameraManager*							m_pCameraMgr;

        kRenderTargetManager*					m_pRenderTargetMgr;
        kPreRenderManager*						m_pPreRenderMgr;
        kRenderPipelineManager*					m_pRenderPipelineMgr;

        std::vector<kSGNode*>	                m_TraverseRoots;

        
        IPreRender*								m_pStartPreRender;
        IRenderTarget*						    m_pPrimeTarget;
    };

}

#endif
