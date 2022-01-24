#ifndef LIST_H
#define LIST_H
#include "Object.h"
#include "Utils.h"
#include <vector>

class LIB_API List : public Object {
public:
	List();
	~List();
	void render(glm::mat4 camera) {};

	int getNumberOfElements() { return listObject.size(); };
	void pushBackOfVec(Object* element) { listObject.push_back(element); };
	void pushFrontOfVec(Object* element) { listObject.insert(listObject.begin(), element); };
	void addRenderObject(Object* element);
	void renderList(glm::mat4 camera);
	Object* getElementByName(const char* name);

	std::vector<Object*> getList() { return listObject; };
private:
	std::vector<Object*> listObject;

};

#endif // LIST_H
