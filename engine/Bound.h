#ifndef PIPELINE_BOUND_H_GUARD
#define PIPELINE_BOUND_H_GUARD

#include "Common.h"
#include "Vector3.h"

namespace pipeline{
    
    class kBound
    {
    public:
        kBound();
        kBound(const kVector3f& minpt, const kVector3f& maxpt);

        kVector3f m_Min;
        kVector3f m_Max;
    };
}

#endif
