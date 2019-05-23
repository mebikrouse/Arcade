#include "Object.h"

Object::Object() 
{
	_id = IdFactory++;
}

Object::~Object() { }

bool operator== (const Object& left, const Object& right)
{
	return left._id == right._id;
}

bool operator!= (const Object& left, const Object& right)
{
	return left._id != right._id;
}

unsigned long Object::IdFactory = 0;
