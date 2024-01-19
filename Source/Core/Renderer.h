#pragma once

#include <vector>

struct Scene;
struct Resources;
struct Mesh;
struct MeshComponent;

class Renderer {
public:
	Renderer() = default;
	void Draw(const Scene& scene, const Resources& resources);
	void SubmitMesh(const MeshComponent& mesh);
private:
	void BindMesh(const Mesh& mesh);
private:
	std::vector<MeshComponent> meshes;
};