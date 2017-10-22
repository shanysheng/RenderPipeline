/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_COMPONENT_H_GUARD
#define PIPELINE_COMPONENT_H_GUARD

#include "Common.h"
#include "FeatureType.h"

namespace pipeline {

    class SGNode;
    
    class Component
    {
    public:
        SGNode* sgnode ;
        
        
        
        Component* GetComponent (FeatureType type);
        Component* GetComponent (const std::string& type);
        
        Component* GetComponentInChildren (FeatureType t, bool includeInactive);
        Component* GetComponentInChildren (FeatureType t);
        
        Component* GetComponentInParent (FeatureType t);
        
        void GetComponents (FeatureType type, std::vector<Component*> results);
        
//        T[] GetComponentsInChildren<T> ();
//        void GetComponentsInChildren<T> (std::vector<T> results);
//        void GetComponentsInChildren<T> (bool includeInactive, std::vector<T> result);
//        T[] GetComponentsInChildren<T> (bool includeInactive);
//        Component[] GetComponentsInChildren (FeatureType t);
//
//        void GetComponentsInParent<T> (bool includeInactive, std::vector<T> results);
//        T[] GetComponentsInParent<T> (bool includeInactive);
//        Component[] GetComponentsInParent (FeatureType t);
//        T[] GetComponentsInParent<T> ();
        //Component[] GetComponentsInParent (FeatureType t, bool includeInactive);
        
        
    };
}

#endif
