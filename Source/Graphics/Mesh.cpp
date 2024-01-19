#include "Mesh.h"

#include <iostream>

#include <glad/glad.h>

#include "../Core/Game.h"

Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int vao, vbo, ebo;

    //-----------------------------------------------------------------------------
    // Vertices, normals, texture coordinates, and indices
    //-----------------------------------------------------------------------------
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        // Position
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        // Normals
        if (mesh->HasNormals()) {
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
        }

        // Texture Coordinates
        if (mesh->mTextureCoords[0]) {
            vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Indicdes
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    //-----------------------------------------------------------------------------
    // Create buffers/arrays
    //-----------------------------------------------------------------------------
    // Generate and bind the Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate and bind the Vertex Buffer Object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // Generate and bind the Element Buffer Object
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //-----------------------------------------------------------------------------
    // Set vertex attributes pointers
    //-----------------------------------------------------------------------------
    // Position 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    // Texture Coord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);
    // Color
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);
    // Tangent
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    // Bitangent
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    glEnableVertexAttribArray(5);

    // Unbind VAO
    glBindVertexArray(0);

    Mesh processedMesh;
    processedMesh.vertices = vertices;
    processedMesh.indices = indices;
    processedMesh.vao = vao;
    processedMesh.vbo = vbo;
    processedMesh.ebo = ebo;

    return processedMesh;
}

std::vector<Mesh> ProcessNode(aiNode* node, const aiScene* scene)
{
    std::vector<Mesh> meshes;

    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
        Mesh processedMesh = ProcessMesh(aiMesh, scene);
        meshes.push_back(processedMesh);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        std::vector<Mesh> childMeshes = ProcessNode(node->mChildren[i], scene);
        meshes.insert(meshes.end(), childMeshes.begin(), childMeshes.end());
    }

    return meshes;
}

void LoadMesh(Resources& resources, const std::string& filepath, const std::string& name)
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

    std::vector<Mesh> meshes = ProcessNode(scene->mRootNode, scene);

    for (size_t i = 0; i < meshes.size(); i++) {
        std::string meshName = name + "_" + std::to_string(i);
        resources.meshes[name] = meshes[i];
    }
}