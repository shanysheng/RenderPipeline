/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_COMPONENT_H_GUARD
#define PIPELINE_COMPONENT_H_GUARD

#include "Common.h"

namespace pipeline {

    class SGNode;
    
    class Component
    {
    public:
        SGNode* sgnode ;
        
        
        
        Component* GetComponent (Type type)
        Component* GetComponent (const string& type);
        
        Component* GetComponentInChildren (Type t, bool includeInactive);
        Component* GetComponentInChildren (Type t);
        
        Component* GetComponentInParent (Type t);
        
        void GetComponents (Type type, std::vector<Component*> results);
        
        T[] GetComponentsInChildren<T> ();
        void GetComponentsInChildren<T> (std::vector<T> results);
        void GetComponentsInChildren<T> (bool includeInactive, std::vector<T> result);
        T[] GetComponentsInChildren<T> (bool includeInactive);
        Component[] GetComponentsInChildren (Type t);
        
        void GetComponentsInParent<T> (bool includeInactive, std::vector<T> results);
        T[] GetComponentsInParent<T> (bool includeInactive);
        Component[] GetComponentsInParent (Type t);
        T[] GetComponentsInParent<T> ();
        Component[] GetComponentsInParent (Type t, bool includeInactive);
        
        
    };
}

#endif
