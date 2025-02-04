#ifndef PIPELINE_IGPURESOURCE_H_GUARD
#define PIPELINE_IGPURESOURCE_H_GUARD

#include "Common.h"

namespace pipeline{
    
    class IRHIResource
    {
    public:
        friend class kRHIResourceManager;
        IRHIResource();
        
        uint32_t GetRefenceCount()const{return m_ReferenceCount;}
        int32_t	GetGPUMemoryCost() const{return m_GPUMemoryCost;}
        
        virtual void Bind()const{};
        virtual void Unbind()const{};
        
    protected:
        IRHIResource*	Reference(){ ++m_ReferenceCount; return this;}
        void			Unreference(){ --m_ReferenceCount;}
        virtual	~IRHIResource();
        
    protected: 
        int32_t			m_ReferenceCount;
        uint32_t		m_GPUMemoryCost;
    };
}

#endif
