#include "IRenderControlUnit.h"

namespace pipeline{
    
    CFrameInfo::CFrameInfo()
    {
        frame = 0;
        timems = 0;
    }
    
    IRenderControlUnit::IRenderControlUnit()
    {
        m_bStopped = false;
        m_pNextRCU = NULL;
    }
    
    IRenderControlUnit::~IRenderControlUnit()
    {
        m_bStopped = false;
        m_pNextRCU = NULL;
        m_ChildrenRCU.clear();
    }
    
    void IRenderControlUnit::_DoPerFrame( CFrameInfo * pFI )
    {
        if(IsStopped())
            return ;
        
        PerFrame(pFI);
        
        for(uint32_t i = 0;i<m_ChildrenRCU.size();++i)
            m_ChildrenRCU[i]->_DoPerFrame(pFI);
        
        if(!m_ChildrenRCU.empty())
            PostChildrenPerFrame(pFI);
        
        if(m_pNextRCU)
            m_pNextRCU->_DoPerFrame(pFI);
    }
    
    void IRenderControlUnit::_DoBeforeFirstFrame( CFrameInfo * pFI )
    {
        if(IsStopped())
            return;
        
        BeforeFirstFrame(pFI);
        
        for(uint32_t i = 0;i<m_ChildrenRCU.size();++i)
            m_ChildrenRCU[i]->_DoBeforeFirstFrame(pFI);
        
        if(!m_ChildrenRCU.empty())
            PostChildrenBeforeFirstFrame(pFI);
        
        if(m_pNextRCU)
            m_pNextRCU->_DoBeforeFirstFrame(pFI);
    }
    
    void IRenderControlUnit::_DoAfterLastFrame( CFrameInfo * pFI )
    {
        if(IsStopped())
            return;
        
        AfterLastFrame(pFI);
        
        for(uint32_t i = 0;i<m_ChildrenRCU.size();++i)
            m_ChildrenRCU[i]->_DoAfterLastFrame(pFI);
        
        if(!m_ChildrenRCU.empty())
            PostChildrenAfterLastFrame(pFI);
        
        if(m_pNextRCU)
            m_pNextRCU->_DoAfterLastFrame(pFI);
    }
    
    void IRenderControlUnit::Stop ()
    {
        m_bStopped = true;
        
        for(uint32_t i = 0;i<m_ChildrenRCU.size();++i)
            m_ChildrenRCU[i]->Stop();
        
        if(m_pNextRCU)
            m_pNextRCU->Stop();
    }
    
    void IRenderControlUnit::Start()
    {
        m_bStopped = false;
        
        for(uint32_t i = 0;i<m_ChildrenRCU.size();++i)
            m_ChildrenRCU[i]->Start();
        
        if(m_pNextRCU)
            m_pNextRCU->Start();
    }
    
    void IRenderControlUnit::SetNextRCU( IRenderControlUnit* pNextRCU )
    {
        m_pNextRCU = pNextRCU;
    }
    
    void IRenderControlUnit::AppendChildrenRCU(IRenderControlUnit * pRCUnit )
    {
        m_ChildrenRCU.push_back(pRCUnit);
    }
    
    void IRenderControlUnit::PerFrame( CFrameInfo * pFI )
    {
    }
    
    void IRenderControlUnit::BeforeFirstFrame( CFrameInfo * pFI )
    {
    }
    
    void IRenderControlUnit::AfterLastFrame( CFrameInfo * pFI )
    {
    }
    
    void IRenderControlUnit::PostChildrenPerFrame(CFrameInfo * pFI )
    {
    }
    
    void IRenderControlUnit::PostChildrenBeforeFirstFrame( CFrameInfo * pFI )
    {
    }
    
    void IRenderControlUnit::PostChildrenAfterLastFrame( CFrameInfo * pFI )
    {
    }
}
