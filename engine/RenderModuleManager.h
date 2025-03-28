#ifndef PIPELINE_RENDERMODULEMANAGER_H_GUARD
#define PIPELINE_RENDERMODULEMANAGER_H_GUARD


#include "Common.h"

namespace pipeline{
    
    class IRenderModule;

    //------------------------------------------------------------------------------
    //	Desc:	The class CRenderModuleManager manages the life periods of a set of 
    //			render modules.
    //
    //------------------------------------------------------------------------------
    class kRenderModuleManager
    {
    public:
        kRenderModuleManager();
        virtual ~kRenderModuleManager();
        
        void				Register(const std::string& PrototypeName, IRenderModule * pPrototype);
        
        IRenderModule*		Give( const std::string& Name, const std::string& PrototypeName);
        IRenderModule*		operator [] (const std::string& Name);
        
        void				ClearPrototypes();
        void				ClearRenderModules();
        
    protected:
        std::unordered_map< std::string, IRenderModule *> m_Prototypes;
        std::unordered_map< std::string, IRenderModule *> m_RenderModules;
    };
}

#endif
