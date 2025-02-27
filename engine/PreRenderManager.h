#ifndef PIPELINE_PRERENDERMANAGER_H_GUARD
#define PIPELINE_PRERENDERMANAGER_H_GUARD

#include "Common.h"
#include "IPreRender.h"

namespace pipeline{
    
    class IPreRender;
    class kRenderingEngine;
    
    //------------------------------------------------------------------------------
    //	Desc:		The main function of CPreRenderManager is to manage pre-render's 
    //				life periods as well as to provide searching services.
    //
    //------------------------------------------------------------------------------
    class kPreRenderManager
    {
    public:
        kPreRenderManager();
        virtual ~kPreRenderManager();
        
        void		Register(const std::string& PrototypeName, IPreRender* pPrototype);
        
        IPreRender* Give( const std::string& PreRenderMame, const std::string& PrototypeName);
        IPreRender* operator [] (const std::string& PreRenderName);
        
        void		ClearPrototypes();
        void		ClearPreRenders();
        
    protected:
        
        std::unordered_map<std::string, IPreRender*> m_Prototypes;
        std::unordered_map<std::string, IPreRender*> m_PreRenders;
    };
    
}

#endif
