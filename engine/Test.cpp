#include "Test.h"
#include <iostream>
#include <cassert>


LIB_API Test::Test() {

}

LIB_API Test::~Test() {

}

void LIB_API Test::testLight() {
    std::cout << "TESTING LIGHT" << std::endl;
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
    std::cout << "TESTING MATERIAL" << std::endl;
	Material* material = new Material();

	material->setAmbient(glm::vec3(1.0f, 1.0f, 1.0f));
	assert(material->getAmbient() == glm::vec4(1.0f * 0.2, 1.0f * 0.2, 1.0f * 0.2, 1.0f));

	material->setDiffuse(glm::vec3(3.0f, 3.0f, 3.0f));
	assert(material->getDiffuse() == glm::vec4(3.0f * 0.6, 3.0f * 0.6, 3.0f * 0.6, 1.0f));

	material->setEmission(glm::vec3(2.0f, 2.0f, 2.0f));
	assert(material->getEmission() == glm::vec4(2.0f, 2.0f, 2.0f, 1.0f));

	material->setShininess(2.0f);
	assert(material->getShiness() - ((1 - sqrt(2.0f)) * 128) < 0.0000001f);

	material->setShininess(1.0f);
	assert(material->getShiness() == 0.0f);

	material->setSpecular(glm::vec3(4.0f, 4.0f, 4.0f));
	assert(material->getSpecular() == glm::vec4(4.0f * 0.4, 4.0f * 0.4, 4.0f * 0.4, 1.0f));

	delete(material);
}

void LIB_API Test::testVertex() {
    std::cout << "TESTING VERTEX" << std::endl;
	Vertex* vertex = new Vertex();

	vertex->setNormal(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	assert(vertex->getNormal() == glm::vec3(1.0f, 1.0f, 1.0f));

	vertex->setUv(glm::vec2(2.0f, 2.0f));
	assert(vertex->getUv() == glm::vec2(2.0f, 2.0f));

	vertex->setVertex(glm::vec3(3.0f, 3.0f, 3.0f));
	assert(vertex->getVertex() == glm::vec3(3.0f, 3.0f, 3.0f));
	delete(vertex);
}

void LIB_API Test::testMesh() {
    std::cout << "TESTING MESH" << std::endl;
	Mesh* mesh = new Mesh();

	mesh->setChildren(4);
	assert(mesh->getChildren() == 4);

	mesh->setHasShadow(true);
	assert(mesh->getHasShadow() == true);
	delete(mesh);
}
void LIB_API Test::testList() {
    std::cout << "TESTING LIST" << std::endl;
	List* list = new List();
	Mesh* mesh = new Mesh();
	mesh->set_name("mesh");
	Light* light = new Light();
	light->set_name("light");

	list->pushFrontOfVec(mesh);
	assert(list->getNumberOfElements() == 1);
	list->pushBackOfVec(light);
	assert(list->getNumberOfElements() == 2);
	assert(list->getElementByName("mesh") == mesh);
	assert(list->getElementByName("light") == light);

	list->addRenderObject(new Material());
	assert(list->getNumberOfElements() == 2);

	delete(list);
}

void LIB_API Test::testCamera() {
    std::cout << "TESTING CAMERA" << std::endl;
    Camera* cam = new Camera();
    glm::vec3 eye(-40.0f, 50.0f, -65.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    glm::vec3 center(-40.0f, 0.0f, 40.0f);

    cam->setEye(eye);
    assert(cam->getEye() == eye);

    cam->setCenter(center);
    assert(cam->getCenter() == center);

    cam->setUp(up);
    assert(cam->getUp() == up);

    glm::mat4 camMat = glm::lookAt(eye, center, up);
    assert(cam->getCameraMat() == camMat);

    delete(cam);

}

void LIB_API Test::testTexture() {
    std::cout << "TESTING TEXTURE" << std::endl;
	char name[] = "texture 1";
	Texture* texture = new Texture(name);
	assert(texture->getTextureId() == 0);
	delete(texture);
}

void LIB_API Test::testNode() {
    std::cout << "TESTING NODE" << std::endl;
	Node* node = new Node();

	node->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	assert(node->getScale() == glm::vec3(1.0f, 1.0f, 1.0f));

	node->setTranslation(glm::vec3(2.0f, 2.0f, 2.0f));
	assert(node->getTranslation() == glm::vec3(2.0f, 2.0f, 2.0f));

	node->setPosMatrix(glm::mat4(1.0f));
	assert(node->getPosMatrix() == glm::mat4(1.0f));

	node->setOrientation(glm::quat());
	assert(node->getOrientation() == glm::quat());

	delete(node);
}

void LIB_API Test::testObject() {
    std::cout << "TESTING OBJECT" << std::endl;
	Mesh* mesh = new Mesh();
	Light* light = new Light();

	assert(mesh->get_id() != 0);
	assert(light->get_id() != 0);

	delete(light);
	delete(mesh);
}

void LIB_API Test::testExec() {
    std::cout << "*****************" << std::endl;
    std::cout << "TEST STARTING" << std::endl;
    std::cout << "*****************" << std::endl;
	testLight();
	testMaterial();
	testVertex();
	testMesh();
	testList();
	testCamera();
	testTexture();
	testNode();
	testObject();
    std::cout << "*****************" << std::endl;
	std::cout << "TEST FINISHED" << std::endl;
    std::cout << "*****************" << std::endl;
}
