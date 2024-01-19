#include "Scene.h"
#include "GameObject.h"
#include "Components.h"
#include "Game.h"

GameObject& Scene::CreateGameObject(const std::string& name) {
    GameObject object;

    object.addComponent(TransformComponent{});
    object.addComponent(TagComponent{});
    object.getComponent<TagComponent>()->tag = name;

    objects.push_back(std::move(object)); // Use move semantics to avoid copying

    return objects.back(); // Return a reference to the newly added object
}

void Scene::DestroyGameObject(GameObject object) {

}

void CreateScene(Scene& scene) {
	scene.shaderProgram.AddShaders(GL_VERTEX_SHADER, "Resources/Shaders/Default.vert", GL_FRAGMENT_SHADER, "Resources/Shaders/Default.frag");
	scene.shaderProgram.Link();

    GameObject& object = scene.CreateGameObject("Suzanne");
    object.addComponent(MeshComponent{ "cube" });
}