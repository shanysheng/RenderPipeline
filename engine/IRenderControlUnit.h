/*
 * Copyright 2017 sheng chongshan. All rights reserved.
 * email: shany.sheng@qq.com
 * License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
 */


#ifndef PIPELINE_IRENDERCONTROLUNIT_H_GUARD
#define PIPELINE_IRENDERCONTROLUNIT_H_GUARD

#include "Common.h"

namespace pipeline{
    
    struct CFrameInfo
    {
        CFrameInfo();
        
        uint64_t FrameIndex;
        double	 SynTimeMS;
    };
    
    class IRenderControlUnit
    {
    public:
        IRenderControlUnit();
        virtual ~IRenderControlUnit();
        
        virtual void PerFrame( CFrameInfo * pFI );
        virtual void BeforeFirstFrame( CFrameInfo * pFI );
        virtual void AfterLastFrame( CFrameInfo * pFI );
        virtual void PostChildrenPerFrame(CFrameInfo * pFI );
        virtual void PostChildrenBeforeFirstFrame( CFrameInfo * pFI );
        virtual void PostChildrenAfterLastFrame( CFrameInfo * pFI );
        
        virtual void Stop ();
        virtual void Start();
        bool         IsStopped() const { return m_bStopped; }
        
        void	SetNextRCU( IRenderControlUnit* pNextRCU );
        void	AppendChildrenRCU(IRenderControlUnit * pRCUnit );
        
    protected:
        
        virtual void _DoPerFrame( CFrameInfo * pFI );
        virtual void _DoBeforeFirstFrame( CFrameInfo * pFI );
        virtual void _DoAfterLastFrame( CFrameInfo * pFI );
        
    private:
        friend class CRenderingEngine;
        
    protected:
        bool m_bStopped;
        IRenderControlUnit* m_pNextRCU;
        std::vector<IRenderControlUnit*> m_ChildrenRCU;
    };
}

#endif
