#include "Scene.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "tiny_gltf.h"

namespace pipeline {
    
    kScene::kScene() {

    }

    kScene::~kScene() {

    }

    int kScene::LoadScene(const std::string& filepath) {
        return 1;
    }
}
