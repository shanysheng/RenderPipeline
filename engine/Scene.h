#ifndef PIPELINE_SCENE_H_GUARD
#define PIPELINE_SCENE_H_GUARD


#include "Common.h"

namespace pipeline{

    class kSGNode;
    class kMesh;
    
    class kScene
    {
    public:
        kScene();
        virtual ~kScene();

        int LoadScene(const std::string& filepath);

    protected:

        kSGNode* m_RootNode;

        std::vector<kSGNode*>    m_Roots;

        std::map<std::string, kMesh*> m_StaticModelMap;
    };
}


#endif
