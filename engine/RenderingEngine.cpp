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

    void kRenderingEngine::SetCamera(CCamera& Camera) {

    }

    void kRenderingEngine::GetCamera(CCamera& Camera) {

    }


    void kRenderingEngine::ClearScreen(float r, float g, float b, float a) {

    }

    void kRenderingEngine::DoRendering() {

    }

    void kRenderingEngine::SwapBuffers() {

    }


    void kRenderingEngine::SetSetupTimeBudget(double) {

    }

    void kRenderingEngine::SetDrawingTimeBudget(double) {

    }

    void kRenderingEngine::SetGPUMemoryBudget(int32_t) {

    }

    void kRenderingEngine::SetExtraRenderingObjectBudget(int32_t) {

    }

    double kRenderingEngine::GetSetupTimeBudget() {
        return 0.0;
    }

    double kRenderingEngine::GetDrawingTimeBudget() {
        return 0.0;
    }

    int32_t kRenderingEngine::GetGPUMemoryBudget() {
        return 0;
    }

    int32_t kRenderingEngine::GetExtraRenderingObjectBudget() {
        return 0;
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
