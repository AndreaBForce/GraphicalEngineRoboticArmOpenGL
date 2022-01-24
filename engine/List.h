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

	int get_number_of_elements() { return listObject.size(); };
	void put_back_of_vec(Object* element) { listObject.push_back(element); };
	void put_front_of_vec(Object* element) { listObject.insert(listObject.begin(), element); };
	void addRenderObject(Object* element);
	void render_list(glm::mat4 camera);
	Object* get_element_by_name(const char* name);

	std::vector<Object*> get_list() { return listObject; };
private:
	std::vector<Object*> listObject;

};

#endif // LIST_H
