#pragma once

#include <memory>

class Object : public std::enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object() = 0;

	friend bool operator== (const Object& left, const Object& right);
	friend bool operator!= (const Object& left, const Object& right);

	template<class T>
	std::shared_ptr<T> shared_from_base() {
		return std::dynamic_pointer_cast<T>(shared_from_this());
	}

private:
	unsigned long _id;

	static unsigned long IdFactory;
};

