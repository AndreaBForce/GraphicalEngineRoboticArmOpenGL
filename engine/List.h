#ifndef LIST_H
#define LIST_H
#include "Object.h"
#include "Utils.h"
#include <vector>

class LIB_API List : public Object{
public:

private:
	std::vector<Object> objectList;
};

#endif // LIST_H