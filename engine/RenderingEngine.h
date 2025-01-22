/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_RENDERINGENGINE_H_GUARD
#define PIPELINE_RENDERINGENGINE_H_GUARD


#include "Common.h"

namespace pipeline {
    
    
    class kSGNode;
    class kScene;
    class CCamera;
    class IPreRender;
    class CLocalClock;
    class CSynClock;
    
    class IRenderTarget;
    class kRenderQueueManager;
    class kCameraManager;
    class kRenderTargetManager;
    class kPreRenderManager;
    class kGPUResourceManipulator;
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
        void SetCamera(CCamera& Camera );
        void GetCamera( CCamera& Camera );
        
        void ClearScreen(float r = 0.0f, float g = 0.3f, float b = 0.9f, float a = 0.0f);
        void DoRendering();
        void SwapBuffers();
        
        void SetSetupTimeBudget(double);
        void SetDrawingTimeBudget(double);
        void SetGPUMemoryBudget(int32_t);
        void SetExtraRenderingObjectBudget(int32_t);
        
        double GetSetupTimeBudget();
        double GetDrawingTimeBudget();
        int32_t GetGPUMemoryBudget();
        int32_t GetExtraRenderingObjectBudget();
        
    protected:

        kRenderQueueManager*					GetRenderQueueManager()		{return m_pRenderQueueMgr;}
        kCameraManager*							GetCameraManager()			{return m_pCameraMgr;}
        kRenderTargetManager*					GetRenderTargetManager()	{return m_pRenderTargetMgr;}
        kPreRenderManager*						GetPreRenderManager()		{return m_pPreRenderMgr;}
        kGPUResourceManipulator*				GetGPUResourceManipulator()	{return m_pGPUResourceMpr;}
        kRenderPipelineManager*					GetRenderPipelineManager()	{return m_pRenderPipelineMgr;}
        CLocalClock*							GetLocalClock()				{return m_pLocalClock;}
        CSynClock*								GetSynClock()				{return m_pSynClock;}
        
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
        
        kGPUResourceManipulator*				m_pGPUResourceMpr;
        
        kRenderQueueManager*   					m_pRenderQueueMgr;
        kCameraManager*							m_pCameraMgr;

        kRenderTargetManager*					m_pRenderTargetMgr;
        kPreRenderManager*						m_pPreRenderMgr;
        kRenderPipelineManager*					m_pRenderPipelineMgr;

        std::vector<kSGNode*>	                m_TraverseRoots;

        CLocalClock*							m_pLocalClock;

        CSynClock*								m_pSynClock;
        
        //CFrameInfo							m_FrameInfo;
        
        IPreRender*								m_pStartPreRender;
        IRenderTarget*						    m_pPrimeTarget;
    };

}

#endif
