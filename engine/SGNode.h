#ifndef PIPELINE_SGNODE_H_GUARD
#define PIPELINE_SGNODE_H_GUARD

#include "Common.h"
#include "Vector3.h"
#include "Matrix4x4.h"

namespace pipeline {
    
    class Transform;
    class Component;
    
    class kSGNode
    {
    public:
        kSGNode ();
        kSGNode (std::string name);
        
        bool IsActive();
        bool IsHierarchyActive();
        void SetActive(bool bactive);
        void SetActiveRecursively (bool state);

        bool IsStatic();
        void SetStatic(bool bstatic);
        
        int32_t GetLayer();
        void SetLayer(int32_t layer);
        
        const std::string& GetTag();
        void SetTag(const char* tagstr);
          
        void BroadcastMessage(const std::string& methodName, int32_t options);
        void SendMessage(const std::string& methodName, int32_t options);

        void SetLocalEulerHint(const kVector3f& euler);
        void SetPositionAndRotation(const kVector3f& position, kMatrix4x4f rotation);
        
        static kSGNode* CreatePrimitive(int32_t type);
        static kSGNode* Find (const std::string& name);
        static kSGNode FindSGNodeWithTag (const std::string& tag);
        static int32_t FindSGNodesWithTag (const std::string& tag, std::list<Component*>& results);

    protected:
        
        bool        m_bAactive ;
        bool        m_bStatic;
        int32_t     m_Layer ;
        std::string m_Tag ;
        
        kVector3f    localEulerAngles;
        kVector3f    localPosition;
        kMatrix4x4f localRotation;
        kVector3f    localScale;

        //Component animation ;
        //Component audio ;
        //Component camera ;
        //Component collider ;
        //Component light;
        //Component particleSystem;
        //Component renderer;
        //Component rigidbody;
    };
}

#endif
