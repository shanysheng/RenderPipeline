#ifndef PIPELINE_IRENDERCONTROLUNIT_H_GUARD
#define PIPELINE_IRENDERCONTROLUNIT_H_GUARD

#include "Common.h"

namespace pipeline{
    
    struct CFrameInfo
    {
        CFrameInfo();
        
        uint64_t frame;
        double	 timems;
    };
    
    //------------------------------------------------------------------------------
    //	Desc:		The base class for both pre-renders and render pipelines is 
    //				IRenderControlUnit. By connecting IRenderControlUnit instances 
    //				in different ways, we configure various control flows inside a 
    //				rendering engine. The object represented by IRenderControlUnit 
    //				instance is called Render Control Unit, or RCU for short.
    //
    //------------------------------------------------------------------------------
    class IRenderControlUnit
    {
    public:
        IRenderControlUnit();
        virtual ~IRenderControlUnit();
        
        virtual void PerFrame( CFrameInfo * pFI);
        virtual void BeforeFirstFrame( CFrameInfo * pFI);
        virtual void AfterLastFrame( CFrameInfo * pFI);
        virtual void PostChildrenPerFrame(CFrameInfo * pFI);
        virtual void PostChildrenBeforeFirstFrame( CFrameInfo * pFI);
        virtual void PostChildrenAfterLastFrame( CFrameInfo * pFI);
        
        virtual void Stop ();
        virtual void Start();
        bool         IsStopped() const { return m_bStopped; }
        
        void	SetNextRCU( IRenderControlUnit* pNextRCU);
        void	AppendChildrenRCU(IRenderControlUnit * pRCUnit);
        
    protected:
        
        //------------------------------------------------------------------------------
        //	Desc:	At runtime, they are invoked by the rendering engine (or say 
        //			CRenderingEngine instance) for three times. _DoPerFrame is 
        //			invoked before each frame starts; _DoBeforeFirstFrame is invoked 
        //			before the first frame for a scene model starts; _DoAfterLastFrame 
        //			is invoked after the last frame for a scene model ends.
        //
        //------------------------------------------------------------------------------
        virtual void _DoPerFrame( CFrameInfo * pFI);
        virtual void _DoBeforeFirstFrame( CFrameInfo * pFI);
        virtual void _DoAfterLastFrame( CFrameInfo * pFI);
        
    private:
        friend class kRenderingEngine;
        
    protected:
        bool m_bStopped;
        IRenderControlUnit* m_pNextRCU;
        std::vector<IRenderControlUnit*> m_ChildrenRCU;
    };
}

#endif
