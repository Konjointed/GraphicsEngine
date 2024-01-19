#pragma once

class Scene;
struct Resources;
struct Mesh;

class Renderer {
public:
	Renderer() = default;
	void Draw(const Scene& scene, const Resources& resources);
private:
	void BindMesh(const Mesh& mesh);
};