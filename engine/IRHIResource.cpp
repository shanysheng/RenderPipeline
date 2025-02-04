#include "IRHIResource.h"

namespace pipeline {
    
    
    IGPUResource::IGPUResource()
    :m_ReferenceCount(1),m_GPUMemoryCost(0)
    {
        
    }
    
    IGPUResource::~IGPUResource()
    {
        
    }

}
