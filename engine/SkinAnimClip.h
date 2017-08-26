/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_SKINANIMCLIP_H_GUARD
#define PIPELINE_SKINANIMCLIP_H_GUARD

namespace pipeline {
    class SkinAnimClip
    {
    public:
        // Properties
        //
        bool empty {
            [GeneratedByOldBindingsGenerator]
            [MethodImpl (MethodImplOptions.InternalCall)]
            get;
        }
        
        AnimationEvent[] events ;
        
        float frameRate;
        
        bool humanMotion ;
        
        
        float length ;
        
        Bounds localBounds ;
        
        float startTime ;
        
        float stopTime
        
        
        WrapMode wrapMode ;
        
   
        
        AnimationClip ();
       
        void AddEvent (AnimationEvent evt);
        
        void ClearCurves ();
        
        void EnsureQuaternionContinuity ();
        
        
        void SampleAnimation (SGNode go, float time);
        
        
        void SetCurve (const std::string& relativePath, Type type, const std::string& propertyName, AnimationCurve curve);
        
        
        void SetEventsInternal (Array value);
    };
}

#endif
