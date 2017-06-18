/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_SGNODE_H_GUARD
#define PIPELINE_SGNODE_H_GUARD

#include "Common.h"
#include "Transform.h"

namespace pipeline {
    
    class Transform
    
    class SGNode
    {
    public:
        SGNode ();
        SGNode (string name);
        
        bool IsActive();
        bool IsHierarchyActive();
        void SetActive(bool bactive);
        
        bool IsStatic();
        void SetStatic(bool bstatic);
        
        int32_t GetLayer();
        void SetLayer(int32_t layer);
        
        const std::string& GetTag();
        void SetTag(const char* tagstr);
        
        Component* AddComponent(int32_t componentType)
        Component* GetComponent(int32_t type);
        void GetComponents(int32_t type, std::list<Component*>& results);
        void GetComponentsInChildren(int32_t type, bool includeInactive, std::list<Component*>& results);
        void GetComponentsInParent(int32_t type, bool includeInactive, std::list<Component*>& results);
     
        void SetActive (bool value);
        void SetActiveRecursively (bool state);
        
        void BroadcastMessage(const std::string& methodName, int32_t options);
        void SendMessage(const std::string& methodName, int32_t options);
        
        static SGNode* CreatePrimitive(int32_t type);
        static SGNode* Find (const std::string& name);
        static SGNode FindSGNodeWithTag (const std::string& tag);
        static int32_t FindSGNodesWithTag (const std::string& tag, std::list<Component*>& results);

    protected:
        
        bool        m_bAactive ;
        bool        m_bStatic;
        int32_t     m_Layer ;
        std::string m_Tag ;
        
        //Component animation ;
        //Component audio ;
        //Component camera ;
        //Component collider ;
        //Component light;
        //Component particleSystem;
        //Component renderer;
        //Component rigidbody;
        
        Transform transform
    };
}

#endif
