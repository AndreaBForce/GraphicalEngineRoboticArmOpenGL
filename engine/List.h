#ifndef LIST_H
#define LIST_H
#include "Object.h"
#include "Utils.h"
#include <vector>
class LIB_API List : public Object {
public:
	List();
	~List();
	void render() {};

	int get_number_of_elements() { return listObject.size(); };
	void put_back_of_vec(Object* oggetto) { listObject.push_back(oggetto); };
	void put_front_of_vec(Object* oggetto) { listObject.insert(listObject.begin(), oggetto); };
	void render_list();
	Object* get_element_by_name(char* name);

	std::vector<Object*> get_list() { return listObject; };
private:
	std::vector<Object*> listObject;
};

#endif // LIST_H