#pragma once

#include <vector>

class EntityManager;
struct Scene;
struct Resources;
struct Mesh;
struct MeshComponent;

class Renderer {
public:
	Renderer() = default;
	void Draw(const Scene& scene, EntityManager& entityManager, const Resources& resources);
	void SubmitMesh(const MeshComponent& mesh);
private:
	void BindMesh(const Mesh& mesh);
private:
	std::vector<MeshComponent> meshes;
};