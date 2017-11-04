/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_RENDERINGENGINE_H_GUARD
#define PIPELINE_RENDERINGENGINE_H_GUARD


#include "Common.h"

namespace pipeline {
    
    
    class SGNode;
    class CCamera;
    class CCameraManager;
    class IPreRender;
    class CGPUResourceManipulator;
    class CCameraManager;
    class CLocalClock;
    class CSynClock;
    
    class IRenderTarget;
    class CRenderQueueManager;
    class CCameraManager;
    class CRenderTargetManager;
    class CPreRenderManager;
    class CGPUResourceManipulator;
    class CRenderPipelineManager;
    
    class CWinInfo
    {
    public:
    };
    
    
    class CRenderingEngine
    {
    public:
        CRenderingEngine(void);
        virtual ~CRenderingEngine(void);

        
        virtual int		Configure( const std::string& ConfigFileName );
        
        virtual int		Initialize( const CWinInfo& WinInfo );
        
        virtual void	Finalize();
        
        int		OpenSceneModel( const std::string& SceneModelName, int ActiveSceneGraph =0 );
        void	CloseSceneModel();
        
        void	SetRenderTraverseRoot( const std::vector<SGNode*>& roots );
        void	SetCamera(CCamera& Camera );
        void	GetCamera( CCamera& Camera );
        
        
        void	ClearScreen(float r = 0.0f, float g = 0.3f, float b = 0.9f, float a = 0.0f);
        void	DoRendering();
        void	SwapBuffers();
 
        
        void SetSetupTimeBudget(double);
        void SetDrawingTimeBudget(double);
        void SetGPUMemoryBudget(int32_t);
        void SetExtraRenderingObjectBudget(int32_t);
        
        double GetSetupTimeBudget();
        double GetDrawingTimeBudget();
        int32_t GetGPUMemoryBudget();
        int32_t GetExtraRenderingObjectBudget();

        
    protected:

        //CSceneModelManipulator2*	GetSceneModelManipulator2()	{return m_pSceneModelMpr;}
        CRenderQueueManager*					GetRenderQueueManager()		{return m_pRenderQueueMgr;}
        CCameraManager*							GetCameraManager()			{return m_pCameraMgr;}
        CRenderTargetManager*					GetRenderTargetManager()	{return m_pRenderTargetMgr;}
        CPreRenderManager*						GetPreRenderManager()		{return m_pPreRenderMgr;}
        CGPUResourceManipulator*				GetGPUResourceManipulator()	{return m_pGPUResourceMpr;}
        CRenderPipelineManager*					GetRenderPipelineManager()	{return m_pRenderPipelineMgr;}
        CLocalClock*							GetLocalClock()				{return m_pLocalClock;}
        CSynClock*								GetSynClock()				{return m_pSynClock;}
        
        
    protected:
        
        virtual int RegisterPreRenderPrototypes();
        virtual int RegisterRenderPipelinePrototypes();
        
        // user override functions
        virtual int OnConfigure(){return 0;}
        virtual int OnRegisterPreRenderPrototypes(){return 0;}
        virtual int OnRegisterRenderPipelinePrototypes(){return 0;}
        
        virtual void UpdateSynClockMillSecondTime();
        virtual void UpdateFrameIndex();
        
    protected:
        
        CWinInfo								m_WinInfo;
        
        //CSceneModelManipulator2*   	m_pSceneModelMpr;
        
        CGPUResourceManipulator*				m_pGPUResourceMpr;
        
        CRenderQueueManager*   					m_pRenderQueueMgr;
        CCameraManager*							m_pCameraMgr;
        CRenderTargetManager*					m_pRenderTargetMgr;
        CPreRenderManager*						m_pPreRenderMgr;
        CRenderPipelineManager*					m_pRenderPipelineMgr;
        std::vector<SGNode*>	m_TraverseRoots;
        CLocalClock*							m_pLocalClock;

        CSynClock*								m_pSynClock;
        
        //CFrameInfo								m_FrameInfo;
        
        IPreRender*								 m_pStartPreRender;
        IRenderTarget*						 m_pPrimeTarget;
    };

}

#endif
