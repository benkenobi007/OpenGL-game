#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "shader.h"
#include "Material.h"

class Model {
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	void updateUniforms() {

	}
public:
	Model(
		glm::vec3 position,
		Material* material,
		Texture* orTexDif,
		Texture* orTexSpec,
		std::vector<Mesh*> meshes
	)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;

		for (auto* i : meshes) {
			this->meshes.push_back(new Mesh(*i));
		}

		//Offset the mesh by the model position
		for (auto& i : this->meshes) {
			i->move(this->position);
			i->setOrigin(this->position);
		}
	}

	~Model() {
		for (auto*& i : this->meshes) {
			delete i;
		}
	}

	//Functions

	void rotate(const glm::vec3 rotation) 
	{
		for (auto& i : this->meshes)
			i->rotate(rotation);
	}
	void update() {

	}

	void render(Shader* shader) {
		this->updateUniforms();

		this->material->sendToShader(*shader);

		//Use program
		shader->use();

		//Activate Texture
		this->overrideTextureDiffuse->bind(0);
		this->overrideTextureSpecular->bind(1);

		//draw
		for (auto& i : this->meshes) {
			i->render(shader);
		}
		

	}
};