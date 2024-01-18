#include "Scene.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void InitScene(Scene& scene)
{
    scene.camera.behavior = std::make_unique<DebugCameraBehavior>();

    scene.shaderProgram.AddShaders(GL_VERTEX_SHADER, "Resources/Shaders/Default.vert", GL_FRAGMENT_SHADER, "Resources/Shaders/Default.frag");
    scene.shaderProgram.Link();
}

void LoadMesh(const std::string& filepath, Scene& t_scene)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath,
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    ProcessNode(scene->mRootNode, scene, t_scene);
}