/*
* Copyright 2017 sheng chongshan. All rights reserved.
* email: shany.sheng@qq.com
* License: https://github.com/shanysheng/RenderPipeline/blob/master/LICENSE
*/

#ifndef PIPELINE_SKINANIM_H_GUARD
#define PIPELINE_SKINANIM_H_GUARD

namespace pipelin {
    
    class SkinAnim
    {
    public:
        
        bool animatePhysics;
        AnimationClip clip;
        AnimationCullingType cullingType;
        
        bool isPlaying;
        Bounds localBounds ;
        
        bool playAutomatically ;
        
        WrapMode wrapMode ;
        
        AnimationState ;
        
        void AddClip (AnimationClip clip, const std::string& newName, int firstFrame, int lastFrame);
        void AddClip (AnimationClip clip, const std::string& newName);
        void Blend (const std::string& animation);
        void Blend (const std::string& animation, float targetWeight);
        
        void CrossFade (const std::string& animation);
        AnimationState CrossFadeQueued (const std::string& animation, float fadeLength, QueueMode queue);
        AnimationState CrossFadeQueued (const std::string& animation, float fadeLength);
        AnimationClip GetClip (const std::string& name);
        
        int GetClipCount ();
        int GetStateCount ();
        AnimationState GetState (const std::string& name);
        AnimationState GetStateAtIndex (int index);
        
        bool IsPlaying (const std::string& name);
        
        bool Play ();
        bool Play (const std::string& animation);
        bool Play (const std::string& animation);
        
        private bool PlayDefaultAnimation (PlayMode mode);
        
        AnimationState PlayQueued ();
        AnimationState PlayQueued (const std::string& animation);
        AnimationState PlayQueued (const std::string& animation, QueueMode queue);
        void RemoveClip (AnimationClip clip);
        void RemoveClip (const std::string& clipName);
        void RemoveClip2 (const std::string& clipName);
        
        void Rewind (const std::string& name);
        void Rewind ();
        
        void Sample ();
        void Stop (const std::string& name);
        void Stop ();
        
        void SyncLayer (int layer);
        
    };
}

#endif
