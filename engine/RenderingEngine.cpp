#include "RenderingEngine.h"

namespace pipeline {
    
    kRenderingEngine::kRenderingEngine(void) {

    }

    kRenderingEngine::~kRenderingEngine(void) {

    }


    int kRenderingEngine::Configure(const std::string& ConfigFileName) {
        return 1;
    }

    int kRenderingEngine::Initialize(const kWinInfo& WinInfo) {
        return 1;
    }

    void  kRenderingEngine::Finalize() {

    }

    int kRenderingEngine::OpenSceneModel(const std::string& SceneModelName, int ActiveSceneGraph ) {
        return 1;
    }

    void kRenderingEngine::CloseSceneModel() {

    }

    void kRenderingEngine::SetRenderTraverseRoot(const std::vector<kSGNode*>& roots) {

    }

    void kRenderingEngine::SetCamera(kCamera& Camera) {

    }

    void kRenderingEngine::GetCamera(kCamera& Camera) {

    }


    void kRenderingEngine::ClearScreen(float r, float g, float b, float a) {

    }

    void kRenderingEngine::DoRendering() {

    }

    void kRenderingEngine::SwapBuffers() {

    }

    int kRenderingEngine::RegisterPreRenderPrototypes() {
        return 1;
    }

    int kRenderingEngine::RegisterRenderPipelinePrototypes() {
        return 1;
    }

    // user override functions
    int kRenderingEngine::OnConfigure() { return 0; }
    int kRenderingEngine::OnRegisterPreRenderPrototypes() { return 0; }
    int kRenderingEngine::OnRegisterRenderPipelinePrototypes() { return 0; }

    void kRenderingEngine::UpdateSynClockMillSecondTime() {

    }

    void kRenderingEngine::UpdateFrameIndex() {

    }

    
}
