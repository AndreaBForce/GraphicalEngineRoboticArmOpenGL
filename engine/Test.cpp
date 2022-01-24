#include "Test.h"
#include <iostream>
#include <cassert>


LIB_API Test::Test() {

}

LIB_API Test::~Test() {

}

void LIB_API Test::testLight() {
	Light* light = new Light();

	assert(light->getLightNr() == LIGHT0);

	light->setAmbient(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	assert(light->getAmbient() == glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	light->setDirection(glm::vec3(4.0f, 4.0f, 4.0f));
	assert(light->getDirection() == glm::vec3(4.0f, 4.0f, 4.0f));

	light->setCutoff(3.5f);
	assert(light->getCutoff() == 3.5f);

	light->setLightType(DIRECTIONAL);
	assert(light->getLightType() == DIRECTIONAL);

	light->setSpecular(glm::vec4(2.0f, 2.0f, 2.0f, 2.0f));
	assert(light->getSpecular() == glm::vec4(2.0f, 2.0f, 2.0f, 2.0f));

	light->setDiffuse(glm::vec4(3.0f, 3.0f, 3.0f, 3.0f));
	assert(light->getDiffuse() == glm::vec4(3.0f, 3.0f, 3.0f, 3.0f));

	delete(light);
}

void LIB_API Test::testMaterial() {
	Material* material = new Material();

	material->setAmbient(glm::vec3(1.0f, 1.0f, 1.0f));
	assert(material->getAmbient() == glm::vec4(1.0f * 0.2, 1.0f * 0.2, 1.0f * 0.2, 1.0f));

	material->setDiffuse(glm::vec3(3.0f, 3.0f, 3.0f));
	assert(material->getDiffuse() == glm::vec4(3.0f * 0.6, 3.0f * 0.6, 3.0f * 0.6, 1.0f));

	material->setEmission(glm::vec3(2.0f, 2.0f, 2.0f));
	assert(material->getEmission() == glm::vec4(2.0f, 2.0f, 2.0f, 1.0f));

	material->setShininess(2.0f);
	assert(material->getShiness() == (1 - sqrt(2.0f)) * 128);

	material->setSpecular(glm::vec3(4.0f, 4.0f, 4.0f));
	assert(material->getSpecular() == glm::vec4(4.0f * 0.4, 4.0f * 0.4, 4.0f * 0.4, 1.0f));
}

void LIB_API Test::testVertex() {
	Vertex* vertex = new Vertex();

	vertex->setNormal(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	assert(vertex->getNormal() == glm::vec3(1.0f, 1.0f, 1.0f));

	vertex->setUv(glm::vec2(2.0f, 2.0f));
	assert(vertex->getUv() == glm::vec2(2.0f, 2.0f));

	vertex->setVertex(glm::vec3(3.0f, 3.0f, 3.0f));
	assert(vertex->getVertex() == glm::vec3(3.0f, 3.0f, 3.0f));
}

void LIB_API Test::testMesh() {
	Mesh* mesh = new Mesh();

	mesh->set_bBoxMin(glm::vec3(1.0f, 1.0f, 1.0f));
	assert(mesh->getBoxMin() == glm::vec3(1.0f, 1.0f, 1.0f));

	mesh->set_bBoxMax(glm::vec3(2.0f, 2.0f, 2.0f));
	assert(mesh->getBoxMax() == glm::vec3(2.0f, 2.0f, 2.0f));

	mesh->set_radius(2.0f);
	assert(mesh->getRadius() == 2.0f);

	mesh->set_children(4);
	assert(mesh->getChildren() == 4);

	mesh->setHasShadow(true);
	assert(mesh->getHasShadow() == true);
}
void LIB_API Test::testList() {
	List* list = new List();
	Mesh* mesh = new Mesh();
	mesh->set_name("mesh");
	Light* light = new Light();
	light->set_name("light");

	list->put_front_of_vec(mesh);
	assert(list->get_number_of_elements() == 1);
	list->put_back_of_vec(light);
	assert(list->get_number_of_elements() == 2);
	assert(list->get_element_by_name("mesh") == mesh);
	assert(list->get_element_by_name("light") == light);

	delete(light);
}

void LIB_API Test::testCamera() {

}

void LIB_API Test::testTexture() {
	char name[] = "texture 1";
	Texture* texture = new Texture(name);
	assert(texture->getTextureId() == 0);
}



void LIB_API Test::testNode() {
	Node* node = new Node();

	node->set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
	assert(node->get_scale() == glm::vec3(1.0f, 1.0f, 1.0f));

	node->set_translation(glm::vec3(2.0f, 2.0f, 2.0f));
	assert(node->get_translation() == glm::vec3(2.0f, 2.0f, 2.0f));

	node->set_pos_matrix(glm::mat4(1.0f));
	assert(node->get_pos_matrix() == glm::mat4(1.0f));

	node->set_orientation(glm::quat());
	assert(node->getOrientation() == glm::quat());
}

void LIB_API Test::testObject() {
	Mesh* mesh = new Mesh();
	Light* light = new Light();

	assert(mesh->get_id() != 0);
	assert(light->get_id() != 0);
}

void LIB_API Test::testExec() {
	testLight();
	testMaterial();
	testVertex();
	testMesh();
	testList();
	testCamera();
	testTexture();
	testNode();
	testObject();
}